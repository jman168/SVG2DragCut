#include "SVGPathParser.h"

void SVGPathParser::parse(std::string path) {
    tokens.clear();

    workingString = path;
    tokenize();
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