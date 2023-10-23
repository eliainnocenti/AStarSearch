
// libraries
#include <iostream>

// graphics
#include <SFML/Graphics.hpp>

// classes
#include "Grid.h"
#include "GraphicInterface.h"
#include "AStarSearch.h"

int main() {

    // seed the random number generator
    srand(static_cast<unsigned>(time(nullptr)));

    // create a grid
    //Grid grid(50, 30, false, true, 3); // Default
    Grid grid(57, 36, false, true, 3); // Fullscreen

    // create a solver (AStarSearch instance)
    AStarSearch a_star_search(grid);

    // checks if a valid run can be performed on the grid
    switch (grid.isThisAValidRun()) {

       case 0:
           // no error, proceed with execution
           break;

       case 1:
           // error: The Goal Cell is missing
           std::cerr << "The Goal Cell is missing." << std::endl;
           return 1;

       case 2:
           // error: The Start Cell is missing
           std::cerr << "The Start Cell is missing." << std::endl;
           return 2;

       case 3:
           // error: Both the Start Cell and the Goal Cell are missing
           std::cerr << "The Start Cell and the Goal Cell are missing." << std::endl;
           return 3;

       default:
           // unidentified error
           std::cerr << "Unidentified error." << std::endl;
           return 4;

    }

    // graphics

    // create a graphic user interface
    GraphicInterface interface(a_star_search);

    // create an event object to handle events
    sf::Event event {};

    unsigned int cellSide = 25;

    // Default
    unsigned int windowWidth = cellSide * grid.getWidth(); // set the width of the window
    unsigned int windowHeight = cellSide * grid.getHeight(); // set the height of the window

    // create the SFML window
    //sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "AStarSearch", sf::Style::Default); // Default
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "AStarSearch", sf::Style::Fullscreen); // Fullscreen

    // main application loop
    while (window.isOpen()) {
        // poll and handle events
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close(); // close the window when the close button is clicked
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close(); // close the window when the Escape key is pressed
            }
        }

        // main application logic

        // clearing the old frame and preparing for drawing the new one
        window.clear(sf::Color::White);

        // update and draw
        interface.handleEvent(window);
        interface.draw(window);

        // bring to screen and display the new frame just drawn
        window.display();
    }

}