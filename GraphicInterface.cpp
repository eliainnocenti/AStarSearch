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

    // if a cell is clicked, it is set as an obstacle / free cell

    bool isMouseClickProcessed = false; // flag to track whether a mouse click has been processed

    // get the dimensions of the grid
    unsigned int width = grid->getWidth();
    unsigned int height = grid->getHeight();

    Cell* cell; // declare a pointer to a Cell object

    // loop through each cell in the grid
    for (int i = 0; i < width; i++){
        for (int j = 0; j < height; j++){
            cell = grid->getCell(i,j); // get the cell at the current coordinates // FIXME in non-square grid
            if (cell != nullptr) {
                // check if the mouse cursor is within the bounds of the current cell
                if (cell->getShape().getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))){
                    // check if the left mouse button is pressed and a click has not been processed yet
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !isMouseClickProcessed) {

                        grid->resetPathDrawn(); // delete the old path
                        grid->updateCell(i, j); // update the cell (obstacle <-> free cell)
                        grid->findPath(); // re-find the path

                        isMouseClickProcessed = true; // set the flag to indicate that a mouse click has been processed
                        sf::sleep(sf::milliseconds(100)); // add a brief pause to prevent rapid multiple clicks
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