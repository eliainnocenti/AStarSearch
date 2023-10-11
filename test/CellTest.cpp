//
// Created by Elia Innocenti on 10/10/23.
//

// libraries
#include "gtest/gtest.h"
#include "../Cell.h"

// default constructor test
TEST (Cell, DefaultConstructor) {
    Cell c;

    // the Cell default constructor must set the default position of the cell to (0,0)
    ASSERT_EQ(0, c.getX());
    ASSERT_EQ(0, c.getY());

    // the Cell default constructor must set the cell as a free cell
    ASSERT_FALSE(c.isTheStart());
    ASSERT_FALSE(c.isTheGoal());
    ASSERT_FALSE(c.isAnObstacle());
    ASSERT_FALSE(c.isAPathElement());
    ASSERT_FALSE(c.isVisited());

    // graphics
    sf::RenderWindow window;
    c.draw(window);

    // the Cell default constructor must set the cell to white (because of it's a free cell)
    ASSERT_EQ(sf::Color::White, c.getShape().getFillColor());
}

// cell color and boolean value test
TEST (Cell, FreeCell) {
    Cell free;
    free.resetAsFree(); // setter

    // all the boolean values must be false
    ASSERT_FALSE(free.isTheStart());
    ASSERT_FALSE(free.isTheGoal());
    ASSERT_FALSE(free.isAnObstacle());
    ASSERT_FALSE(free.isAPathElement());
    ASSERT_FALSE(free.isVisited());

    // graphics
    sf::RenderWindow window;
    free.draw(window);

    // the color must be white
    ASSERT_EQ(sf::Color::White, free.getShape().getFillColor());
}

TEST (Cell, StartCell) {
    Cell start;
    start.setTheStart(); // setter

    // the start boolean value must be true and false all the others
    ASSERT_TRUE(start.isTheStart());
    ASSERT_FALSE(start.isTheGoal());
    ASSERT_FALSE(start.isAnObstacle());
    ASSERT_FALSE(start.isAPathElement());
    ASSERT_FALSE(start.isVisited());

    // graphics
    sf::RenderWindow window;
    start.draw(window);

    // the color must be green
    ASSERT_EQ(sf::Color::Green, start.getShape().getFillColor());
}

TEST (Cell, GoalCell) {
    Cell goal;
    goal.setTheGoal(); // setter

    // the goal boolean value must be true and false all the others
    ASSERT_FALSE(goal.isTheStart());
    ASSERT_TRUE(goal.isTheGoal());
    ASSERT_FALSE(goal.isAnObstacle());
    ASSERT_FALSE(goal.isAPathElement());
    ASSERT_FALSE(goal.isVisited());

    // graphics
    sf::RenderWindow window;
    goal.draw(window);

    // the color must be red
    ASSERT_EQ(sf::Color::Red, goal.getShape().getFillColor());
}

TEST (Cell, ObstacleCell) {
    Cell obstacle;
    obstacle.setAsObstacle(); // setter

    // the obstacle boolean value must be true and false all the others
    ASSERT_FALSE(obstacle.isTheStart());
    ASSERT_FALSE(obstacle.isTheGoal());
    ASSERT_TRUE(obstacle.isAnObstacle());
    ASSERT_FALSE(obstacle.isAPathElement());
    ASSERT_FALSE(obstacle.isVisited());

    // graphics
    sf::RenderWindow window;
    obstacle.draw(window);

    // the color must be black
    ASSERT_EQ(sf::Color::Black, obstacle.getShape().getFillColor());
}

TEST (Cell, PathCell) {
    Cell path;
    path.setAsPathElement(); // setter

    // the path boolean value must be true and false all the others
    ASSERT_FALSE(path.isTheStart());
    ASSERT_FALSE(path.isTheGoal());
    ASSERT_FALSE(path.isAnObstacle());
    ASSERT_TRUE(path.isAPathElement());
    ASSERT_FALSE(path.isVisited());

    // graphics
    sf::RenderWindow window;
    path.draw(window);

    // the color must be blue
    ASSERT_EQ(sf::Color::Blue, path.getShape().getFillColor());
}

TEST (Cell, VisitedCell) {
    Cell visited;
    visited.setAsVisited(); // setter

    // the visited boolean value must be true and false all the others
    ASSERT_FALSE(visited.isTheStart());
    ASSERT_FALSE(visited.isTheGoal());
    ASSERT_FALSE(visited.isAnObstacle());
    ASSERT_FALSE(visited.isAPathElement());
    ASSERT_TRUE(visited.isVisited());

    // graphics
    sf::RenderWindow window;
    visited.draw(window);

    // the color must be cyan
    ASSERT_EQ(sf::Color::Cyan, visited.getShape().getFillColor());
}