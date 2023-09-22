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

    GraphicInterface(Grid& grid); // FIXME ?

    void handleEvent(); // TODO
    void draw(sf::RenderWindow &window);

private:
    Grid* grid; // FIXME ?
};


#endif //ASTARSEARCH_GRAPHICINTERFACE_H
