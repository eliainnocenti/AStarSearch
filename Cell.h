//
// Created by Elia Innocenti on 19/09/23.
//

#ifndef ASTARSEARCH_CELL_H
#define ASTARSEARCH_CELL_H

#include <cstdlib>
#include <memory>

class Cell {
public:
    Cell(int x, int y);

    bool operator==(const Cell &other) const;

    bool operator!=(const Cell &other) const;
    //bool operator < (const Cell& other) const; //TODO

    inline bool isTheStart() const { return start; }
    inline bool isTheGoal() const { return goal; }
    inline bool isAnObstacle() const { return obstacle; }

    inline void setTheStart() { start = true; }
    inline void setTheGoal() { goal = true; }
    inline void setAsObstacle() { obstacle = true; }

    inline int getX() const { return x; }
    inline int getY() const { return y; }

    inline void setX(int x) { this->x = x; }
    inline void setY(int y) { this->y = y; }

private:
    int x, y;

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
