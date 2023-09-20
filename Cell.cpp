//
// Created by Elia Innocenti on 19/09/23.
//

#include "Cell.h"

Cell::Cell(int x, int y) : x(x), y(y) {

}

bool Cell::operator==(const Cell &other) const {
    if (other.getX() == x && other.getY() == y)
        return true;
    return false;
}

bool Cell::operator!=(const Cell &other) const {
    if (other.getX() != x || other.getY() != y)
        return true;
    return false;
}

/*
bool Cell::operator < (const Cell &other) const {
    return std::tie(x, y) < std::tie(other.getX(), other.getY());
}
 */