#include "assert.h"
#include <iostream>
#include <stdio.h>
#include <random>
#include <array> 
#include <utility>

using int_list = std::array<unsigned int, 30>;

void create_random_list_of_integers(int_list& ints, std::pair<unsigned int, unsigned int> range) {
    unsigned int count = ints.size();
    assert(count);
    
    std::random_device randomizer;
    std::uniform_int_distribution<unsigned int> dist(range.first, range.second);
    
    for (unsigned int c = 0; c < count; c++) {
        auto num = dist(randomizer);
        ints[c]=(num);
    }
}

void print_list (int_list list_ints) {
    for (auto int_i : list_ints) {
        std::cout << int_i << ", " ;
    }
    std::cout << std::endl;
}

bool greater (unsigned int& first, unsigned int& second) {
    return (first >= second);
}

bool swap (unsigned int& first, unsigned int& second) {
    std::swap(first, second);
}

void bubble_sort(int_list& list_ints) {
    
    auto size_of_list = list_ints.size();
    
    unsigned int full_pass_iterations = size_of_list - 1;
    unsigned int sorted_places = 0;
    
    for (unsigned int full_passes_done = 0; full_passes_done < full_pass_iterations; full_passes_done++) {
        for (unsigned int head = 0; head < (full_pass_iterations - full_passes_done); head++ ) {

            auto& first = list_ints[head]; 
            auto& second = list_ints[head+1];
        
            if (greater(first, second)) {
                swap(first, second);
            }
        }
    }
}

int main () {
    int_list l_ints  = {0}; 
    
    create_random_list_of_integers(l_ints, {0, 99});
    std::cout << "UnSorted List" << std::endl;
    print_list(l_ints);
    bubble_sort(l_ints);    
    std::cout << "Sorted List" << std::endl;
    print_list(l_ints);
}
