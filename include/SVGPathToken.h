#pragma once

enum Command {none = -1, moveto, moveto_r, closepath, lineto, lineto_r, horizontal_lineto, horizontal_lineto_r, vertical_lineto, vertical_lineto_r};
enum TokenType {CommandToken, ParameterToken};

class SVGPathToken {
    private:
        Command _command;
        char _commandC;
        double _parameter;
        TokenType _type;

    public:
        SVGPathToken(char command);
        SVGPathToken(double parameter);

        TokenType getType();
        Command getCommand();
        double getParameter();

        static Command getCommandFromChar(char c);
};