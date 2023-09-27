#include <iostream>

#include "Grid.h"
#include "Cell.h"
#include "GraphicInterface.h"

int main() {

    srand(static_cast<unsigned>(time(nullptr)));

    Grid grid(30,30, false, true);

    //grid.setTheStart(1,2);
    //grid.setTheGoal(25,20);

    GraphicInterface interface(grid);

    sf::Event event{};

    // FIXME - graphic settings (videomode and fullscreen)

    //sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    int windowWidth = 800;
    int windowHeight = 800;

    // TODO - put some comments
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "AStarSearch", sf::Style::Default);

    //window.setFramerateLimit(60);

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
                if (event.key.code == sf::Keyboard::Space)
                    grid.findPath();
            }
        }

        // Clearing the old frame and preparing for drawing the new one
        window.clear(sf::Color::White);

        // project update and draw
        interface.handleEvent(window);
        interface.draw(window);

        // Bring to screen and display the new frame just drawn
        window.display();
    }
}