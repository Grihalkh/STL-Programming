#pragma once

#include <set>
#include <vector>
#include <time.h>
#include <iostream>
#include <algorithm>

// Enter U from console;
// A is picked at random (random indices from U);
// B is picked manually (A != B, A and B should have an intersection)

// Do A and B
// Do not ( not A or not B)
// Should be the same

// Output 30% largest elements

template<typename T>
void print_vector(const std::vector<T>& s)
{
	std::for_each(s.begin(), s.end(), [](const T& i)
		{
			std::cout << i << " ";
		});

	std::cout << std::endl;
}

template<typename T>
void print_set(const std::set<T> &s)
{
	std::for_each(s.begin(), s.end(), [](const T &i) 
		{
			std::cout << i << " ";
		});
	
	std::cout << std::endl;
}


void task()
{
	srand(time(NULL));

	std::set<int> U, A, B;
	
	// Entering U
	std::cout << "Enter number of elements for U:";
	int nU; std::cin >> nU;
	std::cout << "Enter elements for U:" << std::endl;
	for (int i = 0; i < nU; ++i)
	{
		int tmp; std::cin >> tmp;
		U.insert(tmp);
	}

	// Enter A
	// pick random set length from 1 to n-1
	int nA = rand() % ((nU - 1) - (1) + 1) + 1;
	for (int i = 0; i < nA; ++i)
	{
		// pick random set index from 0 to n-1
		int tmp = rand() % ((nU - 1) + 1);
		tmp = *std::next(U.begin(), tmp);
		A.insert(tmp);
	}

	std::cout << "Set A:" << std::endl;

	print_set(A);

	// Enter B
	bool bSetOk = false;
	while (!bSetOk)
	{
		std::cout << "B should be subset of U, should not be equal to A and should have an intersection with A" << std::endl;
		std::cout << "Enter number of elements for B:";
		int nB; std::cin >> nB;
		std::cout << "Enter elements for B:" << std::endl;
		for (int i = 0; i < nB; ++i)
		{
			int tmp; std::cin >> tmp;
			B.insert(tmp);
		}

		std::vector<int> intersection;
		std::set_intersection(A.begin(), A.end(), B.begin(), B.end(), std::back_inserter(intersection));
		// Checks
		if (std::includes(U.begin(), U.end(), B.begin(), B.end()) && // is in U
			intersection.size() && // A and B have an intersection
			!(intersection.size() == A.size() && intersection.size() == B.size()) // A != B
			)
		{
			bSetOk = true;
		}
		else
		{
			B.empty();
			std::cout << "You have entered B incorrectly! Repeat input." << std::endl;
		}
	}

	// Main Prog
	// A and B
	std::vector<int> intersection1;
	std::set_intersection(A.begin(), A.end(), B.begin(), B.end(), std::back_inserter(intersection1));

	// not A, not B
	std::vector<int> notA, notB;
	std::set_difference(U.begin(), U.end(), A.begin(), A.end(), std::back_inserter(notA));
	std::set_difference(U.begin(), U.end(), B.begin(), B.end(), std::back_inserter(notB));

	// not A or not B
	std::vector<int> tmp;
	std::set_union(notA.begin(), notA.end(), notB.begin(), notB.end(), std::back_inserter(tmp));
	// not (not A or not B)
	std::vector<int> intersection2;
	std::set_difference(U.begin(), U.end(), tmp.begin(), tmp.end(), std::back_inserter(intersection2));

	// Output
	std::cout << "A and B:" << std::endl;
	print_vector(intersection1);
	std::cout << "not (not A and not B):" << std::endl;
	print_vector(intersection2);

	// out 30 % largest
	std::cout << "30% largest:" << std::endl;
	if (std::equal(intersection1.begin(), intersection1.end(), intersection2.begin()))
	{
		int n = 0.3 * intersection1.size();
		if (n == 0)
		{
			std::cout << "There 30% gives us 0 elements :)" << std::endl;
			return;
		}
		for (int i = 0; i < n; ++i)
		{
			auto max = std::max_element(intersection1.begin(), intersection1.end());
			std::cout << *max << " ";
			intersection1.erase(max);
		}
	}
	std::cout << std::endl;
}