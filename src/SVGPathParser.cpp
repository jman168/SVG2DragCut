#include <iostream>

#include "SVGPathParser.h"

void SVGPathParser::parse(std::string path) {
    tokens.clear();

    workingString = path;
    tokenize();

    for(std::string token : tokens) {
        std::cout << token << " : ";
    }
    std::cout << std::endl;
}

void SVGPathParser::tokenize() {
    std::string buffer = "";

    for(char c : workingString) {
        if(getCommand(c) != Command::none) { // If the current charactor is a command
            if(buffer != "") { // If the buffer isn't empty push it to the tokens and clear it
                tokens.push_back(buffer);
                buffer = "";
            }

            // Add the commend to the tokens
            buffer = c;
            tokens.push_back(buffer);

            buffer = ""; // clear the buffer
        }

        else if(c == ' ' || c == ',') { // If the charactor is a spacing charactor add the buffer to the tokens and clear the buffer
            if(buffer != "") {
                tokens.push_back(buffer);
                buffer = "";
            }
        }

        else { // If it's not a command or spacing charactor, add the charactor to the buffer
            buffer += c;
        }
    }

    // Deal with the leftover buffer
    if(buffer != "") { // If the buffer isn't empty push it to the tokens
        tokens.push_back(buffer);
    }
}

Command SVGPathParser::getCommand(char c) {
    Command command = Command::none;
    
    switch (c)
    {
    case 'M':
        command = Command::moveto;
        break;
    case 'm':
        command = Command::moveto_r;
        break;

    case 'Z':
        command = Command::closepath;
        break;
    case 'z':
        command = Command::closepath;
        break;

    case 'L':
        command = Command::lineto;
        break;
    case 'l':
        command = Command::lineto_r;
        break;
    case 'H':
        command = Command::horizontal_lineto;
        break;
    case 'h':
        command = Command::horizontal_lineto_r;
        break;
    case 'V':
        command = Command::vertical_lineto;
        break;
    case 'v':
        command = Command::vertical_lineto_r;
        break;
    }

    return command;
}