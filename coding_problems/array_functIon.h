#pragma once
#include <iostream>
//Given an unsorted array A of size N of non - negative integers,
//find a continuous sub - array which adds to a given number S.

namespace  sub_arrary_with_sum {
	typedef struct sub_array {
		unsigned int start{ 0xFFFFFFFF };
		unsigned int end{ 0xFFFFFFFF };
	};


	sub_array find_sub_array_with_sum(int* A, unsigned int N, unsigned int sum) {
		using namespace std;


		sub_array sa{ 0,0 };
		unsigned int temp_sum{ 0 };
		bool found{ false };
		for (int start = 0, end = 0; end < N; end++) {
			temp_sum = temp_sum + A[end];

			if (temp_sum > sum) {
				while (temp_sum > sum) {
					temp_sum -= A[sa.start];
					sa.start++;

					if (sa.start == end) {
						break;
					}

				}
			}

			if (temp_sum == sum) {
				found = true;
				break;
			}
			sa.end = end;
		}

		if (found == true) {
			cout << "Sub Array found"
				<< " - start index = " << sa.start
				<< ", end index = " << sa.end
				<< endl;
		}
		else {
			cout << "Sub Array Not Found " << endl;
		}

		return sa;
	}

	void test_find_sub_array_with_sum() {
		int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
		sub_array test_sa = find_sub_array_with_sum(a, 10, 18);
	}

}