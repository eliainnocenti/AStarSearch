//
// Created by Elia Innocenti on 19/09/23.
//

#include "Cell.h"

Cell::Cell(int x, int y) : x(x), y(y) {}

Cell::Cell() : Cell(x, y) {}

bool Cell::operator == (const Cell &other) const {
    if (other.getX() == x && other.getY() == y)
        return true;
    return false;
}

bool Cell::operator != (const Cell &other) const {
    if (other.getX() != x || other.getY() != y)
        return true;
    return false;
}


bool Cell::operator < (const Cell &other) const {
    int other_x = other.getX();
    int other_y = other.getY();
    return std::tie(x, y) < std::tie(other_x, other_y);
}
