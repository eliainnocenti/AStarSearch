//
// Created by Elia Innocenti on 19/09/23.
//

#include "Grid.h"

Grid::Grid(int width, int height, bool random) : width(width), height(height) {
    // a random map is generated
    if (random)
        makeRandomMap(width, height);
}

void Grid::findPath(const Cell &start, const Cell &goal) {
    // A*Search
    a_star_search(start, goal);

    //
    std::vector<Cell> path = reconstruct_path(start, goal);

    //
    printPath(path, start, goal);
}

void Grid::a_star_search(const Cell &start, const Cell &goal) {

    PriorityQueue<Cell, double> frontier;
    frontier.put(start, 0);

    came_from[start] = start;
    cost_so_far[start] = 0;

    while (!frontier.empty()) {

        Cell current = frontier.get();

        // early exit
        if (current == goal) {
            break;
        }

        std::vector<Cell> neighbors = this->neighbors(current);

        for (Cell next : neighbors) {
            double new_cost = cost_so_far[current] + cost(current, next);
            if (cost_so_far.find(next) == cost_so_far.end() || new_cost < cost_so_far[next]) {
                cost_so_far[next] = new_cost;
                double priority = new_cost + heuristic(next, goal);
                frontier.put(next, priority);
                came_from[next] = current;
            }
        }
    }

}

std::vector<Cell> Grid::neighbors(const Cell &cell) const {

    std::vector<Cell> results;

    for (Cell dir : DIRS) {
        Cell next{cell.getX() + dir.getX(), cell.getY() + dir.getY()};
        if (in_bounds(next) && passable(next)) {
            results.push_back(next);
        }
    }

    //TODO
    if ((cell.getX() + cell.getY()) % 2 == 0) {
        // see "Ugly paths" section for an explanation:
        std::reverse(results.begin(), results.end());
    }

    return results;
}

bool Grid::in_bounds(const Cell &cell) const {
    return 0 <= cell.getX() && cell.getX() < width && 0 <= cell.getY() && cell.getY() < height;
}

bool Grid::passable(const Cell &cell) const {
    if (!cell.isAnObstacle())
        return true;
    return false;
}

double Grid::cost(const Cell &from_node, const Cell &to_node) const {
    return 1;
}

double Grid::heuristic(const Cell &from_node, const Cell &to_node) const {
    return std::abs(from_node.getX() - to_node.getX()) + std::abs(from_node.getY() - to_node.getY());
}

std::vector<Cell> Grid::reconstruct_path(const Cell &start, const Cell &goal) {
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

void Grid::printPath(const std::vector<Cell> &path, const Cell &start, const Cell &goal) const {
    std::cout << "The path from: " << "{ x: " << start.getX() << ", y: " << start.getY() << " } " <<
              "to: " << "{ x: " << goal.getX() << ", y: " << goal.getY() << " } " << "is: " << std::endl;
    for (auto it : path)
        printInfo(it);
}

void Grid::printInfo(const Cell &cell) const {
    std::cout << "{ x: " << cell.getX() << ", y: " << cell.getY() << " }" << std::endl;
}

void Grid::makeRandomMap(int width, int height) {

    //TODO -> some cell has to be obstacles (randomly)
    for (int i = 0; i < height; i ++) {
        map.emplace_back();
        for (int j = 0; j < width; j++) {
            Cell cell(i, j);
            map[i].push_back(cell);
        }
    }

    setRandomStart();
    setRandomGoal();
}

void Grid::setRandomStart() {
    //TODO
}

void Grid::setRandomGoal() {
    //TODO
}

Cell *Grid::findFreeCell() {
    //TODO
    return nullptr;
}

void Grid::setTheStart(int x, int y) {
    map[x][y].setTheStart();
}

void Grid::setTheStart(const Cell &cell) {
    map[cell.getX()][cell.getY()].setTheStart();
}

void Grid::setTheGoal(int x, int y) {
    map[x][y].setTheGoal();
}

void Grid::setTheGoal(const Cell &cell) {
    map[cell.getX()][cell.getY()].setTheGoal();
}

void Grid::setAnObstacle(int x, int y) {
    map[x][y].setAsObstacle();
}

void Grid::setAnObstacle(const Cell &cell) {
    map[cell.getX()][cell.getY()].setAsObstacle();
}