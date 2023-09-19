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
    Grid(int width, int height, bool random = true);

    static std::array<Cell, 4> DIRS;
private:
    int width, height;

    std::vector<std::vector<Cell>> map; //main data structure

    void makeRandomMap(int width, int height);
    void setRandomStart();
    void setRandomGoal();
    Cell* findFreeCell();

};

std::array<Cell, 4> Grid::DIRS = {
        /* East, West, North, South */
        Cell{1, 0}, Cell{-1, 0},
        Cell{0, -1}, Cell{0, 1}
};


#endif //ASTARSEARCH_GRID_H
