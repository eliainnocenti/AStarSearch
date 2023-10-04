//
// Created by Elia Innocenti on 22/09/23.
//

#ifndef ASTARSEARCH_GRAPHICINTERFACE_H
#define ASTARSEARCH_GRAPHICINTERFACE_H

#include "Grid.h"
#include "Cell.h"

// graphics
#include <SFML/Graphics.hpp>

class GraphicInterface {
public:
    // constructor
    explicit GraphicInterface(Grid& grid);

    // graphics
    void handleEvent(sf::RenderWindow &window);
    void draw(sf::RenderWindow &window);

private:
    std::unique_ptr<Grid> grid;
};


#endif //ASTARSEARCH_GRAPHICINTERFACE_H