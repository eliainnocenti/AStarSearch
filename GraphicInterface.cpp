//
// Created by Elia Innocenti on 22/09/23.
//

#include "GraphicInterface.h"

GraphicInterface::GraphicInterface(AStarSearch& a_star_search) {
    // allocates memory

    this->grid = a_star_search.getGridPointer();
    this->a_star_search = &a_star_search;
}

void GraphicInterface::handleEvent(sf::RenderWindow &window) {
    // if a cell is clicked, it is set as an obstacle / free cell

    // finds the path
    a_star_search->findPath();

    bool isMouseClickProcessed = false; // flag to track whether a mouse click has been processed

    // get the dimensions of the grid
    unsigned int width = grid->getWidth();
    unsigned int height = grid->getHeight();

    Cell* cell; // declare a pointer to a Cell object

    // loop through each cell in the grid
    for (int i = 0; i < width; i++){
        for (int j = 0; j < height; j++){
            cell = grid->getCell(j,i); // get the cell at the current coordinates
            if (cell != nullptr) {
                // check if the mouse cursor is within the bounds of the current cell
                if (cell->getShape().getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))){
                    // check if the left mouse button is pressed and a click has not been processed yet
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !isMouseClickProcessed) {

                        grid->resetPathDrawn(); // delete the old path
                        grid->updateCell(j, i); // update the cell (obstacle <-> free cell)
                        a_star_search->findPath(); // re-find the path

                        isMouseClickProcessed = true; // set the flag to indicate that a mouse click has been processed
                        sf::sleep(sf::milliseconds(100)); // add a brief pause to prevent rapid multiple clicks
                    }
                }
            }
        }
    }

    // instead of re-run the program, it can be restarted by regenerating a new random map and a new start and goal
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        grid->reset();
        a_star_search->findPath();
    }

}

void GraphicInterface::draw(sf::RenderWindow &window) {
    grid->draw(window);
}