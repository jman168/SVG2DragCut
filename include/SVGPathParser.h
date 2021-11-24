#pragma once

#include <vector>
#include <string>

enum Command {none = -1, moveto, moveto_r, closepath, lineto, lineto_r, horizontal_lineto, horizontal_lineto_r, vertical_lineto, vertical_lineto_r};

class SVGPathParser {
    private:
        std::string workingString;
        std::vector<std::string> tokens;

        void tokenize();

        Command getCommand(char c);

    public:
        void parse(std::string path);
};