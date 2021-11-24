# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 2.8.11)
project (SVG2DRAGCUT)

include_directories(include)

# Add executable called "SVG2DragCut" that is built from the source files
# "demo.cxx" and "demo_b.cxx". The extensions are automatically found.
add_executable (SVG2DragCut
    include/SVGPathParser.h
    include/SVGPathToken.h

    src/SVGPathParser.cpp
    src/SVGPathToken.cpp

    src/SVG2DragCut.cpp
)