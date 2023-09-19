//
// Created by Elia Innocenti on 19/09/23.
//

#include "Grid.h"

Grid::Grid(int width, int height, bool random) : width(width), height(height) {
    if (random)
        makeRandomMap(width, height);
}

void Grid::makeRandomMap(int width, int height) {

    //TODO -> some cell has to be obstacles (randomly)
    for (int i = 0; i < width; i ++) {
        //map.emplace_back();
        for (int j = 0; j < height; j++) {
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
}