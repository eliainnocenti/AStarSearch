//
// Created by Elia Innocenti on 07/10/23.
//

#include "AStarSearch.h"

AStarSearch::AStarSearch(Grid& grid) {
    this->grid = std::make_shared<Grid>(grid);
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
    //printPath(path, *startCell, *goalCell); // grid->printPath(path, *(grid->getStartCell()), *(grid->getGoalCell())); // printPath() has to be public

    // sets the path
    setThePath(path); // grid->setThePath(path); // setThePath() has to be public
}

void AStarSearch::aStarSearch(const Cell &start, const Cell &goal, std::unordered_map<Cell, Cell> &came_from, std::unordered_map<Cell, double> &cost_so_far) {

    // initialize the priority queue with the starting point and a priority of 0
    PriorityQueue<Cell, double> frontier; // FIXME - use std::priority_queue and delete PriorityQueue.h
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

bool AStarSearch::in_bounds(const Cell &cell) const {
    // returns true if the cell is inside the map, false otherwise
    return 0 <= cell.getX() && cell.getX() < grid->getHeight() && 0 <= cell.getY() && cell.getY() < grid->getWidth();
}

bool AStarSearch::in_bounds(const int x, const int y) const {
    // returns true if the cell is inside the map, false otherwise
    return 0 <= x && x < grid->getHeight() && 0 <= y && y < grid->getWidth();
}

bool AStarSearch::passable(const Cell &cell) const {
    // return true if the cell is not an obstacle, false otherwise

    if (!(grid->getCell(cell.getX(), cell.getY())->isAnObstacle()))
        return true;
    else
        return false;
}

bool AStarSearch::isThisADiagonalMovements(const Cell &dir) {
    // returns true if it's NE, NW, SE or SW

    if (dir.getX() != 0 && dir.getY() != 0)
        return true;
    return false;
}

bool AStarSearch::isThisAValidDiagonalCell(const Cell &cell, const Cell &dir) const {
    int x = cell.getX();
    int y = cell.getY();

    if (dir.getX() == 1 && dir.getY() == 1) { // if the movement is in SE direction
        if (passable(*(grid->getCell(x+1,y))) && passable(*(grid->getCell(x,y+1)))) // if S and E are not obstacles, it is valid
            return true;
    } else if (dir.getX() == 1 && dir.getY() == -1) { // if the movement is in SW direction
        if (passable(*(grid->getCell(x+1,y))) && passable(*(grid->getCell(x,y-1)))) // if S and W are not obstacles, it is valid
            return true;
    } else if (dir.getX() == -1 && dir.getY() == -1) { // if the movement is in NW direction
        if (passable(*(grid->getCell(x-1,y))) && passable(*(grid->getCell(x,y-1)))) // if N and W are not obstacles, it is valid
            return true;
    } else if (dir.getX() == -1 && dir.getY() == 1) { // if the movement is in NE direction
        if (passable(*(grid->getCell(x-1,y))) && passable(*(grid->getCell(x,y+1)))) // if N and E are not obstacles, it is valid
            return true;
    }
    return false;
}

std::vector<Cell> AStarSearch::neighbors(const Cell &cell) {

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

double AStarSearch::cost(const Cell &from_node, const Cell &to_node) {
    // let's assume the cost is 1
    return 1;
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