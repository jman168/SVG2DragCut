#include "SVGPathToken.h"

SVGPathToken::SVGPathToken(char command) {
    _type = TokenType::CommandToken;
    _command = getCommandFromChar(command);
    _commandC = command;
}

SVGPathToken::SVGPathToken(double parameter) {
    _type = TokenType::ParameterToken;
    _parameter = parameter;
}

TokenType SVGPathToken::SVGPathToken::getType() {
    return _type;
}

Command SVGPathToken::getCommand() {
    return _command;
}

double SVGPathToken::getParameter() {
    return _parameter;
}

Command SVGPathToken::getCommandFromChar(char c) {
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