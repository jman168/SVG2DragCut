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

    double startX, startY, currX = 0.0, currY = 0.0;
    Path *currentPath;
    std::vector<double> parameters;

    for(SVGPathToken token : tokens) {
        if(token.isCommand) { // If the token is a command
            if(token.command != Command::closepath) { // If the command is not a closepath command, clear the parameters (shouldn't be required, bust just for redundancy)
                parameters.clear();
                currentCommand = token.command;
            } else { // If the command is a close path command
                if(parameters.size() != 0) { // If the parameters queue is not empty, append the starting point to it
                    parameters.push_back(startX);
                    parameters.push_back(startY);
                } else { // If the parameters queue is empty, draw a line from the current point to the starting point and clear the current command
                    currentPath->push_back(Line(currX, currY, startX, startY));
                    currentCommand = Command::none;
                }
            }
        } else { // If the token is not a command appent the token to the parameters queue
            parameters.push_back(token.parameter);
        }

        if(currentCommand == Command::moveto) {
            if(parameters.size() == 2) {
                currX = parameters[0];
                currY = parameters[1];

                startX = currX;
                startY = currY;

                currentPath = new Path();
                paths.push_back(currentPath);

                currentCommand = Command::lineto;

                parameters.clear();
            }
        }

        else if(currentCommand == Command::moveto_r) {
            if(parameters.size() == 2) {
                currX += parameters[0];
                currY += parameters[1];

                startX = currX;
                startY = currY;

                currentPath = new Path();
                paths.push_back(currentPath);

                currentCommand = Command::lineto_r;

                parameters.clear();
            }
        }

        else if(currentCommand == Command::lineto) {
            if(parameters.size() == 2) {
                currentPath->push_back(Line(currX, currY, parameters[0], parameters[1]));

                currX = parameters[0];
                currY = parameters[1];

                parameters.clear();
            }
        }

        else if(currentCommand == Command::lineto_r) {
            if(parameters.size() == 2) {
                currentPath->push_back(Line(currX, currY, currX+parameters[0], currY+parameters[1]));

                currX += parameters[0];
                currY += parameters[1];

                parameters.clear();
            }
        }

        else if(currentCommand == Command::horizontal_lineto) {
            if(parameters.size() == 1) {
                currentPath->push_back(Line(currX, currY, parameters[0], currY));

                currX = parameters[0];

                parameters.clear();
            }
        }

        else if(currentCommand == Command::horizontal_lineto_r) {
            if(parameters.size() == 1) {
                currentPath->push_back(Line(currX, currY, currX+parameters[0], currY));

                currX += parameters[0];

                parameters.clear();
            }
        }

        else if(currentCommand == Command::vertical_lineto) {
            if(parameters.size() == 1) {
                currentPath->push_back(Line(currX, currY, currX, parameters[0]));

                currY = parameters[0];

                parameters.clear();
            }
        }

        else if(currentCommand == Command::vertical_lineto_r) {
            if(parameters.size() == 1) {
                currentPath->push_back(Line(currX, currY, currX, currY+parameters[0]));

                currY += parameters[0];

                parameters.clear();
            }
        }

        else if(currentCommand == Command::quadratic_curveto_r) {
            if(parameters.size() == 4) {
                double P0x = currX;
                double P0y = currY;
                double P1x = currX+parameters[0];
                double P1y = currY+parameters[1];
                double P2x = currX+parameters[2];
                double P2y = currY+parameters[3];

                double lastX = currX;
                double lastY = currY;

                for(double t = 0.05; t <= 1.0; t+=0.05) {
                    double C0 = (1-t)*(1-t);
                    double C1 = 2*(1-t)*t;
                    double C2 = t*t;

                    double newX = C0*P0x + C1*P1x + C2*P2x;
                    double newY = C0*P0y + C1*P1y + C2*P2y;

                    currentPath->push_back(Line(lastX, lastY, newX, newY));
                    lastX = newX;
                    lastY = newY;
                }

                currX = lastX;
                currY = lastY;

                parameters.clear();
            }
        }
    }
}