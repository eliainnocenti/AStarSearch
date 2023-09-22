//
// Created by Elia Innocenti on 22/09/23.
//

#include "GraphicInterface.h"

GraphicInterface::GraphicInterface(Grid &grid) {
    this->grid = &grid;
}

void GraphicInterface::handleEvent() {
    // TODO
    // get input from mouse and keyboard
        // if the button is pressed
        int x = 0, y = 0; // get the coordinates
        //grid->updateCell(x,y);
        grid->findPath();
}

void GraphicInterface::draw(sf::RenderWindow &window) {
    grid->draw(window);
}