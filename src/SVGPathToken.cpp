#include "SVGPathToken.h"

SVGPathToken::SVGPathToken(char _command) {
    isCommand = true;
    command = getCommandFromChar(_command);
}

SVGPathToken::SVGPathToken(double _parameter) {
    isCommand = false;
    parameter = _parameter;
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

    case 'C':
        command = Command::curveto;
        break;
    case 'c':
        command = Command::curveto_r;
        break;

    case 'S':
        command = Command::smooth_curveto;
        break;
    case 's':
        command = Command::smooth_curveto_r;
        break;

    case 'Q':
        command = Command::quadratic_curveto;
        break;
    case 'q':
        command = Command::quadratic_curveto_r;
        break;
    
    case 'T':
        command = Command::smooth_quadratic_curveto;
        break;
    case 't':
        command = Command::smooth_quadratic_curveto_r;
        break;

    case 'A':
        command = Command::elliptical_arc;
        break;
    case 'a':
        command = Command::elliptical_arc_r;
        break;

    case 'R':
        command = Command::catmull_rom;
        break;
    case 'r':
        command = Command::catmull_rom_r;
        break;

    case 'B':
        command = Command::bearing;
        break;
    case 'b':
        command = Command::bearing_r;
        break;
    }

    return command;
}