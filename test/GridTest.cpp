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

// TODO - put some comments
TEST (Grid, InBounds1) { // in_bounds(const Cell& cell)
    Grid grid; // width = 10, height = 10

    Cell in_bound(5,6);
    Cell out_of_bound_x(11,9);
    Cell out_of_bound_y(7,13);
    Cell out_of_bound_xy(20,33);

    ASSERT_TRUE(grid.in_bounds(in_bound));
    ASSERT_FALSE(grid.in_bounds(out_of_bound_x));
    ASSERT_FALSE(grid.in_bounds(out_of_bound_y));
    ASSERT_FALSE(grid.in_bounds(out_of_bound_xy));
}

// TODO - put some comments
TEST (Grid, InBounds2) { // in_bounds(const int x, const int y)
    Grid grid; // width = 10, height = 10

    ASSERT_TRUE(grid.in_bounds(5,6));
    ASSERT_FALSE(grid.in_bounds(11,9));
    ASSERT_FALSE(grid.in_bounds(7,13));
    ASSERT_FALSE(grid.in_bounds(20,33));
}

// TODO - put some comments
TEST (Grid, Passable1) { // passable(const Cell& cell)
    Grid grid(10,10,false, false);

    Cell freeCell(1,1);
    Cell obstacle(2,4);
    grid.setAnObstacle(obstacle);

    ASSERT_TRUE(grid.passable(freeCell));
    ASSERT_FALSE(grid.passable(obstacle));
}

// TODO - put some comments
TEST (Grid, Passable2) { // passable(const int x, const int y)
    Grid grid(10,10,false, false);

    grid.setAnObstacle(2,4);

    ASSERT_TRUE(grid.passable(1,1));
    ASSERT_FALSE(grid.passable(2,4));
}

// TODO - put some comments
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

    ASSERT_TRUE(grid.isThisADiagonalMovements(NE));
    ASSERT_TRUE(grid.isThisADiagonalMovements(NW));
    ASSERT_TRUE(grid.isThisADiagonalMovements(SE));
    ASSERT_TRUE(grid.isThisADiagonalMovements(SW));

    ASSERT_FALSE(grid.isThisADiagonalMovements(N));
    ASSERT_FALSE(grid.isThisADiagonalMovements(E));
    ASSERT_FALSE(grid.isThisADiagonalMovements(S));
    ASSERT_FALSE(grid.isThisADiagonalMovements(W));
}

// TODO - put some comments
TEST (Grid, DiagonalMovement0) { // particular case with 2 obstacles, movements through the wall
                                 // questo test esplora solo gli assert_false
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

    ASSERT_FALSE(grid.isThisAValidDiagonalCell(current1,NW));
    ASSERT_FALSE(grid.isThisAValidDiagonalCell(current2,NE));
    ASSERT_FALSE(grid.isThisAValidDiagonalCell(current3,SW));
    ASSERT_FALSE(grid.isThisAValidDiagonalCell(current4,SE));
}


// TODO
// da qui in poi si esplora tutti i possibile movimenti diagonali (quindi assert_true)
// se si considera quindi il movimento attraverso i muri illegale, molti pattern si ripresentano a prescindere
// dal numero di ostacoli (per fortuna). quindi non vengono esplorati tutti tutti i casi per ogni numero di ostacoli, ma
// in generale verranno analizzati comunque tutti i pattern

TEST (Grid, DiagonalMovement1) { // 1 obstacle in every direction // TODO
    Grid grid(10,10,true, false);

    // obstacle on W and movement NW

    // obstacle on W and movement SW

    // obstacle on W and movement NE

    // obstacle on W and movement SE


    // obstacle on E and movement NW

    // obstacle on E and movement SW

    // obstacle on E and movement NE

    // obstacle on E and movement SE


    // obstacle on N and movement NW

    // obstacle on N and movement SW

    // obstacle on N and movement NE

    // obstacle on N and movement SE


    // obstacle on S and movement NW

    // obstacle on S and movement SW

    // obstacle on S and movement NE

    // obstacle on S and movement SE


    // obstacle on NE and movement NW

    // obstacle on NE and movement SW

    // obstacle on NE and movement SE


    // obstacle on SE and movement NW

    // obstacle on SE and movement SW

    // obstacle on SE and movement NE


    // obstacle on SW and movement NW

    // obstacle on SW and movement NE

    // obstacle on SW and movement SE


    // obstacle on NW and movement NE

    // obstacle on NW and movement SW

    // obstacle on NW and movement SE

}

