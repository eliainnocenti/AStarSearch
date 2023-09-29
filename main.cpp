#include <iostream>

// graphics
#include <SFML/Graphics.hpp>

// classes
#include "Grid.h"
#include "Cell.h"
#include "GraphicInterface.h"

int main() {

    // TODO - put some comments

    srand(static_cast<unsigned>(time(nullptr)));

    Grid grid(30, 30, false, true, 2);

    GraphicInterface interface(grid);

    sf::Event event {};

    //---------DEBUG----------------------------------------------------------------------------------------------------
    // FIXME - graphic settings (videomode and fullscreen)

    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    unsigned int screenWidth = desktopMode.width;
    unsigned int screenHeight = desktopMode.height;

    //std::cout << "screenWidth: " << screenWidth << std::endl;
    //std::cout << "screenHeight: " << screenHeight << std::endl;

    // Macbook 13,3 pollici (2560 × 1600) // rapporto schermo 16:10
    unsigned int macbookWidth = 2560;
    unsigned int macbookHeight = 1600;

    //sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "AStarSearch", sf::Style::Fullscreen);
    //sf::RenderWindow window(sf::VideoMode(macbookWidth, macbookHeight), "AStarSearch", sf::Style::Fullscreen);
    //sf::RenderWindow window(sf::VideoMode(width * 25, height * 25), "AStarSearch", sf::Style::Default);

    //window.setFramerateLimit(60);

    //------------------------------------------------------------------------------------------------------------------

    unsigned int windowWidth = 750;
    unsigned int windowHeight = 750;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "AStarSearch", sf::Style::Default);

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
                // TODO - do i have to put the reset() function here?
            }
        }

        // clearing the old frame and preparing for drawing the new one
        window.clear(sf::Color::White);

        // update project and draw
        interface.handleEvent(window);
        interface.draw(window);

        // bring to screen and display the new frame just drawn
        window.display();
    }
}