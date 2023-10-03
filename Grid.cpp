//
// Created by Elia Innocenti on 19/09/23.
//

#include "Grid.h"

Grid::Grid(unsigned int width, unsigned int height, bool diagonal, bool random, float density, bool constCost) : width(width), height(height), diagonalMovements(diagonal), density(density) {

    cellSide = 750 / width; //cellSide = 800 / height

    //---------DEBUG----------------------------------------------------------------------------------------------------
    // FIXME

    //cellSide = int(sf::VideoMode::getDesktopMode().width) / width;
    //cellSide = 2560 / width; //cellSide = 1600 / height
    //cellSide = 40;

    //------------------------------------------------------------------------------------------------------------------

    if (diagonal)
        // Nord, Nord-Est, Est, Sud-Est, Sud, Sud-Ovest, Ovest, Nord-Ovest
        directions = std::unordered_set<Cell> { Cell{-1,0, cellSide}, Cell{-1,1, cellSide},
                                                Cell{0,1, cellSide},  Cell{1,1, cellSide},
                                                Cell{1,0, cellSide},  Cell{1,-1, cellSide},
                                                Cell{0,-1, cellSide}, Cell{-1,-1, cellSide} };
    else
        // Nord, Est, Sud, Ovest
        directions = std::unordered_set<Cell> { Cell{0,1, cellSide},  Cell{1,0, cellSide},
                                                Cell{0,-1, cellSide}, Cell{-1,0, cellSide} };

    if (random) {
        // a random map is generated
        makeRandomMap(width, height, cellSide);

        // pointers updated with random start and goal
        if (!isThereAStart()) {
            std::array<int, 2> randStart = setRandomStart();
            startCell = std::make_shared<Cell>(map[randStart[0]][randStart[1]]);
        }
        if (!isThereAGoal()) {
            std::array<int, 2> randGoal = setRandomGoal();
            goalCell = std::make_shared<Cell>(map[randGoal[0]][randGoal[1]]);
        }
    } else
        makeMap(width, height, cellSide);

}

void Grid::findPath() {

    // data structures for the algorithm
    std::unordered_map<Cell, Cell> came_from;
    std::unordered_map<Cell, double> cost_so_far;

    // A*Search
    aStarSearch(*startCell, *goalCell, came_from, cost_so_far);

    // reconstructs the path
    std::vector<Cell> path = reconstructPath(*startCell, *goalCell, came_from, cost_so_far);

    // prints the path
    //printPath(path, *startCell, *goalCell);

    // sets the path
    setThePath(path);
}

