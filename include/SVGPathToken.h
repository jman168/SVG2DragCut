#pragma once

enum Command {none = -1, 
    moveto, moveto_r, 
    closepath, 
    lineto, lineto_r, 
    horizontal_lineto, horizontal_lineto_r, vertical_lineto, vertical_lineto_r,
    curveto, curveto_r,
    smooth_curveto, smooth_curveto_r,
    quadratic_curveto, quadratic_curveto_r,
    smooth_quadratic_curveto, smooth_quadratic_curveto_r,
    elliptical_arc, elliptical_arc_r,
    catmull_rom, catmull_rom_r,
    bearing, bearing_r};

struct SVGPathToken {
    bool isCommand;
    Command command;
    double parameter;

    SVGPathToken(char _command);
    SVGPathToken(double _parameter);

    static Command getCommandFromChar(char c);
};