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
    Cell(int x, int y);
    Cell(); // the default constructor is needed for came_from (std::unordered_set<Cell, Cell>) // TODO check

    // overloaded operators
    bool operator == (const Cell& other) const;
    bool operator != (const Cell& other) const;
    bool operator < (const Cell& other) const;

    // getter
    inline bool isTheStart() const { return start; }
    inline bool isTheGoal() const { return goal; }
    inline bool isAnObstacle() const { return obstacle; }

    // setter
    inline void setTheStart() { start = true; }
    inline void setTheGoal() { goal = true; }
    inline void setAsObstacle() { obstacle = true; }
    inline void resetTheStart() { start = false; }
    inline void resetTheGoal() { goal = false; }

    // getter
    inline int getX() const { return x; }
    inline int getY() const { return y; }

    // setter
    inline void setX(int x) { this->x = x; }
    inline void setY(int y) { this->y = y; }

private:
    int x, y; //position

    // attributes
    bool start {false};
    bool goal {false};
    bool obstacle {false};

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