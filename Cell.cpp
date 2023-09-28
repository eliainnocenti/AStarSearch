//
// Created by Elia Innocenti on 19/09/23.
//

#include "Cell.h"

Cell::Cell(int x, int y, unsigned int side) : x(x), y(y), side(side) {

    // graphics
    shape.setSize({float(side), float(side)});
    shape.setPosition(float(x*side), float(y*side));
    shape.setOutlineThickness(0.5);
    shape.setOutlineColor(sf::Color::Black);

}

Cell::Cell() : Cell(x, y, side) {}

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

void Cell::draw(sf::RenderWindow &window) {
    // TODO - put some comments
    setColor();
    window.draw(shape);
}

void Cell::setColor() {
    // FIXME - some attributes miss (visited, evaluated)
    // TODO - chose RGB color (change some)
    if (obstacle)
        shape.setFillColor(sf::Color::Black);
    else if (start)
        shape.setFillColor(sf::Color::Green);
    else if (goal)
        shape.setFillColor(sf::Color::Red);
    else if (path)
        shape.setFillColor(sf::Color::Blue);
    else if (visited)
        shape.setFillColor(sf::Color::Cyan);
    else
        shape.setFillColor(sf::Color::White);
}