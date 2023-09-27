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

// graphics
#include <SFML/Graphics.hpp>

class Grid {
public:
    // constructor
    explicit Grid(int width, int height, bool diagonal = false, bool random = true, bool constCost = true);

    // A*Search
    void findPath();

    // set the start
    void setTheStart(int x, int y);
    void setTheStart(const Cell& cell);

    // set the goal
    void setTheGoal(int x, int y);
    void setTheGoal(const Cell& cell);

    // set an obstacle
    void setAnObstacle(int x, int y);
    void setAnObstacle(const Cell& cell);

    // getters
    inline int getWidth() const { return width; }
    inline int getHeight() const { return height; }
    inline std::shared_ptr<Cell> getStartCell() const { return startCell; }
    inline std::shared_ptr<Cell> getGoalCell() const { return goalCell; }
    inline Cell* getCell(int x, int y) { return &map[x][y]; }

    // extra
    void printAllTheObstacles() const;
    void printAllTheGrid() const;

    // graphics
    void draw(sf::RenderWindow &window);
    void updateCell(int x, int y);
    void resetPathDrawn(); // FIXME - can be optimized if it use the path vector instead of scrolling through the entire map

private:
    int width, height; // size

    std::vector<std::vector<Cell>> map; // main data structure
    //std::unordered_map<std::pair<Cell, Cell>, double> weights; // TODO

    // pointers to the Start and the Goal
    std::shared_ptr<Cell> startCell {nullptr};
    std::shared_ptr<Cell> goalCell {nullptr};

    // directions
    bool diagonalMovements;
    std::unordered_set<Cell> directions;

    // graphics
    unsigned int cellSide;

    // mapmaker
    void makeMap(int width, int height, unsigned int cellSide);
    void makeRandomMap(int width, int height, unsigned int cellSide); // TODO
    std::array<int, 2> setRandomStart();
    std::array<int, 2> setRandomGoal();

    // search
    bool in_bounds(const Cell& cell) const;
    bool passable(const Cell& cell) const;
    std::vector<Cell> neighbors(const Cell& cell) const; // FIXME - diagonal movement is not allowed through walls
    double heuristic(const Cell& from_node, const Cell& to_node) const;
    double cost(const Cell& from_node, const Cell& to_node) const; // TODO - possible GridWithWeights implementation
                                                                   // si può utilizzare un dizionario che mette in relazione
                                                                   // un arco e il relativo costo
                                                                   // la funzione cost() ritornerebbe il costo dati
                                                                   // i nodi e la struttura dati
                                                                   // std::unordered_map<std::pair<Cell,Cell>,double> weights
                                                                   // le celle devono però essere adiacenti (deve esistere l'arco)
    void aStarSearch(const Cell& start, const Cell& goal, std::unordered_map<Cell, Cell>& came_from, std::unordered_map<Cell, double>& cost_so_far); // FIXME

    // reconstruct
    std::vector<Cell> reconstructPath(const Cell& start, const Cell& goal, std::unordered_map<Cell, Cell>& came_from, std::unordered_map<Cell, double>& cost_so_far); // TODO check ugly path
    void printPath(const std::vector<Cell>& path, const Cell& start, const Cell& goal) const;
    void printPosition(const Cell& cell) const;
    void printInfo(const Cell& cell) const;

    // graphics
    void setThePath(const std::vector<Cell>& path);

    // extra
    std::vector<Cell> findAllTheObstacles() const;
    bool isThereAStart() const;
    bool isThereAGoal() const;

    // reset
    void reset(); // TODO

};

#endif //ASTARSEARCH_GRID_H