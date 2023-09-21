#include <iostream>

#include "Grid.h"
#include "Cell.h"

int main() {

    Grid grid(10,10, true);

    grid.setTheStart(1,2);
    grid.setTheGoal(6,7);

    Cell start(1,2);
    Cell goal(6,7);

    Cell obstacle1(2,3);

    grid.setAnObstacle(1,6);
    grid.setAnObstacle(3,4);
    grid.setAnObstacle(obstacle1);

    //grid.printAllTheObstacles();

    grid.findPath(start, goal);

    return 0;
}