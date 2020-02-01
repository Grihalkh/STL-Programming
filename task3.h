#pragma once

#include <set>
#include <time.h>
#include <iostream>
#include <algorithm>
#include <iterator>

// Enter U from console;
// A is picked at random (random indices from U);
// B is picked manually (A != B, A and B should have an intersection)

// Do A and B
// Do not ( not A or not B)
// Should be the same

// Output 30% largest elements

template<typename T>
void print_set(const std::set<T> &s)
{
	for (auto i = s.begin(); i != s.end(); ++i)
		std::cout << *i << " ";
	/*
	std::for_each(s.begin(), s.end(), [](const T &i) 
		{
			std::cout << i << " ";
		});
	*/
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

		std::set<int> intersection;
		std::set_intersection(A.begin(), A.end(), B.begin(), B.end(), intersection);
		// Checks
		if (std::includes(U.begin(), U.end(), B.begin(), B.end()) && // is in U
			!std::equal(A.begin(), A.end(), B.begin()) && // A != B
			intersection.size()) // A and B have an intersection
			bSetOk = true;
		else
		{
			B.empty();
			std::cout << "You have entered B incorrectly! Repeat input." << std::endl;
		}
	}
}