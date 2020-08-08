
#include "assert.h"
#include <stdio.h>
#include <random>

void create_random_list_of_integers(std::list<unsigned int>& ints, unsigned int count, std::pair<unsigned int, unsigned int> range) {
    assert(count);
    
    std::random_device randomizer;
    std::uniform_int_distribution<unsigned int> dist(range.first, range.second);
    
    for (unsigned int c = 0; c < count; c++) {
        auto num = dist(randomizer);
        num.push_back
    }
}

void bubble_sort() {
    
}

int main () {
    create_random_list_of_integers(100, {0, 99});
    bubble_sort();    
}
