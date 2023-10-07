//
// Created by Elia Innocenti on 07/10/23.
//

#ifndef ASTARSEARCH_ASTARSEARCH_H
#define ASTARSEARCH_ASTARSEARCH_H

#include "Grid.h"
#include "Cell.h"
#include "GraphicInterface.h"
#include "PriorityQueue.h"

#include <utility>
#include <queue>

class AStarSearch {
public:

    AStarSearch(Grid& grid);

    void findPath();

private:

    std::shared_ptr<Grid> grid;

    void aStarSearch(const Cell& start, const Cell& goal, std::unordered_map<Cell, Cell>& came_from, std::unordered_map<Cell, double>& cost_so_far);
    bool in_bounds(const Cell& cell) const;
    bool in_bounds(const int x, const int y) const;
    bool passable(const Cell& cell) const;
    static bool isThisADiagonalMovements(const Cell& dir);
    bool isThisAValidDiagonalCell(const Cell& cell, const Cell& dir) const;
    std::vector<Cell> neighbors(const Cell& cell);
    double heuristic(const Cell& from_node, const Cell& to_node) const;
    static double cost(const Cell& from_node, const Cell& to_node);

    static std::vector<Cell> reconstructPath(const Cell& start, const Cell& goal, std::unordered_map<Cell, Cell>& came_from, std::unordered_map<Cell, double>& cost_so_far); // TODO check ugly path


};


#endif //ASTARSEARCH_ASTARSEARCH_H