TEST (Grid, DiagonalMovement2) { // 2 obstacle in every direction // TODO

    // obstacle on W,SW and movement NW

    // obstacle on W,SW and movement NE

    // obstacle on W,SW and movement SE


    // obstacle on W,NW and movement SW

    // obstacle on W,NW and movement NE

    // obstacle on W,NW and movement SE


    // obstacle on E,SE and movement NE

    // obstacle on E,SE and movement NW

    // obstacle on E,SE and movement SW


    // obstacle on E,NE and movement SE

    // obstacle on E,NE and movement NW

    // obstacle on E,NE and movement SW


    // obstacle on N,NW and movement NE

    // obstacle on N,NW and movement SE

    // obstacle on N,NW and movement SW


    // obstacle on N,NE and movement NW

    // obstacle on N,NE and movement SE

    // obstacle on N,NE and movement SW


    // obstacle on S,SW and movement SE

    // obstacle on S,SW and movement NE

    // obstacle on S,SW and movement NW


    // obstacle on S,SE and movement SW

    // obstacle on S,SE and movement NE

    // obstacle on S,SE and movement NW

    //----------------------------------

    // obstacle on NW,NE and movement SE

    // obstacle on NW,NE and movement SW


    // obstacle on NW,SW and movement NE

    // obstacle on NW,SW and movement SE


    // obstacle on SW,SE and movement NE

    // obstacle on SW,SE and movement NW


    // obstacle on SE,NE and movement NW

    // obstacle on SE,NE and movement SW

    //----------------------------------

    // obstacle on NE,SW and movement NW

    // obstacle on NE,SW and movement SE

    // obstacle on NW,SE and movement NE

    // obstacle on NW,SE and movement SW

    //----------------------------------

    // obstacle on NW,S and movement NE

    // obstacle on NW,S and movement SE

    // obstacle on NW,S and movement SW


    // obstacle on NE,W and movement NW

    // obstacle on NE,W and movement SE

    // obstacle on NE,W and movement SW


    // obstacle on SE,N and movement NW

    // obstacle on SE,N and movement SE

    // obstacle on SE,N and movement SW


    // obstacle on SW,E and movement NW

    // obstacle on SW,E and movement SE

    // obstacle on SW,E and movement NE

    //----------------------------------

    // obstacle on NW,E and movement NE

    // obstacle on NW,E and movement SE

    // obstacle on NW,E and movement SW


    // obstacle on NE,S and movement NW

    // obstacle on NE,S and movement SE

    // obstacle on NE,S and movement SW


    // obstacle on SE,W and movement NW

    // obstacle on SE,W and movement NE

    // obstacle on SE,W and movement SW


    // obstacle on SW,N and movement NW

    // obstacle on SW,N and movement NE

    // obstacle on SW,N and movement SE

}

TEST (Grid, DiagonalMovement3) { // 3 obstacle in every direction // TODO

    // obstacle on N,SE,SW and movement

    // obstacle on N,SE,SW and movement


    // TODO


    //----------------------------------

    // obstacle on N,SW,S and movement

    // obstacle on N,SW,S and movement

    // obstacle on N,SW,S and movement


    // TODO


    //----------------------------------

    // obstacle on N,SE,S and movement

    // obstacle on N,SE,S and movement

    // obstacle on N,SE,S and movement


    // TODO


    //----------------------------------

    // obstacle on N,SW,W and movement

    // obstacle on N,SW,W and movement


    //TODO


    //----------------------------------

    // obstacle on N,SE,E and movement

    // obstacle on N,SE,E and movement


    // TODO


    //----------------------------------

    // obstacle on N,E,SW and movement

    // obstacle on N,E,SW and movement


    // obstacle on E,S,NW and movement

    // obstacle on E,S,NW and movement


    // obstacle on S,W,NE and movement

    // obstacle on S,W,NE and movement


    // obstacle on W,N,SE and movement

    // obstacle on W,N,SE and movement

    //----------------------------------

    // obstacle on SW,NW,NE and movement SE

    // obstacle on NW,NE,SE and movement SW

    // obstacle on NE,SE,SW and movement NW

    // obstacle on SE,SW,NW and movement NE


}

