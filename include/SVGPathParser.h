#pragma once

#include <vector>
#include <string>

#include "SVGPathToken.h"
#include "Line.h"

typedef std::vector<Line> Path;

class SVGPathParser {
    private:
        double currX, currY;
        double prevX, prevY;

        std::string workingString;
        std::vector<SVGPathToken> tokens;

        Path *currentPath;

        void tokenize();
        void getPaths();

        void setX(double x);
        void setY(double y);
        void addX(double x);
        void addY(double y);

    public:
        void parse(std::string pathData);

        std::vector<Path> paths;
};