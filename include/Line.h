#pragma once

#include <iostream>

struct LPoint {
    double x, y;
};

class Line {
    public:
        LPoint p1, p2;

    public:
        Line(double x1, double y1, double x2, double y2);
        Line(LPoint _p1, LPoint _p2);
};