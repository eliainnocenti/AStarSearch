//
// Created by Elia Innocenti on 10/10/23.
//

// libraries
#include "gtest/gtest.h"
#include "../Grid.h"

// default constructor test
TEST (Grid, DefaultConstructor) {
    Grid grid;

    // the Grid default constructor must set width = 10 and height = 10
    ASSERT_EQ(10, grid.getWidth());
    ASSERT_EQ(10, grid.getHeight());

    // the Grid default constructor must set diagonal movement bool value to false
    ASSERT_FALSE(grid.isDiagonalMovementAllowed());

    // the Grid default constructor must set random bool value to true
    ASSERT_TRUE(grid.isThisARandomRun());

    // the Grid default constructor must set the density ot the number of obstacles equal to 2.5
    ASSERT_EQ(2.5, grid.getDensity());

    // the Grid default constructor must set the cost between nodes constant and equal to 1
    ASSERT_TRUE(grid.isTheCostConst());
    ASSERT_EQ(1, grid.getCost(Cell(0,0), Cell(1,0))); // must be any two adjacent cells

    // the Grid default constructor must set a valid StartCell
    std::shared_ptr<Cell> startCell = grid.getStartCell();
    int x_s = startCell->getX(); int y_s = startCell->getY();
    ASSERT_TRUE(0 <= x_s && x_s < grid.getHeight() && 0 <= y_s && y_s < grid.getWidth());
    ASSERT_FALSE(startCell->isAnObstacle());

    // the Grid default constructor must set a valid GoalCell
    std::shared_ptr<Cell> goalCell = grid.getGoalCell();
    int x_g = goalCell->getX(); int y_g = goalCell->getY();
    ASSERT_TRUE(0 <= x_g && x_g < grid.getHeight() && 0 <= y_g && y_g < grid.getWidth());
    ASSERT_FALSE(goalCell->isAnObstacle());

    // and the GoalCell and the StartCell must be different
    ASSERT_FALSE(*startCell == *goalCell);
}