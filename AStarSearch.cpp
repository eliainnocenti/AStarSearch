//
// Created by Elia Innocenti on 07/10/23.
//

#include "AStarSearch.h"

AStarSearch::AStarSearch(Grid& grid) {
    // allocates memory

    this->grid = &grid;
    directions = grid.getDirections();
}

AStarSearch::AStarSearch() {
    // default values

    this->grid = nullptr;
    directions = std::unordered_set<Cell> { Cell{0,1},  Cell{1,0}, Cell{0,-1}, Cell{-1,0} };
}

Grid *AStarSearch::getGridPointer() const {
    return grid;
}

std::unordered_set<Cell> AStarSearch::getDirections() const {
    return directions;
}

void AStarSearch::findPath() {
    // data structures for the algorithm
    std::unordered_map<Cell, Cell> came_from;
    std::unordered_map<Cell, double> cost_so_far;

    // A*Search
    aStarSearch(*(grid->getStartCell()), *(grid->getGoalCell()), came_from, cost_so_far);

    // reconstructs the path
    std::vector<Cell> path = reconstructPath(*(grid->getStartCell()), *(grid->getGoalCell()), came_from, cost_so_far);

    // prints the path
    //grid->printPath(path);

    // sets the path
    grid->setThePath(path);
}

void AStarSearch::aStarSearch(const Cell &start, const Cell &goal, std::unordered_map<Cell, Cell> &came_from, std::unordered_map<Cell, double> &cost_so_far) {

    // initialize the priority queue with the starting point and a priority of 0
    PriorityQueue frontier;
    frontier.put(start, 0);

    // initialize maps to keep track of the path and costs so far
    came_from[start] = start;
    cost_so_far[start] = 0;

    // main loop of the A* algorithm
    while (!frontier.empty()) {

        // extract the current point from the priority queue
        Cell current = frontier.get();

        // early exit
        if (current == goal) {
            break;
        }

        // find neighbors of the current point.
        std::vector<Cell> neighbors = this->neighbors(current);

        // explore neighbors of the current point
        for (const Cell& next : neighbors) {
            // calculate the new cost to reach the current neighbor
            double new_cost = cost_so_far[current] + cost(current, next);
            // check if it's the first encounter with the neighbor or if the new cost is better than the previous cost
            if (cost_so_far.find(next) == cost_so_far.end() || new_cost < cost_so_far[next]) {
                // update the cost so far and the neighbor's priority
                cost_so_far[next] = new_cost;
                double priority = new_cost + heuristic(next, goal);

                // sdd the neighbor to the priority queue and record the path
                frontier.put(next, priority);
                came_from[next] = current;
            }
        }
    }
}

std::vector<Cell> AStarSearch::neighbors(const Cell &cell) {
    // finds neighboring cells of the given 'cell' within the grid

    // initialize an empty vector to store the neighboring cells
    std::vector<Cell> results;

    // iterate through the predefined directions to explore neighboring cells
    for (const Cell& dir : directions) {
        // calculate the coordinates of the potential neighboring cell
        Cell next{cell.getX() + dir.getX(), cell.getY() + dir.getY(), grid->getCellSide()};

        if (grid->in_bounds(next)) { // if the cell is within the grid bounds
            if (grid->passable(next)) { // if the cell is not an obstacle
                if (grid->isThisADiagonalMovements(dir)) { // if the movement is diagonal
                    if (grid->isThisAValidDiagonalCell(cell, dir)) { // if the movements is not through the wall
                        results.push_back(next); // add it to the results vector
                        //map[next.getX()][next.getY()].setAsVisited(); // mark the cell as visited
                        grid->setAsVisited(next);
                    } else continue;
                } else {
                    // if the movement is not diagonal and the cell is passable and within the grid bounds
                    results.push_back(next); // add it to the results vector
                    //map[next.getX()][next.getY()].setAsVisited(); // mark the cell as visited
                    grid->setAsVisited(next);
                }
            }
        }
    }

    // TODO check - ugly paths
    if ((cell.getX() + cell.getY()) % 2 == 0) {
        std::reverse(results.begin(), results.end());
    }

    return results;
}

double AStarSearch::heuristic(const Cell &from_node, const Cell &to_node) const {
    // a heuristic function is a function that estimates the cost from a given node to the goal node in a graph or search space

    if (grid->isDiagonalMovementAllowed()) {
        // euclidean distance
        double dx = from_node.getX() - to_node.getX();
        double dy = from_node.getY() - to_node.getY();
        return std::sqrt(dx * dx + dy * dy);
    } else
        // manhattan distance
        return std::abs(from_node.getX() - to_node.getX()) + std::abs(from_node.getY() - to_node.getY());
}

double AStarSearch::cost(const Cell &from_node, const Cell &to_node) const {
    // returns the cost from one node to another one

    return grid->getCost(from_node, to_node);
}

std::vector<Cell> AStarSearch::reconstructPath(const Cell &start, const Cell &goal, std::unordered_map<Cell, Cell> &came_from, std::unordered_map<Cell, double> &cost_so_far) {
    // returns the cells that are part of the path

    std::vector<Cell> path;
    Cell current = goal;
    if (came_from.find(goal) == came_from.end()) {
        return path; // no path can be found
    }
    while (current != start) {
        path.push_back(current);
        current = came_from[current];
    }

    // optional
    path.push_back(start);
    std::reverse(path.begin(), path.end());
    return path;
}