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

    // reconstruct the path
    std::vector<Cell> path = reconstructPath(*startCell, *goalCell, came_from, cost_so_far);

    // print the path
    //printPath(path, *startCell, *goalCell);

    // set the path
    setThePath(path);
}

void Grid::aStarSearch(const Cell &start, const Cell &goal, std::unordered_map<Cell, Cell>& came_from, std::unordered_map<Cell, double>& cost_so_far) {
    // TODO - put some comments
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

        for (const Cell& next : neighbors) {
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

std::vector<Cell> Grid::neighbors(const Cell &cell) {
    // TODO - put some comments

    // FIXME - diagonal movement

    std::vector<Cell> results;

    for (const Cell& dir : directions) {
        Cell next{cell.getX() + dir.getX(), cell.getY() + dir.getY(), cellSide};
        if (in_bounds(next)) {
            if (passable(next)) {
                results.push_back(next);

                //
                map[next.getX()][next.getY()].setAsVisited();
            }
        }
    }

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

    //---------DEBUG----------------------------------------------------------------------------------------------------
    // FIXME

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
    // TODO - put some comments
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
    // TODO - put some comments
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
    // TODO - put some comments
    for (const auto& it : path) {
        if (!map[it.getX()][it.getY()].isTheStart() && !map[it.getX()][it.getY()].isTheGoal())
            if (map[it.getX()][it.getY()].isVisited())
                map[it.getX()][it.getY()].clean();
            map[it.getX()][it.getY()].setAsPathElement();
    }
}

void Grid::printPath(const std::vector<Cell> &path, const Cell &start, const Cell &goal) const {
    // TODO - put some comments, reorganize the code
    std::cout << "The path from: " << "{ x: " << start.getX() << ", y: " << start.getY() << " } " <<
              "to: " << "{ x: " << goal.getX() << ", y: " << goal.getY() << " } " << "is: " << std::endl;
    for (const auto& it : path)
        printPosition(it);
}

void Grid::printPosition(const Cell &cell) {
    // TODO - put some comments
    std::cout << "{ x: " << cell.getX() << ", y: " << cell.getY() << " }" << std::endl;
}

void Grid::printInfo(const Cell &cell) {
    // TODO - put some comments, reorganize the code
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
    // TODO - put some comments
    for (int i = 0; i < height; i ++) {
        map.emplace_back();
        for (int j = 0; j < width; j++) {
            Cell cell(i, j, cellSide);
            map[i].push_back(cell);
        }
    }
}

void Grid::makeRandomMap(unsigned int width, unsigned int height, unsigned int cellSide) {
    // TODO - put some comments
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
    // TODO - put some comments
    std::array<int, 2> randStart {};

    unsigned int randX;
    unsigned int randY;

    do {
        randX = rand() % height;
        randY = rand() % width;
    } while (map[randX][randY].isAnObstacle() || map[randX][randY].isTheGoal());

    map[randX][randY].setTheStart();

    randStart[0] = randX;
    randStart[1] = randY;

    return randStart;
}

std::array<int, 2> Grid::setRandomGoal() {
    // TODO - put some comments
    std::array<int, 2> randGoal {};

    unsigned int randX;
    unsigned int randY;

    do {
        randX = rand() % height;
        randY = rand() % width;
    } while (map[randX][randY].isAnObstacle() || map[randX][randY].isTheStart());

    map[randX][randY].setTheGoal();

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
    // TODO - put some comments, reorganize the code
    std::vector<Cell> obstacles = findAllTheObstacles();
    std::cout << "The obstacles are in positions: " << std::endl;
    for (const auto & obstacle : obstacles)
        printPosition(obstacle);
    std::cout << std::endl;
}

std::vector<Cell> Grid::findAllTheObstacles() const {
    // TODO - put some comments
    std::vector<Cell> obstacles;
    for (int i = 0; i < height; i ++) {
        for (int j = 0; j < width; j++) {
            if (map[i][j].isAnObstacle())
                obstacles.push_back(map[i][j]);
        }
    }
    return obstacles;
}

void Grid::printAllTheGrid() const {
    // TODO - put some comments
    for (int i = 0; i < height; i ++) {
        for (int j = 0; j < width; j++) {
            printInfo(map[i][j]);
        }
    }
}

void Grid::draw(sf::RenderWindow &window) {
    // TODO - put some comments
    for (int i = 0; i < height; i ++) {
        for (int j = 0; j < width; j++) {
            map[i][j].draw(window);
        }
    }
}

void Grid::updateCell(int x, int y) {
    // TODO - put some comments
    if (map[x][y].isAnObstacle() && !map[x][y].isTheStart() && !map[x][y].isTheGoal())
        map[x][y].resetAsFree();
    else if (!map[x][y].isTheStart() && !map[x][y].isTheGoal())
        map[x][y].setAsObstacle();
}

void Grid::resetPathDrawn() {
    // TODO - put some comments
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            map[i][j].clean();
}

bool Grid::isThereAStart() const {
    // TODO - put some comments
    if (startCell != nullptr)
        return true;
    return false;
}

bool Grid::isThereAGoal() const {
    // TODO - put some comments
    if (goalCell != nullptr)
        return true;
    return false;
}

void Grid::reset() {
    // TODO - put some comments

    resetPathDrawn();
    resetAllTheObstacles(findAllTheObstacles());

    for (int i = 0; i < height; i ++) {
        for (int j = 0; j < width; j++) {
            float randomNumber = rand() % 10;
            if (randomNumber < density)
                map[i][j].setAsObstacle();
        }
    }

    map[startCell->getX()][startCell->getY()].resetTheStart();
    std::array<int, 2> randStart = setRandomStart();
    startCell = std::make_shared<Cell>(map[randStart[0]][randStart[1]]);

    map[goalCell->getX()][goalCell->getY()].resetTheGoal();
    std::array<int, 2> randGoal = setRandomGoal();
    goalCell = std::make_shared<Cell>(map[randGoal[0]][randGoal[1]]);

    findPath();

}

void Grid::resetAllTheObstacles(const std::vector<Cell> &obstacles) {
    // TODO - put some comments
    for (const auto& it : obstacles)
        map[it.getX()][it.getY()].resetAsFree();
}

Cell *Grid::getCell(unsigned int x, unsigned int y) {
    if (in_bounds(x,y))
        return &map[x][y];
    return nullptr;
}