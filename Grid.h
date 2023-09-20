//
// Created by Elia Innocenti on 19/09/23.
//

#ifndef ASTARSEARCH_GRID_H
#define ASTARSEARCH_GRID_H

#include <vector>
#include <array>
#include <unordered_map>
#include <unordered_set>
#include <iostream>

#include "Cell.h"
#include "PriorityQueue.h"

class Grid {
public:
    // constructor
    explicit Grid(int width, int height, bool diagonal = false, bool random = true);

    // A*Search
    void findPath(const Cell& start, const Cell& goal); // TODO check

    // set the start
    void setTheStart(int x, int y);
    void setTheStart(const Cell& cell);

    // set the goal
    void setTheGoal(int x, int y);
    void setTheGoal(const Cell& cell);

    // set an obstacle
    void setAnObstacle(int x, int y);
    void setAnObstacle(const Cell& cell);

    // getter
    inline int getWidth() const { return width; }
    inline int getHeight() const { return height; }

private:
    int width, height; // size

    // directions
    bool diagonalMovements;
    std::unordered_set<Cell> directions;

    std::vector<std::vector<Cell>> map; // main data structure

    // data structures for the algorithm
    std::unordered_map<Cell, Cell> came_from;
    std::unordered_map<Cell, double> cost_so_far;

    // mapmaker
    void makeRandomMap(int width, int height);
    void setRandomStart(); // TODO
    void setRandomGoal(); // TODO
    Cell* findFreeCell(); // TODO

    // search
    bool in_bounds(const Cell& cell) const; // TODO check
    bool passable(const Cell& cell) const; // TODO check
    std::vector<Cell> neighbors(const Cell& cell) const; // TODO check
    double heuristic(const Cell& from_node, const Cell& to_node) const; // TODO check
    double cost(const Cell& from_node, const Cell& to_node) const; // TODO check
    void aStarSearch(const Cell& start, const Cell& goal); // TODO check

    // reconstruct
    std::vector<Cell> reconstructPath(const Cell& start, const Cell& goal); // TODO check
    void printPath(const std::vector<Cell>& path, const Cell &start, const Cell &goal) const;
    void printInfo(const Cell& cell) const;

    // reset
    void reset(); // TODO

};

#endif //ASTARSEARCH_GRID_H