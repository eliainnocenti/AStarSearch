#include <iostream>

#include "Grid.h"
#include "Cell.h"

int main() {

    srand(static_cast<unsigned>(time(nullptr)));

    Grid grid(10,10, true);

    Cell start(1,2);
    Cell goal(6,7);

    grid.setAnObstacle(3,1);
    grid.setAnObstacle(3,2);
    grid.setAnObstacle(3,3);
    grid.setAnObstacle(3,4);
    grid.setAnObstacle(3,5);

    //grid.printAllTheObstacles(); // for debugging

    //grid.findPath(start, goal);

    grid.findRandomPath();

    return 0;
}