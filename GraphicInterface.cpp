//
// Created by Elia Innocenti on 22/09/23.
//

#include "GraphicInterface.h"

GraphicInterface::GraphicInterface(Grid &grid) {
    this->grid = std::make_unique<Grid>(grid);
}

void GraphicInterface::handleEvent(sf::RenderWindow &window) {
    // TODO - put some comments
    grid->findPath();
    // FIXME - to be optimized (mouse click especially)
    unsigned int width = grid->getWidth();
    unsigned int height = grid->getHeight();
    Cell* cell;
    for (int i = 0; i < width; i++){
        for (int j = 0; j < height; j++){
            cell = grid->getCell(i,j);
            if (cell->getShape().getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))){
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    grid->resetPathDrawn();
                    grid->updateCell(i, j);
                    grid->findPath();
                }
            }
        }
    }

    // FIXME - reset() function
    //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        //grid.reset();
}

void GraphicInterface::draw(sf::RenderWindow &window) {
    grid->draw(window);
}