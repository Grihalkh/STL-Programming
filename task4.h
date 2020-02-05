#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <locale>

// var 25

/*
Дан массив слов, слово и подстрока. Сформировать новую подстроку, взяв в каждом слове те символы,
которые входят в заданную подстроку. В полученной подстроке все цифры заменить на подстроку “DD”. 
Сформировать предложение из слов массива, удалив в каждом слове столько первых символов, сколько 
было выполнено замен в полученной подстроке. Добавить в конец предложения перевернутое заданное слово.
*/

void task()
{
	setlocale(LC_ALL, "rus");

	std::vector<std::string> word_arr = { "Пр1вет", "в7ему", "м1ру", "!" };
	std::string word = "погромирование";
	std::string sub = "евм";

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