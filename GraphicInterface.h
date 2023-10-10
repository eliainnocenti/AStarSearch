//
// Created by Elia Innocenti on 22/09/23.
//

#ifndef ASTARSEARCH_GRAPHICINTERFACE_H
#define ASTARSEARCH_GRAPHICINTERFACE_H

// classes
#include "Grid.h"
#include "Cell.h"
#include "AStarSearch.h"

// graphics
#include <SFML/Graphics.hpp>

class GraphicInterface {
public:
    // constructor
    explicit GraphicInterface(AStarSearch& a_star_search);

    // destructor
    ~GraphicInterface();

    // graphics
    void handleEvent(sf::RenderWindow &window);
    void draw(sf::RenderWindow &window);

private:
    Grid* grid; // pointer to the grid
    AStarSearch* a_star_search; // pointer to the searcher (AStarSearch instance) // TODO - change "searcher" into something else

};

#endif //ASTARSEARCH_GRAPHICINTERFACE_H