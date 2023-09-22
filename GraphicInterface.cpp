//
// Created by Elia Innocenti on 22/09/23.
//

#include "GraphicInterface.h"

GraphicInterface::GraphicInterface(Grid &grid) {
    this->grid = &grid;
}

void GraphicInterface::handleEvent(sf::RenderWindow &window) {
    // FIXME
    grid->findPath();
    int x = grid->getWidth();
    int y = grid->getHeight();
    Cell* cell;
    for (int i = 0; i < x; i++){
        for (int j = 0; j < y; j++){
            cell = grid->getCell(i,j);
            if (cell->getShape().getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))){
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    grid->updateCell(i, j);
                    grid->findPath();
                }
            }
        }
    }
    // FIXME - the cells of the old path has to be restored as free cell
}

void GraphicInterface::draw(sf::RenderWindow &window) {
    grid->draw(window);
}