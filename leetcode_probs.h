#pragma once
/*Given an array of integers , return indices of the two numbers such that they add up to a specific target.
You may assume that each input would have exactly one solution , and you may not use the same element twice.
Example:
Given nums = [ 2 , 7 , 11 , 15 ] , target = 9 ,
Because nums[ 0 ] + nums[ 1 ] = 2 + 7 = 9 ,
return[ 0 , 1 ].
*/
#include <vector>
#include <unordered_map>

std::vector<int> twoSum( std::vector<int>& nums , int target ) {
#if SLOW
	auto size_of_array = nums.size( );
	auto slow_itr = 0;
	auto fast_itr = 0;
	auto result = 0;
	while ( slow_itr < size_of_array - 1 ) {
		fast_itr = slow_itr + 1;
		while ( fast_itr < size_of_array ) {
			result = ( nums[ slow_itr ] + nums[ fast_itr ] );
			if ( result == target ) {
				break;
			}
			fast_itr++;
		}
		if ( result == target ) {
			break;
		}
		slow_itr++;
	}
	return { slow_itr,fast_itr };
#else if USE_HASH_MAP_FOR_PERF
	using tkey = unsigned int;
	using tvalue = int;
	std::unordered_map<tkey , tvalue> lookup_complement;
	auto indices = 0;
	for ( auto n : nums ) {
		lookup_complement.insert( std::make_pair( n , indices ) );
		indices++;
	}

	indices = 0;
	tvalue res = -1;
	for ( auto n : nums ) {
		tkey compliment_to_be_found = target - n;
		if ( lookup_complement.find( compliment_to_be_found ) != lookup_complement.end( ) ) {
			res = lookup_complement.at( compliment_to_be_found );
			if ( res != indices ) {
				return { indices, res };
			}
		}
		indices++;
	}

	return { -1, -1 };
#else //USE_SINGLE_PASS HASH MAP

#endif

}

void test_leet( ) {
	std::vector<int> input { 3, 2, 4 };
	auto target = 6;
	auto result = twoSum( input , target );
	std::cout << result.at( 0 ) << " , " << result.at( 1 ) << std::endl;
}