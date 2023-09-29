//
// Created by Elia Innocenti on 19/09/23.
//

#ifndef ASTARSEARCH_PRIORITYQUEUE_H
#define ASTARSEARCH_PRIORITYQUEUE_H

#include <utility>
#include <queue>

// define a templated structure for a Priority Queue
template<typename T, typename priority_t>
struct PriorityQueue {

    // define a type for an element in the priority queue.
    typedef std::pair<priority_t, T> PQElement;

    // creates a priority queue using a vector as the underlying container,
    // and uses std::greater to ensure the highest priority (lowest value) is at the top.
    std::priority_queue<PQElement, std::vector<PQElement>, std::greater<PQElement>> elements;

    // checks if the priority queue is empty
    inline bool empty() const {
        return elements.empty();
    }

    // adds an item to the priority queue with a specified priority
    inline void put(T item, priority_t priority) {
        elements.emplace(priority, item);
    }

    // gets the item with the highest priority (lowest value) from the priority queue.
    T get() {
        // retrieves the item with the highest priority (at the top of the queue)
        T best_item = elements.top().second;

        // removes the item from the queue
        elements.pop();

        // returns the item with the highest priority
        return best_item;
    }
};

#endif //ASTARSEARCH_PRIORITYQUEUE_H