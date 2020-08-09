#include "assert.h"
#include <iostream>
#include <stdio.h>
#include <random>
#include <array>
#include <utility>
#include <functional>
#include <memory>

const unsigned int list_length = 10;
using int_list = std::array<unsigned int , list_length>;
using dist_range = std::pair<unsigned int , unsigned int>;
dist_range def_range = { 0, 99 };

void create_random_list_of_integers( int_list& ints , dist_range range ) {
    unsigned int count = ints.size( );
    assert( count );

    std::random_device randomizer;
    std::uniform_int_distribution<unsigned int> dist( range.first , range.second );

    for ( unsigned int c = 0; c < count; c++ ) {
        auto num = dist( randomizer );
        ints[c] = ( num );
    }
}

std::unique_ptr<int_list> int_randomizer( dist_range range = def_range ) {
    std::unique_ptr<int_list> ints = std::make_unique<int_list>( );
    create_random_list_of_integers( *ints.get( ) , range );
    return ints;
}

void print_list( int_list& list_ints ) {
    for ( auto int_i : list_ints ) {
        std::cout << int_i << ", ";
    }
    std::cout << std::endl;
}

bool smaller( unsigned int& first , unsigned int& second ) {
    return ( first <= second );
}

bool greater( unsigned int& first , unsigned int& second ) {
    return ( first >= second );
}

void swap( unsigned int& first , unsigned int& second ) {
    std::swap( first , second );
}

std::unique_ptr<int_list> bubble_sort( std::unique_ptr<int_list> p_ints ) {
    int_list& ints = *p_ints.get( );

    std::cout << __FUNCTION__ << ":: Unsorted list " << std::endl;
    print_list( ints );

    //inner loop compare head and head+1 and move head from begin to end-1
    //inner loop iterate over the integers from beginning to end - iteration
    //outer loop iterate size - 1 times and move temp end to end - iterations

    auto size_of_list = ints.size( );
    unsigned int full_pass_iterations = size_of_list - 1;

    for ( unsigned int full_passes_done = 0; full_passes_done < full_pass_iterations; full_passes_done++ ) {
        for ( unsigned int head = 0; head < ( full_pass_iterations - full_passes_done ); head++ ) {
            auto& first = ints[head];
            auto& second = ints[head + 1];

            if ( greater( first , second ) ) {
                swap( first , second );
            }
        }
    }

    std::cout << __FUNCTION__ << ":: Sorted list " << std::endl;
    print_list( ints );
    return p_ints;
}

void selection_sort( std::unique_ptr<int_list> p_ints ) {
    int_list& ints = *p_ints.get( );

    std::cout << __FUNCTION__ << ":: Unsorted list " << std::endl;
    print_list( ints );

    //inner loop compare head element to all others in the the list head vs head+(1...end)
    //outer loop move head (begin...end - 1)

    auto size_of_list = ints.size( );
    unsigned int full_pass_iterations = size_of_list - 1;

    for ( unsigned int full_passes_done = 0; full_passes_done < full_pass_iterations; full_passes_done++ ) {
        unsigned int head = full_passes_done;
        for ( unsigned int compare = head + 1; compare <= full_pass_iterations; compare++ ) {
            auto& first = ints[head];
            auto& second = ints[compare];

            if ( greater( first , second ) ) {
                swap( first , second );
            }
        }
    }

    std::cout << __FUNCTION__ << ":: Sorted list " << std::endl;
    print_list( ints );
}

void selection_sort_perf_opt( std::unique_ptr<int_list> p_ints ) {
    int_list& ints = *p_ints.get( );
    std::cout << __FUNCTION__ << ":: Unsorted list " << std::endl;
    print_list( ints );

    auto size_of_list = ints.size( );
    unsigned int full_pass_iterations = size_of_list - 1;

    for ( unsigned int full_passes_done = 0; full_passes_done < full_pass_iterations; full_passes_done++ ) {
        unsigned int head = full_passes_done;
        unsigned int minimum = head;

        for ( unsigned int compare = head + 1; compare <= full_pass_iterations; compare++ ) {
            auto& first = ints[minimum];
            auto& second = ints[compare];

            if ( greater( first , second ) ) {
                minimum = compare;
            }
        }

        if ( head != minimum ) {
            swap( ints[head] , ints[minimum] );
        }
    }

    std::cout << __FUNCTION__ << ":: Sorted list " << std::endl;
    print_list( ints );
}

unsigned int spot_insert_location( int_list& ints , unsigned int value , unsigned int end ) {
    unsigned int pos = 0;
    while ( pos < end ) {
        if ( ints[pos] > value ) {
            return pos;
        }
        pos++;
    }
}

