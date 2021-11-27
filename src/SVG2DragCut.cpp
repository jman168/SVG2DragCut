#include <iostream>
#include <iomanip>
#include <math.h>

#include "SVGPathParser.h"

#define CUTTER_OFFSET 0.25
#define DROP -1.5

double normalizeAngle(double theta) {
    return fmod(theta+2*M_PI, 2*M_PI);
}

int main() {
    SVGPathParser parser;

    std::cout << std::fixed;

    parser.parse("M 7.5508535,10.609433 4.5912579,8.353455 1.0549982,9.51255 2.2859954,6.0006725 0.09086558,2.99567 3.8112587,3.0811878 5.9908541,0.06489859 7.0591863,3.6296291 10.601379,4.770463 7.5412527,6.8880695 Z");

    for(std::vector<Line> path : parser.paths) {
        double theta = normalizeAngle(atan2(path[0].p2.y-path[0].p1.y, path[0].p2.x-path[0].p1.x));

        double x1 = path[0].p1.x + cos(theta)*CUTTER_OFFSET;
        double y1 = path[0].p1.y + sin(theta)*CUTTER_OFFSET;

        std::cout << "G0 Z0\n";
        std::cout << "G0 X" << x1 << " Y"  << y1 << "\n";
        std::cout << "G0 Z" << DROP << "\n";

        for(int i = 0; i < path.size(); i++) {
            Line line = path[i];
            double theta = normalizeAngle(atan2(line.p2.y-line.p1.y, line.p2.x-line.p1.x));

            double x1 = line.p1.x + cos(theta)*CUTTER_OFFSET;
            double y1 = line.p1.y + sin(theta)*CUTTER_OFFSET;

            double x2 = line.p2.x + cos(theta)*CUTTER_OFFSET;
            double y2 = line.p2.y + sin(theta)*CUTTER_OFFSET;

            std::cout << "G1 X" << x2 << " Y"  << y2 << "\n";

            if(i+1 < path.size()) {
                Line nextLine = path[i+1];
                double theta1 = normalizeAngle(atan2(line.p2.y-line.p1.y, line.p2.x-line.p1.x)+M_PI);
                double theta2 = normalizeAngle(atan2(nextLine.p2.y-nextLine.p1.y, nextLine.p2.x-nextLine.p1.x));
                double diffTheta;

                if(theta2 - theta1 > 0) {
                    diffTheta = theta2 - theta1;
                } else {
                    diffTheta = 2*M_PI+theta2-theta1;
                }

                double ax = nextLine.p1.x + cos(theta2)*CUTTER_OFFSET;
                double ay = nextLine.p1.y + sin(theta2)*CUTTER_OFFSET;

                if(diffTheta > M_PI) {
                    std::cout << "G3 R" << CUTTER_OFFSET << " X" << ax << " Y" << ay << "\n";
                } else {
                    std::cout << "G2 R" << CUTTER_OFFSET << " X" << ax << " Y" << ay << "\n";
                }
            }
        }
    }

    std::cout << "G0 Z0\n";
    std::cout << "G0 X0 Y0\n";
}