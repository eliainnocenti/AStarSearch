#include <iostream>

// graphics
#include <SFML/Graphics.hpp>

// classes
#include "Grid.h"
#include "Cell.h"
#include "GraphicInterface.h"

int main() {

    // seed the random number generator
    srand(static_cast<unsigned>(time(nullptr)));

    // create a grid
    Grid grid(64, 40, false, true, 3);

    // FIXME - solve when the findPath() function is called, but there is neither the start cell nor the goal cell (no random settings)

    // create a graphic user interface
    GraphicInterface interface(grid);

    // create an event object to handle events
    sf::Event event {};

    //---------DEBUG----------------------------------------------------------------------------------------------------
    // FIXME - graphic settings (fullscreen)

    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    unsigned int screenWidth = desktopMode.width;
    unsigned int screenHeight = desktopMode.height;

    //std::cout << "screenWidth: " << screenWidth << std::endl;
    //std::cout << "screenHeight: " << screenHeight << std::endl;

    // Macbook 13,3 pollici (2560 × 1600) // rapporto schermo 16:10
    unsigned int macbookWidth = 2560;
    unsigned int macbookHeight = 1600;

    //sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "AStarSearch", sf::Style::Fullscreen);
    //sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "AStarSearch", sf::Style::Fullscreen);
    //sf::RenderWindow window(sf::VideoMode(macbookWidth, macbookHeight), "AStarSearch", sf::Style::Fullscreen);

    std::cout << grid.getCellSide();

    //------------------------------------------------------------------------------------------------------------------

    unsigned int windowWidth = 20 * grid.getWidth(); // set the width of the window
    unsigned int windowHeight = 20 * grid.getHeight(); // set the height of the window

    // create the SFML window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "AStarSearch", sf::Style::Default);

    // main application loop
    while (window.isOpen()) {
        // poll and handle events
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close(); // close the window when the close button is clicked
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close(); // close the window when the Escape key is pressed
                // TODO - do i have to put the reset() function here?
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