void insert_into_sorted_array( int_list& ints , unsigned int insert_this , unsigned int insert_at ) {
    assert( insert_this > insert_at );

    auto value_of_interest = ints[insert_this];
    auto start_array_shift_at = insert_this;
    auto end_array_shift_at = insert_at;

    while ( start_array_shift_at > end_array_shift_at ) {
        ints[start_array_shift_at] = ints[start_array_shift_at - 1];
        start_array_shift_at--;
    }

    ints[end_array_shift_at] = value_of_interest;
}

void insertion_sort( std::unique_ptr<int_list> p_ints ) {
    int_list& ints = *p_ints.get( );
    std::cout << __FUNCTION__ << ":: Unsorted list " << std::endl;
    print_list( ints );

    auto sorted_head = 0u;
    auto sorted_end = 0u;
    auto compare = sorted_end + 1u;

    auto sorted_array_iterations = ints.size( ) - 1;

    for ( sorted_end = 0; sorted_end < sorted_array_iterations; sorted_end++ ) {
        compare = sorted_end + 1u;
        for ( auto sorted_item_of_interest = sorted_end; sorted_item_of_interest >= sorted_head; sorted_item_of_interest-- ) {
            if ( greater( ints[sorted_item_of_interest] , ints[compare] ) ) {
                auto insert_at = spot_insert_location( ints , ints[compare] , sorted_end );
                insert_into_sorted_array( ints , compare , insert_at );
            } else {
                break;
            }

            if ( sorted_item_of_interest == 0 ) {
                break;
            }
        }
    }

    std::cout << __FUNCTION__ << ":: Sorted list " << std::endl;
    print_list( ints );
}

void insertion_sort_perf_opt( std::unique_ptr<int_list> p_ints ) {
    int_list& ints = *p_ints.get( );
    std::cout << __FUNCTION__ << ":: Unsorted list " << std::endl;
    print_list( ints );

    //start with a sub-sorted list head and compare head + 1 with it.
    //increase the sub-sorted list to head+(0...n-1) and while comparing the nth element with
    //each element in the sorted sub array to find the place where it can be inserted

    auto sorted_head = 0u;
    auto sorted_end = 0u;
    auto compare = sorted_end + 1u;

    auto sorted_array_iterations = ints.size( ) - 1;

    for ( sorted_end = 0; sorted_end < sorted_array_iterations; sorted_end++ ) {
        compare = sorted_end + 1u;
        for ( auto sorted_item_of_interest = sorted_end; sorted_item_of_interest >= sorted_head; sorted_item_of_interest-- ) {
            if ( greater( ints[sorted_item_of_interest] , ints[compare] ) ) {
                swap( ints[compare] , ints[sorted_item_of_interest] );
                compare = sorted_item_of_interest;
            } else {
                break;
            }

            if ( sorted_item_of_interest == 0 ) {
                break;
            }
        }
    }

    std::cout << __FUNCTION__ << ":: Sorted list " << std::endl;
    print_list( ints );
}

void algo_merge_two_sorted_arrays( int_list& first_arr , int_list& sec_arr , std::array<unsigned int , 20>& final_arr ) {
    auto first_arr_itr = first_arr.begin( );
    auto sec_arr_itr = sec_arr.begin( );

    for ( auto& final_arr_itr : final_arr ) {
        if ( first_arr_itr == first_arr.end( ) ) {
            final_arr_itr = *sec_arr_itr;
            sec_arr_itr++;
        } else if ( sec_arr_itr == sec_arr.end( ) ) {
            final_arr_itr = *first_arr_itr;
            first_arr_itr++;
        } else if ( ( *first_arr_itr ) > ( *sec_arr_itr ) ) {
            final_arr_itr = *sec_arr_itr;
            sec_arr_itr++;
        } else {
            final_arr_itr = *first_arr_itr;
            first_arr_itr++;
        }
    }

    for ( auto int_i : final_arr ) {
        std::cout << int_i << ", ";
    }
    std::cout << std::endl;
}

//merge 2 sorted arrays
void merge_two_sorted_arrays( ) {
    std::cout << __FUNCTION__ << std::endl;
    auto first_arr = int_randomizer( );
    first_arr = bubble_sort( std::move( first_arr ) );
    auto sec_arr = int_randomizer( );
    sec_arr = bubble_sort( std::move( sec_arr ) );

    std::array<unsigned int , 20> final_arr { 0 };

    algo_merge_two_sorted_arrays( *first_arr , *sec_arr , final_arr );
}

//merge sort
void merge_sort( std::unique_ptr<int_list> p_ints ) {
    int_list& ints = *p_ints;

    auto begin = 0;
    auto end = ints.size( );
    auto mid = begin + end / 2;
}

int main( ) {
    bubble_sort( int_randomizer( ) );
    selection_sort( int_randomizer( ) );
    selection_sort_perf_opt( int_randomizer( ) );
    insertion_sort( int_randomizer( ) );
    insertion_sort_perf_opt( int_randomizer( ) );

    merge_two_sorted_arrays( );
}
