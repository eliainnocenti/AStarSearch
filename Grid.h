//
// Created by Elia Innocenti on 19/09/23.
//

#ifndef ASTARSEARCH_GRID_H
#define ASTARSEARCH_GRID_H

#include <vector>
#include <array>
#include <unordered_map>
#include <unordered_set>

#include "Cell.h"
#include "PriorityQueue.h"

class Grid {
public:
    //constructor
    Grid(int width, int height, bool random = true);

    //directions
    static std::array<Cell, 4> DIRS;

    //A*Search
    void findPath(); //TODO


private:
    int width, height; //size

    std::vector<std::vector<Cell>> map; //main data structure

    //data structure for the algorithm
    std::unordered_map<Cell*, Cell*> came_from;
    std::unordered_map<Cell*, double> cost_so_far;

    //mapmaker
    void makeRandomMap(int width, int height);
    void setRandomStart();
    void setRandomGoal();
    Cell* findFreeCell();

    //search
    bool in_bounds() const; //TODO
    bool passable() const; //TODO
    std::vector<Cell> neighbors() const; //TODO
    double heuristic() const; //TODO
    double cost() const; //TODO
    void a_star_search(); //TODO

    //reconstruct
    std::vector<Cell> reconstruct_path(); //TODO

    //reset
    void reset(); //TODO


};

std::array<Cell, 4> Grid::DIRS = {
        // East, West, North, South
        Cell{1, 0}, Cell{-1, 0},
        Cell{0, -1}, Cell{0, 1}
};


#endif //ASTARSEARCH_GRID_H