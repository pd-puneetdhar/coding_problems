#include "assert.h"
#include <iostream>
#include <stdio.h>
#include <random>
#include <array> 
#include <utility>
#include <functional>
#include <memory>

using int_list = std::array<unsigned int, 30>;
using dist_range = std::pair<unsigned int, unsigned int>;

void create_random_list_of_integers(int_list& ints, dist_range range) {
    unsigned int count = ints.size();
    assert(count);
    
    std::random_device randomizer;
    std::uniform_int_distribution<unsigned int> dist(range.first, range.second);
    
    for (unsigned int c = 0; c < count; c++) {
        auto num = dist(randomizer);
        ints[c]=(num);
    }
}

std::unique_ptr<int_list> int_randomizer(dist_range range) {
    std::unique_ptr<int_list> ints = std::make_unique<int_list>() ;
    create_random_list_of_integers(*ints.get(), range);
    return ints;
}

void print_list (int_list& list_ints) {
    for (auto int_i : list_ints) {
        std::cout << int_i << ", " ;
    }
    std::cout << std::endl;
}

bool smaller (unsigned int& first, unsigned int& second) {
    return (first <= second);
}

bool greater (unsigned int& first, unsigned int& second) {
    return (first >= second);
}

bool swap (unsigned int& first, unsigned int& second) {
    std::swap(first, second);
}

void bubble_sort(std::unique_ptr<int_list> p_ints) {
    int_list& ints = *p_ints.get();

    std::cout << __FUNCTION__ << ":: Unsorted list " << std::endl;
    print_list(ints);

    //inner loop compare head and head+1 and move head from begin to end-1 
    //inner loop iterate over the integers from beginning to end - iteration 
    //outer loop iterate size - 1 times and move temp end to end - iterations
    
    auto size_of_list = ints.size();
    unsigned int full_pass_iterations = size_of_list - 1;

    for (unsigned int full_passes_done = 0; full_passes_done < full_pass_iterations; full_passes_done++) {
        for (unsigned int head = 0; head < (full_pass_iterations - full_passes_done); head++ ) {

            auto& first = ints[head]; 
            auto& second = ints[head+1];
        
            if (greater(first, second)) {
                swap(first, second);
            }
        }
    }

    std::cout << __FUNCTION__ << ":: Sorted list " << std::endl;
    print_list(ints);

}

void selection_sort(std::unique_ptr<int_list> p_ints) {
    int_list& ints = *p_ints.get();

    std::cout << __FUNCTION__ << ":: Unsorted list " << std::endl;
    print_list(ints);

    //inner loop compare head element to all others in the the list head vs head+(1...end)
    //outer loop move head (begin...end - 1)
    
    auto size_of_list = ints.size();
    unsigned int full_pass_iterations  = size_of_list - 1;
    
    for (unsigned int full_passes_done = 0; full_passes_done < full_pass_iterations; full_passes_done++) {
        unsigned int head = full_passes_done;
        for (unsigned int compare = head+1; compare <= full_pass_iterations; compare++) {
            
            auto& first = ints[head];
            auto& second = ints[compare];
            
            if (greater(first, second)) {
                swap(first, second);
            }
        }
    }

    std::cout << __FUNCTION__ << ":: Sorted list " << std::endl;
    print_list(ints);

}


void selection_sort_perf_opt(std::unique_ptr<int_list> p_ints) {
    int_list& ints = *p_ints.get();
    std::cout << __FUNCTION__ << ":: Unsorted list " << std::endl;
    print_list(ints);

    auto size_of_list = ints.size();
    unsigned int full_pass_iterations  = size_of_list - 1;
    
    for (unsigned int full_passes_done = 0; full_passes_done < full_pass_iterations; full_passes_done++) {
        unsigned int head = full_passes_done;
        unsigned int minimum = head; 

        for (unsigned int compare = head+1; compare <= full_pass_iterations; compare++) {
            auto& first = ints[minimum];
            auto& second = ints[compare];
            
            if (greater(first, second)) {
                minimum = compare;
            }
        }
        
        if (head != minimum) {
            swap(ints[head], ints[minimum]);
        }
    }

    std::cout << __FUNCTION__ << ":: Sorted list " << std::endl;
    print_list(ints);
}

int main () {

    dist_range range = { 0, 99}; 
    bubble_sort(int_randomizer(range));    
    selection_sort(int_randomizer(range));
    selection_sort_perf_opt(int_randomizer(range));
}
