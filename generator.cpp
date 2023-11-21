#include <iostream>
#include "Grid.hpp"

int main(int argv, char* argc[]) {
    Grid grid;
    grid.fill();
    grid.generate();
    std::cout << grid.toString() << std::endl;
}