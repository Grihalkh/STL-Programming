#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// 11 var

struct info
{
	string fam, name;
	int app_num;
	//float debt;
};

class info_compare
{
public:
	bool operator()(const info& A, const info& B) const
	{ return A.app_num < B.app_num; }
};

void task()
{
	multimap <float, info> appartments;

	int n; cin >> n;

	info tmp;
	float tmp_debt = 0;

	// Input

	for (int i = 0; i < n; ++i)
	{
		cin >> tmp.fam
			>> tmp.name
			>> tmp.app_num
			>> tmp_debt;
		appartments.insert(make_pair(tmp_debt, tmp));
	}

	// Task

	// Fill array of debts
	vector<float> debts;

	for (auto i = appartments.begin(); i != appartments.end(); ++i)
	{
		debts.push_back(i->first);
	}


	// All equal -> get first 60%
	if (adjacent_find(debts.begin(), debts.end(), not_equal_to<>()) == debts.end())
	{
		int end_n = n * 0.6;

		for (int i = 1; i <= end_n; ++i)
			cout << i << endl;
		return;
	}
	
	// Not all equal -> get 80% from max
	float max_debt = *max_element(debts.begin(), debts.end());
	float search_debt = 0.8 * max_debt;

	// Print all flats which debt is more than search_debt
	for (auto appartment = appartments.begin(); appartment != appartments.end(); ++appartment)
	{
		if (appartment->first > search_debt)
			cout << appartment->second.app_num << endl;
	}
}