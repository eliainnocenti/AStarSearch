//
// Created by Elia Innocenti on 10/10/23.
//

// libraries
#include "gtest/gtest.h"
#include "../Grid.h"
#include "../AStarSearch.h"

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
    ASSERT_TRUE(grid.in_bounds(*startCell));
    ASSERT_FALSE(startCell->isAnObstacle());

    // the Grid default constructor must set a valid GoalCell
    std::shared_ptr<Cell> goalCell = grid.getGoalCell();
    ASSERT_TRUE(grid.in_bounds(*goalCell));
    ASSERT_FALSE(goalCell->isAnObstacle());

    // and the GoalCell and the StartCell must be different
    ASSERT_FALSE(*startCell == *goalCell);
}

// in bounds test
TEST (Grid, InBounds1) { // in_bounds(const Cell& cell)
    Grid grid; // width = 10, height = 10

    // setters
    Cell in_bound(5,6);
    Cell out_of_bound_x(11,9);
    Cell out_of_bound_y(7,13);
    Cell out_of_bound_xy(20,33);

    // this value must be in bounds
    ASSERT_TRUE(grid.in_bounds(in_bound));
    // these values must be out of bounds
    ASSERT_FALSE(grid.in_bounds(out_of_bound_x));
    ASSERT_FALSE(grid.in_bounds(out_of_bound_y));
    ASSERT_FALSE(grid.in_bounds(out_of_bound_xy));
}

// in bounds test
TEST (Grid, InBounds2) { // in_bounds(const int x, const int y)
    Grid grid; // width = 10, height = 10

    // this value must be in bounds
    ASSERT_TRUE(grid.in_bounds(5,6));
    // these values must be out of bounds
    ASSERT_FALSE(grid.in_bounds(11,9));
    ASSERT_FALSE(grid.in_bounds(7,13));
    ASSERT_FALSE(grid.in_bounds(20,33));
}

// passable test
TEST (Grid, Passable1) { // passable(const Cell& cell)
    Grid grid(10,10,false, false);

    // setters
    Cell freeCell(1,1);
    Cell obstacle(2,4);
    grid.setAnObstacle(obstacle);

    // this value must not be an obstacle
    ASSERT_TRUE(grid.passable(freeCell));
    // this value must be an obstacle
    ASSERT_FALSE(grid.passable(obstacle));
}

// passable test
TEST (Grid, Passable2) { // passable(const int x, const int y)
    Grid grid(10,10,false, false);

    // setter
    grid.setAnObstacle(2,4);

    // this value must not be an obstacle
    ASSERT_TRUE(grid.passable(1,1));
    // this value must be an obstacle
    ASSERT_FALSE(grid.passable(2,4));
}

// diagonal direction test
TEST (Grid, DiagonalDirection) {
    Grid grid;

    // diagonal directions
    Cell NE(-1,1);
    Cell NW(-1,-1);
    Cell SE(1,1);
    Cell SW(1,-1);

    // other directions
    Cell N(-1,0);
    Cell E(0,1);
    Cell S(1,0);
    Cell W(0,-1);

    // these directions must be diagonal directions
    ASSERT_TRUE(grid.isThisADiagonalMovements(NE));
    ASSERT_TRUE(grid.isThisADiagonalMovements(NW));
    ASSERT_TRUE(grid.isThisADiagonalMovements(SE));
    ASSERT_TRUE(grid.isThisADiagonalMovements(SW));

    // these directions must not be diagonal directions
    ASSERT_FALSE(grid.isThisADiagonalMovements(N));
    ASSERT_FALSE(grid.isThisADiagonalMovements(E));
    ASSERT_FALSE(grid.isThisADiagonalMovements(S));
    ASSERT_FALSE(grid.isThisADiagonalMovements(W));
}

