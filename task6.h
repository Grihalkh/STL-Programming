#pragma once
#include <iostream>
#include <vector>
#include <string>

// Lexical analiser

enum state : int { error = 0, inprogress, success };

// Abstract lexeme
class Lexeme
{
protected:
	int inner_state = 0;
public:
	Lexeme* next_lexeme = nullptr;

	Lexeme(Lexeme* next_lexeme)
	{
		this->next_lexeme = next_lexeme;
	}
	virtual state Check(char c) = 0;
	virtual std::string GetFormat() = 0;
};

// Class with some useful funcs
class Utils
{
public:
	static bool IsChar(char c)
	{
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
			return true;
		return false;
	}
	static bool IsNum(char c)
	{
		if (c >= '0' && c <= '9')
			return true;
		return false;
	}
	static bool IsCharOrNum(char c)
	{
		if (IsChar(c) || IsNum(c))
			return true;
		return false;
	}
	static std::string GetFormat(Lexeme* lexems)
	{
		std::string res = "";
		Lexeme* tmp = lexems;
		while (tmp != nullptr)
		{
			res += tmp->GetFormat();
			tmp = tmp->next_lexeme;
		}
		return res;
	}
	static bool NotInReserved(std::string full_var_name)
	{
		if (full_var_name == "and" ||
			full_var_name == "or")
			return false;
		return true;
	}
};

// Variable lexeme
class Variable : public Lexeme
{
private:
	std::string full_var_name = "";
public:
	Variable(Lexeme* next_lexeme) : Lexeme(next_lexeme) {}
	
	virtual std::string GetFormat() override
	{
		return "I";
	}

	virtual state Check(char c) override
	{
		switch (inner_state)
		{
		case 0:
			if (c == ' ') // пропускаем все пробелы
				return inprogress;
			if (Utils::IsChar(c)) // если в начале буква, переходим в след. состояние
			{
				inner_state = 1;
				full_var_name += c;
				return inprogress;
			}
			return error;

		case 1: // принимаем любые буквы или цифры
			if (Utils::IsCharOrNum(c))
			{
				full_var_name += c;
				return inprogress;
			}
			// пока не встретим один из символов, не явл. буквой или цифрой
			else if (Utils::NotInReserved(full_var_name))
				return success;
			return error;
		default:
			return error;
		}
	}
};

// operator '=' Lexeme
class Equal : public Lexeme
{
public:
	Equal(Lexeme* next_lexeme) : Lexeme(next_lexeme) {}

	virtual std::string GetFormat() override
	{
		return "=";
	}

	virtual state Check(char c) override
	{
		switch (inner_state)
		{
		case 0:
			if (c == ' ')
				return inprogress;
			if (c == '=')
			{
				inner_state = 1;
				return inprogress;
			}
			return error;
		case 1:
			return success;
		default:
			return error;
		}
	}
};

// operator '=', '<', '>', '<>' Lexemes
class Compare : public Lexeme
{
public:
	Compare(Lexeme* next_lexeme) : Lexeme(next_lexeme) {}

	virtual std::string GetFormat() override
	{
		return "(=|<>|<|>)";
	}

	virtual state Check(char c) override
	{
		switch (inner_state)
		{
		case 0:
			if (c == ' ') // пропускаем все пробелы
				return inprogress;
			if (c == '=' || c == '>') // если начинается с = или > переходим в состояние 1
			{
				inner_state = 1;
				return inprogress;
			}
			if (c == '<')
			{
				inner_state = 2;
				return inprogress;
			}
			return error;
		case 1: // если до этого был =,>,<>, то выходим
			return success;
		case 2:
			if (c != '>') // если символ после < не >, выходим
				return success;
			inner_state = 1;
			return inprogress; // иначе символ = >, переходим в состояние 1
		default:
			return error;
		}
	}
};

// operator 'and', 'or' Lexemes
class Logic : public Lexeme
{
public:
	Logic(Lexeme* next_lexeme) : Lexeme(next_lexeme) {}

	virtual std::string GetFormat() override
	{
		return "(and|or)";
	}

	virtual state Check(char c) override
	{
		switch (inner_state)
		{
		case 0:
			if (c == ' ') // пропускаем все пробелы
				return inprogress;
			if (c == 'a') // ветвь and
			{
				inner_state = 1;
				return inprogress;
			}
			if (c == 'o') // ветвь or
			{
				inner_state = 4;
				return inprogress;
			}
			return error;
		case 1:
			if (c == 'n')
			{
				inner_state = 2;
				return inprogress;
			}
			return error;
		case 2:
			if (c == 'd')
			{
				inner_state = 3;
				return inprogress;
			}
		case 3:
			if (c == ' ' || c == '(' || c == ')')
				return success;
			return error;
		case 4:
			if (c == 'r')
			{
				inner_state = 3;
				return inprogress;
			}
			return error;
		}
	}
};


// main function
void task()
{
	setlocale(LC_ALL, "rus");
	// expression structure in terms of lexems
	Lexeme* lexems = 
		new Variable(new Equal(
		new Variable(new Compare(new Variable(
		new Logic(
		new Variable(new Compare(new Variable(
		nullptr)))))))));

	std::string expression;

	std::cout << "Введите выражение формата:" << std::endl <<
		Utils::GetFormat(lexems) << std::endl;
	std::getline(std::cin, expression);

	int lexeme_index = 1;

	int c_index = 0;
	state s = lexems->Check(expression[c_index]);
	for (c_index = 0; c_index <= expression.size();)
	{
		switch (s)
		{
		case error:
			for (int i = 0; i < c_index; ++i)
				std::cout << "~";
			std::cout << "^" << std::endl;
			std::cout << "Ошибка синтаксиса в лексеме " << lexeme_index << std::endl;
			return;
		case success:
			lexeme_index++;
			lexems = lexems->next_lexeme;
			if (lexems == nullptr)
			{
				std::cout << "Проверка синтаксиса прошла успешно" << std::endl;
				return;
			}
			else
				s = lexems->Check(expression[c_index]);
			break;
		case inprogress:
			c_index++;
			s = lexems->Check(expression[c_index]);
			break;
		}
	}
	std::cout << "Произошла непредвиденная ошибка :(" << std::endl;
}