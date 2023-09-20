#include <iostream>

#include "Grid.h"
#include "Cell.h"

int main() {

    Grid grid(10,10, true);

    grid.setTheStart(1,2);
    grid.setTheGoal(6,7);

    Cell start(1,2);
    Cell goal(6,7);

    //grid.setAnObstacle(1,6);

    grid.findPath(start, goal);

    return 0;
}