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
    void findPath(const Cell& start, const Cell& goal);
    void findRandomPath();

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

    // extra
    void printAllTheObstacles() const;

private:
    int width, height; // size

    std::vector<std::vector<Cell>> map; // main data structure

    // directions
    bool diagonalMovements;
    std::unordered_set<Cell> directions;

    // mapmaker
    void makeRandomMap(int width, int height); // TODO
    Cell* setRandomStart();
    Cell* setRandomGoal();

    // search
    bool in_bounds(const Cell& cell) const;
    bool passable(const Cell& cell) const;
    std::vector<Cell> neighbors(const Cell& cell) const;
    double heuristic(const Cell& from_node, const Cell& to_node) const;
    double cost(const Cell& from_node, const Cell& to_node) const; // TODO - possible GridWithWeights implementation
    void aStarSearch(const Cell& start, const Cell& goal, std::unordered_map<Cell, Cell>& came_from, std::unordered_map<Cell, double>& cost_so_far);

    // reconstruct
    std::vector<Cell> reconstructPath(const Cell& start, const Cell& goal, std::unordered_map<Cell, Cell>& came_from, std::unordered_map<Cell, double>& cost_so_far); // TODO check ugly path
    void printPath(const std::vector<Cell>& path, const Cell &start, const Cell &goal) const;
    void printInfo(const Cell& cell) const;

    // extra
    std::vector<Cell> findAllTheObstacles() const;

    // reset
    void reset(); // TODO

};

#endif //ASTARSEARCH_GRID_H