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
	std::string sub = "���123456789";

	std::string new_sub;

	// ��������� ����� ���������
	for (auto& el : word_arr)
		for (char c : el)
			if (sub.find(c) != std::string::npos)
				new_sub += c;

	std::cout << "����� ���������: " << new_sub << std::endl;

	int cnt = 0;
	// ������ ����� �� DD
	for (std::string::iterator it = new_sub.begin(); it != new_sub.end(); ++it)
		if (std::isdigit(*it))
		{
			new_sub.replace(it, it + 1, "DD");
			cnt++;
		}

	std::cout << "��������� ����� ������ ���� �� DD: " << new_sub << std::endl;

	// ������� ������� � ������ � ��������� �����������
	std::string sentence;

	for (auto& el : word_arr)
	{
		el.erase(0, cnt);
		sentence += el;
	}

	std::cout << "����������� �� ��������� ����: " << sentence << std::endl;

	std::reverse(word.begin(), word.end());

	std::cout << "��������� �����������: " << word + sentence << std::endl;
}