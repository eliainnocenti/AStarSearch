//
// Created by Elia Innocenti on 22/09/23.
//

#ifndef ASTARSEARCH_GRAPHICINTERFACE_H
#define ASTARSEARCH_GRAPHICINTERFACE_H

#include "Grid.h"
#include "Cell.h"
#include "AStarSearch.h"

// graphics
#include <SFML/Graphics.hpp>

class GraphicInterface {
public:
    // constructor
    explicit GraphicInterface(Grid& grid, AStarSearch& a_star_search);

    // graphics
    void handleEvent(sf::RenderWindow &window);
    void draw(sf::RenderWindow &window);

private:
    std::shared_ptr<Grid> grid; //
    AStarSearch* a_star_search; //
};


#endif //ASTARSEARCH_GRAPHICINTERFACE_H