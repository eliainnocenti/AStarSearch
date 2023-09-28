//
// Created by Elia Innocenti on 19/09/23.
//

#ifndef ASTARSEARCH_CELL_H
#define ASTARSEARCH_CELL_H

#include <cstdlib>
#include <memory>

// graphics
#include <SFML/Graphics.hpp>

class Cell {
public:
    // constructors
    Cell(int x, int y, unsigned int side);
    Cell(); // the default constructor is needed for came_from (std::unordered_set<Cell, Cell>) // TODO check

    // overloaded operators
    bool operator == (const Cell& other) const;
    bool operator != (const Cell& other) const;
    bool operator < (const Cell& other) const;

    // getters
    inline bool isTheStart() const { return start; }
    inline bool isTheGoal() const { return goal; }
    inline bool isAnObstacle() const { return obstacle; }
    inline bool isAPathElement() const { return path; }
    inline bool isVisited() const { return visited; }

    // setters
    inline void setTheStart() { start = true; }
    inline void setTheGoal() { goal = true; }
    inline void setAsObstacle() { obstacle = true; }
    inline void setAsPathElement() { path = true; }
    inline void setAsVisited() { visited = true; }
    inline void resetTheStart() { start = false; }
    inline void resetTheGoal() { goal = false; }
    inline void resetAsFree() { obstacle = false; }
    inline void clean() { path = false; visited = false; }

    // getters
    inline int getX() const { return x; }
    inline int getY() const { return y; }
    inline sf::RectangleShape getShape() const { return shape; }

    // setters
    inline void setX(int x) { this->x = x; }
    inline void setY(int y) { this->y = y; }

    // draw
    void draw(sf::RenderWindow &window);

private:
    int x, y; // position

    // graphics attributes
    unsigned int side;

    // cell sprite
    sf::RectangleShape shape;

    // attributes
    bool start {false};
    bool goal {false};
    bool obstacle {false};
    bool path {false};
    bool visited {false};
    // TODO - add boolean attributes
        // evaluated

    // graphics
    void setColor();

};

namespace std {
/* implement hash function so we can put Cell into an unordered_set */
    template<>
    struct hash<Cell> {
        std::size_t operator()(const Cell &id) const noexcept {
            return std::hash<int>()(id.getX() ^ (id.getY() << 16));
        }
    };
}

#endif //ASTARSEARCH_CELL_H