// diagonal movement test
TEST (Grid, DiagonalMovement0) {
    Grid grid(5,5,true, false);

    // NW direction
    Cell current1(1,1);
    Cell NW(-1,-1);
    grid.setAnObstacle(1,0);
    grid.setAnObstacle(0,1);

    // NE direction
    Cell current2(1,3);
    Cell NE(-1,1);
    grid.setAnObstacle(0,3);
    grid.setAnObstacle(1,4);

    // SW direction
    Cell current3(3,1);
    Cell SW(1,-1);
    grid.setAnObstacle(3,0);
    grid.setAnObstacle(4,1);

    // SE direction
    Cell current4(3,3);
    Cell SE(1,1);
    grid.setAnObstacle(3,4);
    grid.setAnObstacle(4,3);

    // these diagonal movements must be illegal cause these are movements through the wall
    ASSERT_FALSE(grid.isThisAValidDiagonalCell(current1,NW));
    ASSERT_FALSE(grid.isThisAValidDiagonalCell(current2,NE));
    ASSERT_FALSE(grid.isThisAValidDiagonalCell(current3,SW));
    ASSERT_FALSE(grid.isThisAValidDiagonalCell(current4,SE));
}

// draw function test
TEST (Grid, Draw) {
    Grid grid;

    // graphics
    sf::RenderWindow window;
    grid.draw(window);

    for (int i = 0; i < grid.getHeight(); i++) {
        for (int j = 0; j < grid.getWidth(); j++) {

            // the start cell must be green
            if ((*grid.getCell(i,j)).isTheStart())
                EXPECT_EQ(sf::Color::Green, (*grid.getCell(i,j)).getShape().getFillColor());

            // the goal cell must be red
            else if ((*grid.getCell(i,j)).isTheGoal())
                EXPECT_EQ(sf::Color::Red, (*grid.getCell(i,j)).getShape().getFillColor());

            // a path cell must be blue
            else if ((*grid.getCell(i,j)).isAPathElement())
                EXPECT_EQ(sf::Color::Blue, (*grid.getCell(i,j)).getShape().getFillColor());

            // a visited cell must be cyan
            else if ((*grid.getCell(i,j)).isVisited())
                EXPECT_EQ(sf::Color::Cyan, (*grid.getCell(i,j)).getShape().getFillColor());

            // an obstacle cell must be black
            else if ((*grid.getCell(i,j)).isAnObstacle())
                EXPECT_EQ(sf::Color::Black, (*grid.getCell(i,j)).getShape().getFillColor());

            // a free cell must be white
            else
                EXPECT_EQ(sf::Color::White, (*grid.getCell(i,j)).getShape().getFillColor());
        }
    }

}

// update cell function test
TEST (Grid, UpdateCell) {
    Grid grid(5,5,false,false);

    grid.updateCell(1,1); // free cell -> obstacle

    // this cell mus be an obstacle
    ASSERT_TRUE((*grid.getCell(1,1)).isAnObstacle());

    grid.updateCell(1,1); // obstacle -> free cell

    // this cell must be a free cell
    ASSERT_FALSE((*grid.getCell(1,1)).isAnObstacle());

}

// set the path function test
TEST (Grid, SetThePath) {
    Grid grid(5,5,false, false);
    AStarSearch a_star_search(grid);

    // setters
    grid.setTheStart(0,0);
    grid.setTheGoal(4,0);

    a_star_search.findPath(); // find the path and set the path cells

    std::vector<Cell> path { Cell{0,0}, Cell{1,0}, Cell{2,0}, Cell{3,0}, Cell{4,0} };

    // every path cells (except the start and the goal) must have the path boolean value set to true
    for (const auto& it : path) {
        if(!(grid.getCell(it.getX(),it.getY())->isTheStart()) && !(grid.getCell(it.getX(),it.getY())->isTheGoal()))
            // this cell must have the path boolean value set to true
            EXPECT_TRUE((*grid.getCell(it.getX(),it.getY())).isAPathElement());
    }
}

// reset path drawn function test
TEST (Grid, ResetPathDrawn) {
    Grid grid;
    AStarSearch a_star_search(grid);

    a_star_search.findPath(); // find the path and set the path cells

    grid.resetPathDrawn(); // set the path cells and the visited cells as free cells

    for (int i = 0; i < grid.getHeight(); i++)
        for (int j = 0; j < grid.getWidth(); j++) {
            // this cell must have the path boolean value set to false
            EXPECT_FALSE((*grid.getCell(i,j)).isAPathElement());
            // this cell must have the visited boolean value set to false
            EXPECT_FALSE((*grid.getCell(i,j)).isVisited());
        }
}

// reset() // TODO