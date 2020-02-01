#pragma once

#pragma once

#include <iostream>
#include <vector>

using namespace std;

void task()
{
	vector<float> v = { 1.0, -2.0, -3.0, 4.0 };

	float sum = 0;
	int cnt = 0;

	for (auto el = v.begin(); el != v.end(); ++el)
	{
		if (*el < 0)
		{
			sum += *el; cnt++;
		}
	}

	cout << "Mean = " << sum / cnt << endl;
}