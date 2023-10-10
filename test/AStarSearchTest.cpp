//
// Created by Elia Innocenti on 10/10/23.
//

// libraries
#include "gtest/gtest.h"
#include "../AStarSearch.h"

// default constructor test
TEST (AStarSearch, DefaultConstructor) {
    AStarSearch a_star_search;

    // the AStarSearch default constructor must set the pointer to the grid to nullptr
    ASSERT_EQ(nullptr, a_star_search.getGridPointer());

    // the AStarSearch default constructor must set the default directions to North, East, South and West
    std::unordered_set<Cell> default_directions { Cell{0,1},  Cell{1,0}, Cell{0,-1}, Cell{-1,0} };
    ASSERT_EQ(default_directions, a_star_search.getDirections());
}

//