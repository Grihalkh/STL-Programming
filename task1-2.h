#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T>
void print_mat(vector< vector<T> > matrix)
{
	for (auto& row : matrix)
	{
		for (auto& el : row)
			cout << el << " ";
		cout << endl;
	}
}

void task()
{
	int n = 4;
	vector< vector<int> > A = {
		{ 0, 2, -3, -9},
		{-4, 5, -6, -3},
		{-7, 8,  0,  4},
		{-7, 8, -7,  4}
	};

	cout << "Init matrix" << endl;
	print_mat(A);

	cout << "Enter row num [0;" << n-1 << "] : ";
	int row; cin >> row;

	// Program starts here

	// Finding first and last negative in given row

	vector<int>::iterator first_negative = find_if(A.at(row).begin(), A.at(row).end(),
		[](int i) { return i < 0; });

	vector<int>::reverse_iterator last_negative = find_if(A.at(row).rbegin(), A.at(row).rend(),
		[](int i) { return i < 0; });

	// Doubling everything between first and last negative
	for (auto i = first_negative + 1; i < last_negative.base() - 1; ++i)
		(*i) = (*i) * 2;

	cout << "Matrix after doubling elements" << endl;
	print_mat(A);

	// Reversing elements in a row
	reverse(A.at(row).begin(), A.at(row).end());

	cout << "Matrix after reverse" << endl;
	print_mat(A);

	// Finding number of zero elements on main diagonal
	int cnt_zero = 0;

	for (int j = 0; j < n; ++j)
	{
		if (A[j][j] == 0)
			cnt_zero++;
	}
	
	if (cnt_zero % 2 == 0)
	{
		// Finding the min element of the last row and replacing zeros with it
		auto min_el = min_element(A.at(n - 1).begin(), A.at(n - 1).end());

		for (int j = 0; j < n; ++j)
		{
			if (A[j][j] == 0)
				A[j][j] = *min_el;
		}
	}

	cout << "Matrix after min on diag" << endl;
	print_mat(A);

	// Finding repeating rows and deleting them

	for (auto one_row = A.begin(); one_row < A.end() - 1; ++one_row)
	{
		for (auto other_row = one_row + 1; other_row < A.end(); ++other_row)
		{
			if (equal(one_row->begin(), one_row->end(), other_row->begin()))
			{
				A.erase(other_row);
				// recovering pointer
				other_row = one_row;
			}
		}
	}

	cout << "Matrix after deleting repeating rows" << endl;
	print_mat(A);
}