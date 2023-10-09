//
// Created by Elia Innocenti on 19/09/23.
//

#ifndef ASTARSEARCH_GRID_H
#define ASTARSEARCH_GRID_H

// libraries
#include <vector>
#include <array>
#include <unordered_map>
#include <unordered_set>
#include <iostream>

// classes
#include "Cell.h"

// graphics
#include <SFML/Graphics.hpp>

class Grid {
public:
    // constructor
    explicit Grid(unsigned int width, unsigned int height, bool diagonal = false, bool random = true, float density = 2.5, bool constCost = true);

    // set the start
    void setTheStart(int x, int y);
    void setTheStart(const Cell& cell);

    // set the goal
    void setTheGoal(int x, int y);
    void setTheGoal(const Cell& cell);

    // set an obstacle
    void setAnObstacle(int x, int y);
    void setAnObstacle(const Cell& cell);

    // set as visited
    void setAsVisited(int x, int y);
    void setAsVisited(const Cell& cell);

    // getters
    inline unsigned int getWidth() const { return width; }
    inline unsigned int getHeight() const { return height; }
    inline unsigned int getCellSide() const { return cellSide; }
    inline bool isDiagonalMovementAllowed() const { return diagonalMovements; }
    inline std::shared_ptr<Cell> getStartCell() const { return startCell; }
    inline std::shared_ptr<Cell> getGoalCell() const { return goalCell; }
    inline std::unordered_set<Cell> getDirections() const { return directions; }
    Cell* getCell(int x, int y);
    double getCost(const Cell& from_node, const Cell& to_node) const; // TODO - possible GridWithWeights implementation


    // extra
    void printAllTheObstacles() const;
    void printAllTheGrid() const;
    void printPath(const std::vector<Cell>& path) const;
    int isThisAValidRun();

    // search
    bool in_bounds(const Cell& cell) const;
    bool in_bounds(const int x, const int y) const;
    bool passable(const Cell& cell) const;
    bool isThisADiagonalMovements(const Cell& cell) const;
    bool isThisAValidDiagonalCell(const Cell& cell, const Cell& dir) const;

    // graphics
    void draw(sf::RenderWindow &window);
    void updateCell(int x, int y);
    void setThePath(const std::vector<Cell>& path);
    void resetPathDrawn(); // TODO - can be optimized if it use the path vector instead of scrolling through the entire map

    // reset
    void reset(); // FIXME

private:
    unsigned int width, height; // size

    std::vector<std::vector<Cell>> map; // main data structure
    //std::unordered_map<std::pair<Cell, Cell>, double> weights; // TODO - possible GridWithWeights implementation
                                                                 // I can use a dictionary that relates an edge to its corresponding cost.
                                                                 // The cost() function would return the cost given the nodes and the data structure
                                                                 // std::unordered_map<std::pair<Cell, Cell>, double> weights.
                                                                 // However, the cells must be adjacent (the edge must exist).

    // pointers to the Start and the Goal
    std::shared_ptr<Cell> startCell {nullptr};
    std::shared_ptr<Cell> goalCell {nullptr};

    // directions
    bool diagonalMovements;
    std::unordered_set<Cell> directions;

    // graphics
    unsigned int cellSide;

    // mapmaker
    void makeMap(unsigned int width, unsigned int height, unsigned int cellSide);
    void makeRandomMap(unsigned int width, unsigned int height, unsigned int cellSide);
    std::array<int, 2> setRandomStart();
    std::array<int, 2> setRandomGoal();
    float density;

    // reconstruct
    static void printPosition(const Cell& cell) ;
    static void printInfo(const Cell& cell) ;

    // extra
    std::vector<Cell> findAllTheObstacles() const;
    void resetAllTheObstacles(const std::vector<Cell>& obstacles);
    bool isThereAStart() const;
    bool isThereAGoal() const;

};

#endif //ASTARSEARCH_GRID_H