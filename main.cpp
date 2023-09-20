#include <iostream>

#include "Grid.h"
#include "Cell.h"

std::array<Cell, 4> Grid::DIRS = {
        // East, West, North, South
        Cell{1, 0}, Cell{-1, 0},
        Cell{0, -1}, Cell{0, 1}
};

int main() {

    Grid grid(10,10);

    grid.setTheStart(1,2);
    grid.setTheGoal(6,7);

    Cell start(1,2);
    Cell goal(6,7);

    //grid.setAnObstacle(1,6);

    grid.findPath(start, goal);

    return 0;
}