TEST (Grid, DiagonalMovement5) { // 5 obstacle in every direction // TODO

    // obstacle on W,NW,N,NE,E and movement SW

    // obstacle on W,NW,N,NE,E and movement SE


    // obstacle on N,NE,E,SE,S and movement NW

    // obstacle on N,NE,E,SE,S and movement SW


    // obstacle on E,SE,S,SW,W and movement NE

    // obstacle on E,SE,S,SW,W and movement NW


    // obstacle on S,SW,W,NW,N and movement SE

    // obstacle on S,SW,W,NW,N and movement NE


    // if the patter is like: obstacle on SW,W,N,NE,E -> DiagonalMovement 6
}

TEST (Grid, DiagonalMovement6) { // 6 obstacle in every direction // TODO

    // obstacle on NW,N,NE,E,SE,S and movement SW (W free)

    // obstacle on N,NE,E,SE,S,SW and movement NW (W free)

    // obstacle on SE,S,SW,W,NW,N and movement NE (E free)

    // obstacle on S,SW,W,NW,N,NE and movement SE (E free)

    // obstacle on W,NW,N,NE,E,SE and movement SW (S free)

    // obstacle on NE,E,SE,S,SW,W and movement NW (N free)

    // obstacle on E,SE,S,SW,W,NW and movement NE (N free)

    // obstacle on SW,W,NW,N,NE,E and movement SE (S free)

}

// TODO - put some comments
TEST (Grid, Draw) {
    Grid grid;

    sf::RenderWindow window;

    grid.draw(window);

    for (int i = 0; i < grid.getHeight(); i++) {
        for (int j = 0; j < grid.getWidth(); j++) {

            if ((*grid.getCell(i,j)).isTheStart())
                EXPECT_EQ(sf::Color::Green, (*grid.getCell(i,j)).getShape().getFillColor());

            else if ((*grid.getCell(i,j)).isTheGoal())
                EXPECT_EQ(sf::Color::Red, (*grid.getCell(i,j)).getShape().getFillColor());

            else if ((*grid.getCell(i,j)).isAPathElement())
                EXPECT_EQ(sf::Color::Blue, (*grid.getCell(i,j)).getShape().getFillColor());

            else if ((*grid.getCell(i,j)).isVisited())
                EXPECT_EQ(sf::Color::Cyan, (*grid.getCell(i,j)).getShape().getFillColor());

            else if ((*grid.getCell(i,j)).isAnObstacle())
                EXPECT_EQ(sf::Color::Black, (*grid.getCell(i,j)).getShape().getFillColor());

            else
                EXPECT_EQ(sf::Color::White, (*grid.getCell(i,j)).getShape().getFillColor());
        }
    }

}

// TODO - put some comments
TEST (Grid, UpdateCell) {
    Grid grid(5,5,false,false);

    grid.updateCell(1,1);

    ASSERT_TRUE((*grid.getCell(1,1)).isAnObstacle());

    grid.updateCell(1,1);

    ASSERT_FALSE((*grid.getCell(1,1)).isAnObstacle());

}

// TODO - put some comments
TEST (Grid, SetThePath) {
    Grid grid(5,5,false, false);
    AStarSearch a_star_search(grid);

    grid.setTheStart(0,0);
    grid.setTheGoal(4,0);

    a_star_search.findPath();

    std::vector<Cell> path { Cell{0,0}, Cell{1,0}, Cell{2,0}, Cell{3,0}, Cell{4,0} };

    for (const auto& it : path) {
        if(!(grid.getCell(it.getX(),it.getY())->isTheStart()) && !(grid.getCell(it.getX(),it.getY())->isTheGoal()))
            EXPECT_TRUE((*grid.getCell(it.getX(),it.getY())).isAPathElement());
    }
}

// TODO - put some comments
TEST (Grid, ResetPathDrawn) {
    Grid grid;
    AStarSearch a_star_search(grid);

    a_star_search.findPath();

    grid.resetPathDrawn();

    for (int i = 0; i < grid.getHeight(); i++)
        for (int j = 0; j < grid.getWidth(); j++) {
            EXPECT_FALSE((*grid.getCell(i,j)).isAPathElement());
            EXPECT_FALSE((*grid.getCell(i,j)).isVisited());
        }
}

// reset() // TODO