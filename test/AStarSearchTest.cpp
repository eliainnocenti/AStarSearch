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

// no path run test
TEST (AstarSearch, NoPath) {
    Grid grid(10,10,false,false);
    AStarSearch a_star_search(grid);

    // setters
    grid.setTheStart(1,1);
    grid.setTheGoal(9,9);

    // add obstacles in a vertical line at column 4
    for (int i = 0; i < grid.getHeight(); i++)
        grid.setAnObstacle(i,4);

    a_star_search.findPath(); // find the path

    // there must not be a path
    for (int i = 0; i < grid.getHeight(); i++)
        for (int j = 0; j < grid.getWidth(); j++)
            // this cell must have the path boolean value set to false
            EXPECT_FALSE((*grid.getCell(i,j)).isAPathElement());
}

// path with no diagonal movements run test
TEST (AStarSearch, PathNoDiagonalMovement) {
    Grid grid(10,10, false, false);
    AStarSearch a_star_search(grid);

    // setters
    grid.setTheStart(6,2);
    grid.setTheGoal(4,9);

    // setters
    grid.setAnObstacle(0,2);
    grid.setAnObstacle(0,5);
    grid.setAnObstacle(0,9);
    grid.setAnObstacle(1,1);
    grid.setAnObstacle(1,3);
    grid.setAnObstacle(1,6);
    grid.setAnObstacle(1,9);
    grid.setAnObstacle(2,1);
    grid.setAnObstacle(2,7);
    grid.setAnObstacle(2,9);
    grid.setAnObstacle(3,1);
    grid.setAnObstacle(3,2);
    grid.setAnObstacle(3,7);
    grid.setAnObstacle(4,1);
    grid.setAnObstacle(4,2);
    grid.setAnObstacle(4,4);
    grid.setAnObstacle(5,3);
    grid.setAnObstacle(5,6);
    grid.setAnObstacle(5,7);
    grid.setAnObstacle(5,8);
    grid.setAnObstacle(5,9);
    grid.setAnObstacle(6,1);
    grid.setAnObstacle(6,4);
    grid.setAnObstacle(6,7);
    grid.setAnObstacle(7,1);
    grid.setAnObstacle(8,2);
    grid.setAnObstacle(8,8);
    grid.setAnObstacle(8,9);
    grid.setAnObstacle(9,2);
    grid.setAnObstacle(9,4);
    grid.setAnObstacle(9,8);

    a_star_search.findPath(); // find the path

    std::vector<Cell> path { Cell{6,2}, Cell{6,3}, Cell{7,3}, Cell{7,4}, Cell{7,5},
                             Cell{6,5}, Cell{5,5}, Cell{4,5}, Cell{4,6}, Cell{4,7},
                             Cell{4,8}, Cell{4,9} };

    // every path cells (except the start and the goal) must have the path boolean value set to true
    for (const auto& it : path)
        if (!(*grid.getCell(it.getX(),it.getY())).isTheStart() && !(*grid.getCell(it.getX(),it.getY())).isTheGoal())
            // this cell must have the path boolean value set to true
            EXPECT_TRUE((*grid.getCell(it.getX(),it.getY())).isAPathElement());
}

// path with no diagonal movements run test
TEST (AStarSearch, PathDiagonalMovement) {
    Grid grid(10,10, true, false);
    AStarSearch a_star_search(grid);

    // setters
    grid.setTheStart(2,7);
    grid.setTheGoal(9,7);

    // setters
    grid.setAnObstacle(0,5);
    grid.setAnObstacle(0,7);
    grid.setAnObstacle(0,9);
    grid.setAnObstacle(1,6);
    grid.setAnObstacle(1,7);
    grid.setAnObstacle(2,3);
    grid.setAnObstacle(3,3);
    grid.setAnObstacle(3,4);
    grid.setAnObstacle(3,6);
    grid.setAnObstacle(3,8);
    grid.setAnObstacle(3,9);
    grid.setAnObstacle(4,1);
    grid.setAnObstacle(4,2);
    grid.setAnObstacle(4,3);
    grid.setAnObstacle(4,9);
    grid.setAnObstacle(5,4);
    grid.setAnObstacle(5,6);
    grid.setAnObstacle(6,3);
    grid.setAnObstacle(6,4);
    grid.setAnObstacle(6,5);
    grid.setAnObstacle(6,6);
    grid.setAnObstacle(6,7);
    grid.setAnObstacle(7,1);
    grid.setAnObstacle(7,8);
    grid.setAnObstacle(7,9);
    grid.setAnObstacle(8,2);
    grid.setAnObstacle(8,4);
    grid.setAnObstacle(8,7);

    a_star_search.findPath(); // find the path

    std::vector<Cell> path { Cell{2,7}, Cell{2,6}, Cell{2,5}, Cell{1,4}, Cell{1,3},
                             Cell{1,2}, Cell{2,1}, Cell{3,0}, Cell{4,0}, Cell{5,0},
                             Cell{6,1}, Cell{7,2}, Cell{7,3}, Cell{7,4}, Cell{7,5},
                             Cell{8,6}, Cell{9,6}, Cell{9,7} };

    // every path cells (except the start and the goal) must have the path boolean value set to true
    for (const auto& it : path)
        if (!(*grid.getCell(it.getX(),it.getY())).isTheStart() && !(*grid.getCell(it.getX(),it.getY())).isTheGoal())
            // this cell must have the path boolean value set to true
            EXPECT_TRUE((*grid.getCell(it.getX(),it.getY())).isAPathElement());
}