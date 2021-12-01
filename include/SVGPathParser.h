#pragma once

#include <vector>
#include <string>

#include "SVGPathToken.h"
#include "Line.h"

typedef std::vector<Line> Path;

class SVGPathParser {
    private:
        std::string workingString;
        std::vector<SVGPathToken> tokens;

        void tokenize();
        void getPaths();

    public:
        void parse(std::string pathData);

        std::vector<Path *> paths;
};