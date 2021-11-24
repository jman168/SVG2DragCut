#pragma once

#include <vector>
#include <string>

#include "SVGPathToken.h"

class SVGPathParser {
    private:
        std::string workingString;
        std::vector<SVGPathToken> tokens;

        void tokenize();

    public:
        void parse(std::string path);
};