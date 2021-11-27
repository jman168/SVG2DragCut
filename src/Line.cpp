#include "Line.h"

Line::Line(double x1, double y1, double x2, double y2) {
    p1.x = x1;
    p1.y = y1;
    p2.x = x2;
    p2.y = y2;
}

Line::Line(LPoint _p1, LPoint _p2) {
    p1 = _p1;
    p2 = _p2;
}