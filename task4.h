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
	std::string sub = "евм123456789";

	std::string new_sub;

	// Формируем новую подстроку
	for (auto& el : word_arr)
		for (char c : el)
			if (sub.find(c) != std::string::npos)
				new_sub += c;

	std::cout << "Новая подстрока: " << new_sub << std::endl;

	int cnt = 0;
	// Меняем цифры на DD
	for (std::string::iterator it = new_sub.begin(); it != new_sub.end(); ++it)
		if (std::isdigit(*it))
		{
			new_sub.replace(it, it + 1, "DD");
			cnt++;
		}

	std::cout << "Подстрока после замены цифр на DD: " << new_sub << std::endl;

	// Удаляем символы в начале и формируем предложение
	std::string sentence;

	for (auto& el : word_arr)
	{
		el.erase(0, cnt);
		sentence += el;
	}

	std::cout << "Предложение из урезанных слов: " << sentence << std::endl;

	std::reverse(word.begin(), word.end());

	std::cout << "Финальное предложение: " << word + sentence << std::endl;
}