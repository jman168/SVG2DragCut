#include <iostream>

#include "SVGPathParser.h"

void SVGPathParser::parse(std::string pathData) {
    tokens.clear();

    workingString = pathData;
    tokenize();
    getPaths();
}

void SVGPathParser::tokenize() {
    std::string buffer = "";

    for(char c : workingString) {
        if(SVGPathToken::getCommandFromChar(c) != Command::none) { // If the current charactor is a command
            if(buffer != "") { // If the buffer isn't empty push it to the tokens and clear it
                tokens.push_back(SVGPathToken(std::stod(buffer)));
                buffer = "";
            }

            tokens.push_back(SVGPathToken(c)); // Add the commend to the tokens
        }

        else if(c == ' ' || c == ',') { // If the charactor is a spacing charactor add the buffer to the tokens and clear the buffer
            if(buffer != "") {
                tokens.push_back(SVGPathToken(std::stod(buffer)));
                buffer = "";
            }
        }

        else { // If it's not a command or spacing charactor, add the charactor to the buffer
            buffer += c;
        }
    }

    // Deal with the leftover buffer
    if(buffer != "") { // If the buffer isn't empty push it to the tokens
        tokens.push_back(SVGPathToken(std::stod(buffer)));
    }
}

void SVGPathParser::getPaths() {
    Command currentCommand = Command::none;

    int parameter = 0;

    double startX, startY;

    for(SVGPathToken token : tokens) {
        if(token.getType() == TokenType::CommandToken) {
            currentCommand = token.getCommand();
            if(currentCommand != Command::closepath) {
                parameter = 0;
            }
        }

        else if(currentCommand == Command::moveto) {
            if(parameter == 0) {
                setX(token.getParameter());
                startX = currX;

                parameter = 1;
            } else if(parameter == 1) {
                setY(token.getParameter());
                startY = currY;

                parameter = 0;
                currentCommand = Command::lineto;

                Path path;
                paths.push_back(path);
                currentPath = &paths[paths.size()-1];
            }
        }

        else if(currentCommand == Command::moveto_r) {
            if(parameter == 0) {
                addX(token.getParameter());
                parameter = 1;
            } else if(parameter == 1) {
                addY(token.getParameter());
                parameter = 0;
                currentCommand = Command::lineto_r;

                Path path;
                paths.push_back(path);
                currentPath = &paths[paths.size()-1];
            }
        }

        else if(currentCommand == Command::lineto) {
            if(parameter == 0) {
                setX(token.getParameter());
                parameter = 1;
            } else if(parameter == 1) {
                setY(token.getParameter());
                parameter = 0;

                currentPath->push_back(Line(prevX, prevY, currX, currY));
            }
        } 

        else if(currentCommand == Command::lineto_r) {
            if(parameter == 0) {
                addX(token.getParameter());
                parameter = 1;
            } else if(parameter == 1) {
                addY(token.getParameter());
                parameter = 0;

                currentPath->push_back(Line(prevX, prevY, currX, currY));
            }
        } 
        
        if(currentCommand == Command::closepath) { // Special case for closepath
            if(parameter == 0) {
                currentPath->push_back(Line(currX, currY, startX, startY));
            }
        }
    }
}

void SVGPathParser::setX(double x) {
    prevX = currX;
    currX = x;
}

void SVGPathParser::setY(double y) {
    prevY = currY;
    currY = y;
}

void SVGPathParser::addX(double x) {
    prevX = currX;
    currX += x;
}

void SVGPathParser::addY(double y) {
    prevY = currY;
    currY += y; 
}