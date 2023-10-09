//
// Created by Elia Innocenti on 07/10/23.
//

#ifndef ASTARSEARCH_ASTARSEARCH_H
#define ASTARSEARCH_ASTARSEARCH_H

// libraries
#include <utility>
#include <queue>

// classes
#include "Cell.h"
#include "Grid.h"

class AStarSearch {
public:

    // constructor
    explicit AStarSearch(Grid& grid);

    // destructor
    ~AStarSearch();

    // getter
    Grid* getGridPointer() const;

    // find the path
    void findPath();

private:

    Grid* grid; // pointer to the grid
    std::unordered_set<Cell> directions; // directions

    // search
    void aStarSearch(const Cell& start, const Cell& goal, std::unordered_map<Cell, Cell>& came_from, std::unordered_map<Cell, double>& cost_so_far);
    std::vector<Cell> neighbors(const Cell& cell);
    double heuristic(const Cell& from_node, const Cell& to_node) const;
    double cost(const Cell& from_node, const Cell& to_node) const;

    // reconstruct
    static std::vector<Cell> reconstructPath(const Cell& start, const Cell& goal, std::unordered_map<Cell, Cell>& came_from, std::unordered_map<Cell, double>& cost_so_far); // TODO check ugly path

};

struct PriorityQueue {
    // define a type for an element in the priority queue
    typedef std::pair<double, Cell> PQelement;

    // creates a priority queue using a vector as the underlying container,
    // and uses std::greater to ensure the highest priority (lowest value) is at the top
    std::priority_queue< PQelement, std::vector<PQelement>, std::greater<> > frontier;

    // checks if the priority queue is empty
    inline bool empty() const {
        return frontier.empty();
    }

    // adds an item to the priority queue with a specified priority
    inline void put(const Cell& item, double priority) {
        frontier.emplace(priority, item);
    }

    // gets the item with the highest priority (lowest value) from the priority queue.
    Cell get() {
        // retrieves the item with the highest priority (at the top of the queue)
        Cell best_item = frontier.top().second;

        // removes the item from the queue
        frontier.pop();

        // returns the item with the highest priority
        return best_item;
    }
};


#endif //ASTARSEARCH_ASTARSEARCH_H
