#include <iostream>
#include <iomanip>

#include "SVGPathParser.h"

int main() {
    SVGPathParser parser;

    parser.parse("M 100 100 L 200 200");
    parser.parse("M100 100L200 200");
    parser.parse("M 100 100 200 100 L 200 200");
    parser.parse("M100,100 200,100 L200 200");
    parser.parse("M 100 200 L 200 100 L -100 -200");
    parser.parse("M 100 200 L 200 100 -100 -200");
}