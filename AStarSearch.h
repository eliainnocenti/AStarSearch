//
// Created by Elia Innocenti on 07/10/23.
//

#ifndef ASTARSEARCH_ASTARSEARCH_H
#define ASTARSEARCH_ASTARSEARCH_H

// libraries
#include <utility>
#include <queue>

// classes
#include "Cell.h"
#include "PriorityQueue.h"
#include "Grid.h"

class AStarSearch {
public:

    // constructor
    explicit AStarSearch(Grid& grid);

    Grid* getGridPointer() const;

    // find the path
    void findPath();

private:

    Grid* grid; // ... // TODO - put some comments // FIXME ? - do i have to use smart_ptr?
    std::unordered_set<Cell> directions; // ... // TODO - put some comments


    // TODO - check if some methods of this class have to be Grid methods // TODO - put some comments

    void aStarSearch(const Cell& start, const Cell& goal, std::unordered_map<Cell, Cell>& came_from, std::unordered_map<Cell, double>& cost_so_far);
    bool in_bounds(const Cell& cell) const; // can be a Grid method
    bool in_bounds(const int x, const int y) const; // can be a Grid method
    bool passable(const Cell& cell) const; // can be a Grid method
    static bool isThisADiagonalMovements(const Cell& dir); // can be a Grid method ?
    bool isThisAValidDiagonalCell(const Cell& cell, const Cell& dir) const; // can be a Grid method ?
    std::vector<Cell> neighbors(const Cell& cell);
    double heuristic(const Cell& from_node, const Cell& to_node) const;
    static double cost(const Cell& from_node, const Cell& to_node); // can be a Grid method ?

    static std::vector<Cell> reconstructPath(const Cell& start, const Cell& goal, std::unordered_map<Cell, Cell>& came_from, std::unordered_map<Cell, double>& cost_so_far); // TODO check ugly path

};


#endif //ASTARSEARCH_ASTARSEARCH_H
