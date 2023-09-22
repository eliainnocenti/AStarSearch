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
    GraphicInterface(Grid& grid); // FIXME ?

    void handleEvent(sf::RenderWindow &window); // FIXME
    void draw(sf::RenderWindow &window);

private:
    Grid* grid; // FIXME ? - do i need a shared_ptr/unique_ptr
};


#endif //ASTARSEARCH_GRAPHICINTERFACE_H
