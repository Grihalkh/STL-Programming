#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <locale>

// var 25

/*
��� ������ ����, ����� � ���������. ������������ ����� ���������, ���� � ������ ����� �� �������,
������� ������ � �������� ���������. � ���������� ��������� ��� ����� �������� �� ��������� �DD�. 
������������ ����������� �� ���� �������, ������ � ������ ����� ������� ������ ��������, ������� 
���� ��������� ����� � ���������� ���������. �������� � ����� ����������� ������������ �������� �����.
*/

void task()
{
	setlocale(LC_ALL, "rus");

	std::vector<std::string> word_arr = { "��1���", "�7���", "�1��", "!" };
	std::string word = "��������������";
	std::string sub = "���";

	std::vector<std::string> new_word_arr;

	for (char el : sub)
	{
		for (int i = 0; i < word_arr.size(); ++i)
		{
			if (word_arr[i].find(el) != std::string::npos)
				new_word_arr[i].append(el);
		}
		
	}
}