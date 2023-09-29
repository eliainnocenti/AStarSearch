//
// Created by Elia Innocenti on 22/09/23.
//

#include "GraphicInterface.h"

GraphicInterface::GraphicInterface(Grid &grid) {
    this->grid = std::make_unique<Grid>(grid);
}

void GraphicInterface::handleEvent(sf::RenderWindow &window) {

    // finds the path
    grid->findPath();

    //---------DEBUG----------------------------------------------------------------------------------------------------
    // FIXME - to be optimized (mouse click)

    // if a cell is clicked, it is set as an obstacle / free cell
    unsigned int width = grid->getWidth();
    unsigned int height = grid->getHeight();
    Cell* cell;
    for (int i = 0; i < width; i++){
        for (int j = 0; j < height; j++){
            cell = grid->getCell(i,j); // FIXME
            if (cell != nullptr) {
                if (cell->getShape().getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))){
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        grid->resetPathDrawn(); // delete the old path
                        grid->updateCell(i, j); // update the cell (obstacle <-> free cell)
                        grid->findPath(); // re-find the path
                    }
                }
            }
        }
    }

    //---------DEBUG----------------------------------------------------------------------------------------------------
    // FIXME - reset() function

    // instead of re-run the program, it can be restarted by regenerating a new random map and a new start and goal
    /*
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        grid.reset();
        */

    //------------------------------------------------------------------------------------------------------------------
}

void GraphicInterface::draw(sf::RenderWindow &window) {
    grid->draw(window);
}