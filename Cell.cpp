//
// Created by Elia Innocenti on 19/09/23.
//

#include "Cell.h"

Cell::Cell(int x, int y, unsigned int side) : x(x), y(y), side(side) {

    // graphics
    shape.setSize({float(side), float(side)});
    shape.setPosition(float(y*side), float(x*side));
    shape.setOutlineThickness(0.5);
    shape.setOutlineColor(sf::Color::Black);

}

Cell::Cell() : Cell(0, 0, 25) {}

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

Cell &Cell::operator = (const Cell &other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
        side = other.side;
        start = other.start;
        goal = other.goal;
        obstacle = other.obstacle;
        path = other.path;
        visited = other.visited;
        // the sprite is not copied, it is not needed
    }
    return *this;
}

void Cell::draw(sf::RenderWindow &window) {
    // draw function

    setColor();
    window.draw(shape);
}

void Cell::setColor() {
    // sets the right color for each cell based on its quality

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