//
// Created by Elia Innocenti on 10/10/23.
//

// libraries
#include "gtest/gtest.h"
#include "../AStarSearch.h"

// default constructor test
TEST (AStarSearch, DefaultConstructor) {
    AStarSearch a_star_search;

    // the AStarSearch default constructor must set the pointer to the grid to nullptr
    ASSERT_EQ(nullptr, a_star_search.getGridPointer());

    // the AStarSearch default constructor must set the default directions to North, East, South and West
    std::unordered_set<Cell> default_directions { Cell{0,1},  Cell{1,0}, Cell{0,-1}, Cell{-1,0} };
    ASSERT_EQ(default_directions, a_star_search.getDirections());
}

// TODO - put some comments
TEST (AstarSearch, NoPath) {
    Grid grid(10,10,false,false);
    AStarSearch a_star_search(grid);

    grid.setTheStart(1,1);
    grid.setTheGoal(9,9);

    for (int i = 0; i < grid.getHeight(); i++)
        grid.setAnObstacle(i,4);

    a_star_search.findPath();

    for (int i = 0; i < grid.getHeight(); i++)
        for (int j = 0; j < grid.getWidth(); j++)
            EXPECT_FALSE((*grid.getCell(i,j)).isAPathElement());
}

// TODO - put some comments
TEST (AStarSearch, PathNoDiagonalMovement) {
    Grid grid(10,10, false, false);
    AStarSearch a_star_search(grid);

    grid.setTheStart(6,2);
    grid.setTheGoal(4,9);

    // TODO
    grid.setAnObstacle(0,2);
    grid.setAnObstacle(0,5);
    grid.setAnObstacle(0,9);
    grid.setAnObstacle(0,2);
    grid.setAnObstacle(0,2);
    grid.setAnObstacle(0,2);
    grid.setAnObstacle(0,2);
    grid.setAnObstacle(0,2);
    grid.setAnObstacle(0,2);
    grid.setAnObstacle(0,2);
    grid.setAnObstacle(0,2);
    grid.setAnObstacle(0,2);
    grid.setAnObstacle(0,2);
    grid.setAnObstacle(0,2);
    grid.setAnObstacle(0,2);
    grid.setAnObstacle(0,2);
    grid.setAnObstacle(0,2);
    grid.setAnObstacle(0,2);
    grid.setAnObstacle(0,2);
    grid.setAnObstacle(0,2);
    grid.setAnObstacle(0,2);
    grid.setAnObstacle(0,2);
    grid.setAnObstacle(0,2);
    grid.setAnObstacle(0,2);
    grid.setAnObstacle(0,2);
    grid.setAnObstacle(0,2);
    grid.setAnObstacle(0,2);
    grid.setAnObstacle(0,2);
    grid.setAnObstacle(0,2);
    grid.setAnObstacle(0,2);
    grid.setAnObstacle(0,2);
    grid.setAnObstacle(0,2);

    a_star_search.findPath();

    std::vector<Cell> path { Cell{6,2}, Cell{6,3}, Cell{7,3}, Cell{7,4}, Cell{7,5},
                             Cell{6,5}, Cell{5,5}, Cell{4,5}, Cell{4,6}, Cell{4,7},
                             Cell{4,8}, Cell{4,9} };

    for (const auto& it : path)
        EXPECT_TRUE((*grid.getCell(it.getX(),it.getY())).isAPathElement());
}


// path with diagonal movement // TODO