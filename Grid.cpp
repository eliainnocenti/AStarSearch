//
// Created by Elia Innocenti on 19/09/23.
//

#include "Grid.h"

Grid::Grid(unsigned int width, unsigned int height, bool diagonal, bool random, float density, bool constCost) : width(width), height(height), diagonalMovements(diagonal), random(random), density(density), constCost(constCost) {

    cellSide = 25;

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

Grid::Grid() : Grid(10, 10) {} // diagonal = false, random = true, density = 2.5, constCost = true

bool Grid::in_bounds(const Cell &cell) const {
    // returns true if the cell is inside the map, false otherwise
    return 0 <= cell.getX() && cell.getX() < height && 0 <= cell.getY() && cell.getY() < width;
}

bool Grid::in_bounds(const int x, const int y) const {
    // returns true if the cell is inside the map, false otherwise
    return 0 <= x && x < height && 0 <= y && y < width;
}

bool Grid::passable(const Cell &cell) const {
    // return true if the cell is not an obstacle, false otherwise
    if (!map[cell.getX()][cell.getY()].isAnObstacle())
        return true;
    else
        return false;
}

bool Grid::passable(const int x, const int y) const {
    // return true if the cell is not an obstacle, false otherwise
    if (!map[x][y].isAnObstacle())
        return true;
    else
        return false;
}

bool Grid::isThisADiagonalMovements(const Cell &cell) const {
    // returns true if it's NE, NW, SE or SW

    if (cell.getX() != 0 && cell.getY() != 0)
        return true;
    return false;
}

bool Grid::isThisAValidDiagonalCell(const Cell &cell, const Cell &dir) const {

    int x = cell.getX();
    int y = cell.getY();

    if (dir.getX() == 1 && dir.getY() == 1) { // if the movement is in SE direction
        if (passable(map[x+1][y]) && passable(map[x][y+1])) // if S and E are not obstacles, it is valid
            return true;
    } else if (dir.getX() == 1 && dir.getY() == -1) { // if the movement is in SW direction
        if (passable(map[x+1][y]) && passable(map[x][y-1])) // if S and W are not obstacles, it is valid
            return true;
    } else if (dir.getX() == -1 && dir.getY() == -1) { // if the movement is in NW direction
        if (passable(map[x-1][y]) && passable(map[x][y-1])) // if N and W are not obstacles, it is valid
            return true;
    } else if (dir.getX() == -1 && dir.getY() == 1) { // if the movement is in NE direction
        if (passable(map[x-1][y]) && passable(map[x][y+1])) // if N and E are not obstacles, it is valid
            return true;
    }
    return false;
}

double Grid::getCost(const Cell &from_node, const Cell &to_node) const {

    // let's assume the cost is 1 for now
    if (constCost)
        return 1;

    else
        return 1; // TODO - implement
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

void Grid::printPath(const std::vector<Cell> &path) const {
    // service function that prints path elements

    std::cout << "The path from: " << "{ x: " << startCell->getX() << ", y: " << startCell->getY() << " } " <<
              "to: " << "{ x: " << goalCell->getX() << ", y: " << goalCell->getY() << " } " << "is: " << std::endl;
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
    else if (cell.isVisited())
        std::cout << "{ x: " << cell.getX() << ", y: " << cell.getY() << " } " << " visited" << std::endl;
    else
        std::cout << "{ x: " << cell.getX() << ", y: " << cell.getY() << " } " << " free cell" << std::endl;
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

void Grid::setAsVisited(int x, int y) {
    map[x][y].setAsVisited();
}

void Grid::setAsVisited(const Cell &cell) {
    map[cell.getX()][cell.getY()].setAsVisited();
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
}


Cell *Grid::getCell(int x, int y) { if (in_bounds(x,y)) { return &map[x][y]; } return nullptr; }

int Grid::isThisAValidRun() {
    // checks if there are any errors related to the start cell and the goal cell

    bool start = isThereAStart();
    bool goal = isThereAGoal();

    if (start && goal)
        return 0; // both start and goal cells are present, indicating a valid run

    else if (start && !goal)
        return 1; // start cell is present, but goal cell is missing

    else if (!start && goal)
        return 2; // goal cell is present, but start cell is missing

    else // !start && !goal
        return 3; // both start and goal cells are missing
}

void Grid::deepClean() {
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++) {
            map[i][j].clean();
            map[i][j].resetAsFree();
            map[i][j].resetTheStart();
            map[i][j].resetTheGoal();
        }
}