void Grid::aStarSearch(const Cell &start, const Cell &goal, std::unordered_map<Cell, Cell>& came_from, std::unordered_map<Cell, double>& cost_so_far) {

    // initialize the priority queue with the starting point and a priority of 0
    PriorityQueue<Cell, double> frontier;
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

std::vector<Cell> Grid::neighbors(const Cell &cell) {
    // finds neighboring cells of the given 'cell' within the grid

    //---------DEBUG----------------------------------------------------------------------------------------------------
    // FIXME - diagonal movement

    // initialize an empty vector to store the neighboring cells
    std::vector<Cell> results;

    // iterate through the predefined directions to explore neighboring cells
    for (const Cell& dir : directions) {
        // calculate the coordinates of the potential neighboring cell
        Cell next{cell.getX() + dir.getX(), cell.getY() + dir.getY(), cellSide};
        if (in_bounds(next)) {
            if (passable(next)) {
                results.push_back(next); // if it's passable and within the grid bounds, add it to the results vector

                // mark the cell as visited
                map[next.getX()][next.getY()].setAsVisited();
            }
        }
    }

    //------------------------------------------------------------------------------------------------------------------

    // TODO check - ugly paths
    if ((cell.getX() + cell.getY()) % 2 == 0) {
        std::reverse(results.begin(), results.end());
    }

    return results;
}

bool Grid::in_bounds(const Cell &cell) const {
    // returns true if the cell is inside the map, false otherwise
    return 0 <= cell.getX() && cell.getX() < width && 0 <= cell.getY() && cell.getY() < height;
}

bool Grid::in_bounds(const int x, const int y) const {
    // returns true if the cell is inside the map, false otherwise
    return 0 <= x && x < width && 0 <= y && y < height;
}

bool Grid::passable(const Cell &cell) const {
    // returns true if the cell is not an obstacles, false otherwise

    //---------DEBUG----------------------------------------------------------------------------------------------------
    // FIXME

    // TODO - diagonal movements (cannot pass trough the walls)
    if (diagonalMovements)
        return false;

    // return true if the cell is not an obstacle, false otherwise
    if (!map[cell.getX()][cell.getY()].isAnObstacle())
        return true;
    else
        return false;

    //------------------------------------------------------------------------------------------------------------------

}

double Grid::cost(const Cell &from_node, const Cell &to_node) {
    // let's assume the cost is 1
    return 1;
}

double Grid::heuristic(const Cell &from_node, const Cell &to_node) const {
    // a heuristic function is a function that estimates the cost from a given node to the goal node in a graph or search space

    if (diagonalMovements) {
        // euclidean distance
        double dx = from_node.getX() - to_node.getX();
        double dy = from_node.getY() - to_node.getY();
        return std::sqrt(dx * dx + dy * dy);
    } else
        // manhattan distance
        return std::abs(from_node.getX() - to_node.getX()) + std::abs(from_node.getY() - to_node.getY());
}

std::vector<Cell> Grid::reconstructPath(const Cell &start, const Cell &goal, std::unordered_map<Cell, Cell>& came_from, std::unordered_map<Cell, double>& cost_so_far) {
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

void Grid::setThePath(const std::vector<Cell> &path) {
    // highlights the path by marking the cells of the path itself

    for (const auto& it : path) {
        if (!map[it.getX()][it.getY()].isTheStart() && !map[it.getX()][it.getY()].isTheGoal()) {
            if (map[it.getX()][it.getY()].isVisited())
                map[it.getX()][it.getY()].clean();

            map[it.getX()][it.getY()].setAsPathElement(); // mark the path cells
        }
    }
}

void Grid::printPath(const std::vector<Cell> &path, const Cell &start, const Cell &goal) const {
    // service function that prints path elements

    std::cout << "The path from: " << "{ x: " << start.getX() << ", y: " << start.getY() << " } " <<
              "to: " << "{ x: " << goal.getX() << ", y: " << goal.getY() << " } " << "is: " << std::endl;
    for (const auto& it : path)
        printPosition(it);
}

void Grid::printPosition(const Cell &cell) {
    // service function that prints the position of a cell
    std::cout << "{ x: " << cell.getX() << ", y: " << cell.getY() << " }" << std::endl;
}

void Grid::printInfo(const Cell &cell) {
    // service function that prints the position of a cell and its quality

    if (cell.isTheStart())
        std::cout << "{ x: " << cell.getX() << ", y: " << cell.getY() << " } " << "start" << std::endl;
    else if (cell.isTheGoal())
        std::cout << "{ x: " << cell.getX() << ", y: " << cell.getY() << " } " << "goal" << std::endl;
    else if (cell.isAnObstacle())
        std::cout << "{ x: " << cell.getX() << ", y: " << cell.getY() << " } " << "obstacle" << std::endl;
    else if (cell.isAPathElement())
        std::cout << "{ x: " << cell.getX() << ", y: " << cell.getY() << " } " << " path" << std::endl;
}

void Grid::makeMap(unsigned int width, unsigned int height, unsigned int cellSide) {
    // creates a map

    for (int i = 0; i < height; i ++) {
        map.emplace_back();
        for (int j = 0; j < width; j++) {
            Cell cell(i, j, cellSide);
            map[i].push_back(cell);
        }
    }
}

void Grid::makeRandomMap(unsigned int width, unsigned int height, unsigned int cellSide) {
    // creates a map and sets the obstacles randomly

    for (int i = 0; i < height; i ++) {
        map.emplace_back();
        for (int j = 0; j < width; j++) {
            Cell cell(i, j, cellSide);
            float randomNumber = rand() % 10;
            if (randomNumber < density)
                cell.setAsObstacle();
            map[i].push_back(cell);
        }
    }
}

std::array<int, 2> Grid::setRandomStart() {
    // sets a random start. it returns the start position

    std::array<int, 2> randStart {};

    unsigned int randX;
    unsigned int randY;

    do {
        randX = rand() % height;
        randY = rand() % width;
    } while (map[randX][randY].isAnObstacle() || map[randX][randY].isTheGoal());

    map[randX][randY].setTheStart(); // sets the right cell in the map as the Start

    randStart[0] = randX;
    randStart[1] = randY;

    return randStart;
}

std::array<int, 2> Grid::setRandomGoal() {
    // sets a random goal. it returns the goal position

    std::array<int, 2> randGoal {};

    unsigned int randX;
    unsigned int randY;

    do {
        randX = rand() % height;
        randY = rand() % width;
    } while (map[randX][randY].isAnObstacle() || map[randX][randY].isTheStart());

    map[randX][randY].setTheGoal(); // sets the right cell in the map as the Goal

    randGoal[0] = randX;
    randGoal[1] = randY;

    return randGoal;
}

void Grid::setTheStart(int x, int y) {
    map[x][y].setTheStart();
    startCell = std::make_shared<Cell>(map[x][y]);
}

void Grid::setTheStart(const Cell &cell) {
    map[cell.getX()][cell.getY()].setTheStart();
    startCell = std::make_shared<Cell>(map[cell.getX()][cell.getY()]);
}

void Grid::setTheGoal(int x, int y) {
    map[x][y].setTheGoal();
    goalCell = std::make_shared<Cell>(map[x][y]);
}

void Grid::setTheGoal(const Cell &cell) {
    map[cell.getX()][cell.getY()].setTheGoal();
    goalCell = std::make_shared<Cell>(map[cell.getX()][cell.getY()]);
}

void Grid::setAnObstacle(int x, int y) {
    map[x][y].setAsObstacle();
}

void Grid::setAnObstacle(const Cell &cell) {
    map[cell.getX()][cell.getY()].setAsObstacle();
}

void Grid::printAllTheObstacles() const {
    // service function that prints all the obstacles in the grid

    std::vector<Cell> obstacles = findAllTheObstacles();
    std::cout << "The obstacles are in positions: " << std::endl;
    for (const auto & obstacle : obstacles)
        printPosition(obstacle);
    std::cout << std::endl;
}

std::vector<Cell> Grid::findAllTheObstacles() const {
    // service function that finds all the obstacles in the grid

    std::vector<Cell> obstacles;
    for (int i = 0; i < height; i ++) {
        for (int j = 0; j < width; j++) {
            if (map[i][j].isAnObstacle())
                obstacles.push_back(map[i][j]);
        }
    }
    return obstacles;
}

void Grid::resetAllTheObstacles(const std::vector<Cell> &obstacles) {
    // sets all the obstacles as free cells

    for (const auto& it : obstacles)
        map[it.getX()][it.getY()].resetAsFree();
}

void Grid::printAllTheGrid() const {
    // service function that prints the info of all the cells in the grid

    for (int i = 0; i < height; i ++) {
        for (int j = 0; j < width; j++) {
            printInfo(map[i][j]);
        }
    }
}

void Grid::draw(sf::RenderWindow &window) {
    // draws function. calls the draw function for each cell

    for (int i = 0; i < height; i ++) {
        for (int j = 0; j < width; j++) {
            map[i][j].draw(window);
        }
    }
}

void Grid::updateCell(int x, int y) {
    // sets the cell as an obstacle if it is not already one and if it is neither the start nor the goal
    // if it is an obstacle, it sets the cell as a free cell

    if (map[x][y].isAnObstacle() && !map[x][y].isTheStart() && !map[x][y].isTheGoal())
        map[x][y].resetAsFree();
    else if (!map[x][y].isTheStart() && !map[x][y].isTheGoal())
        map[x][y].setAsObstacle();
}

void Grid::resetPathDrawn() {
    // sets all the grid cells as not path cells and as not visited cells

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            map[i][j].clean();
}

bool Grid::isThereAStart() const {
    if (startCell != nullptr) { return true; } return false;
}

bool Grid::isThereAGoal() const {
    if (goalCell != nullptr) { return true; } return false;
}

void Grid::reset() {
    // restarts the program regenerating a new random map and a new start and goal

    resetPathDrawn(); // cleans all the grid cells
    resetAllTheObstacles(findAllTheObstacles()); // set all the obstacles as free cells

    // re-creates obstacles randomly
    for (int i = 0; i < height; i ++) {
        for (int j = 0; j < width; j++) {
            float randomNumber = rand() % 10;
            if (randomNumber < density)
                map[i][j].setAsObstacle();
        }
    }

    // re-sets a random start
    map[startCell->getX()][startCell->getY()].resetTheStart();
    std::array<int, 2> randStart = setRandomStart();
    startCell = std::make_shared<Cell>(map[randStart[0]][randStart[1]]);

    // re-sets a random goal
    map[goalCell->getX()][goalCell->getY()].resetTheGoal();
    std::array<int, 2> randGoal = setRandomGoal();
    goalCell = std::make_shared<Cell>(map[randGoal[0]][randGoal[1]]);

    // finds the path
    findPath();

}

Cell *Grid::getCell(int x, int y) { if (in_bounds(x,y)) { return &map[x][y]; } return nullptr; }