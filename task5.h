#pragma once

#include <iostream>
#include <functional>
#include <string>
#include <vector>
#include <map>
#include <locale>

// Я поменял значения варианта, ибо только при +3 и *4 нельзя дойти из 5 до 40
const int start = 5, end = 40;
const int op_plus = 5, op_mult = 4;
const std::vector<int> restrictions = { 20, 25 };

template<typename T>
std::string vector_to_string(const std::vector<T>& vec)
{
    std::string res;
    bool first = true;
    for (auto& el : vec)
    {
        if (!first)
            res += ", ";
        res += std::to_string(el);
        first = false;
    }
    return res;
}

void task()
{
    setlocale(LC_ALL, "rus");

    // Прямой ход расчета
    std::cout << "~ ~ Прямой ход расчета ~ ~" << std::endl;
    std::cout << "Начинаем с " << start << ", заканчиваем " << end << ". Операции: +" << op_plus << ", *" << op_mult << std::endl << std::endl;

    int branchCount = 0;

    std::function<void (int, int, std::string)> calc = [&calc, &branchCount](int x, int fin, std::string way)
    {
        branchCount++;
        if (x < fin)
        {
            calc(x + op_plus, fin, way + "+" + std::to_string(op_plus));
            if (x != 0) // Избегаем бесконечных ветвлений
                calc(x * op_mult, fin, way + "*" + std::to_string(op_mult));
        }
        else if (x == fin)
            std::cout << way << std::endl;
    };
    
    calc(start, end, "");
    std::cout << "Количество ветвлений:" << branchCount << std::endl;



    // Прямой ход расчета с ограничениями. Траектория должна проходить через хотя бы одно из чисел-ограничителей
    std::cout << std::endl << "~ ~ Прямой ход расчета с ограничениями ~ ~" << std::endl;
    std::cout << "Начинаем с " << start << ", заканчиваем " << end << ". Ограничения = " << vector_to_string(restrictions) << 
        ". Операции: +" << op_plus << ", *" << op_mult << std::endl << std::endl;

    branchCount = 0;

    std::function<void (int, int, std::string, const std::vector<int>&, bool, std::vector<int>)> calc_restricted =
        [&calc_restricted, &branchCount]
        (int x, int fin, std::string way, const std::vector<int>& restrictions, bool okToPrint, std::vector<int> metConditions)
    {
        branchCount++;

        for (auto& el : restrictions)
            if (x == el) // Если путь проходит через одно из значений - ограничений
            {
                okToPrint = true;
                metConditions.push_back(el);
            }

        if (x < fin)
        {
            calc_restricted(x + op_plus, fin, way + "+" + std::to_string(op_plus), restrictions, okToPrint, metConditions);
            if (x != 0) // Избегаем бесконечных ветвлений
                calc_restricted(x * op_mult, fin, way + "*" + std::to_string(op_mult), restrictions, okToPrint, metConditions);
        }
        else if (x == fin && okToPrint)
            std::cout << way << ", путь прошел через " << vector_to_string(metConditions) << std::endl;
    };

    calc_restricted(start, end, "", restrictions, false, std::vector<int>());
    std::cout << "Количество ветвлений:" << branchCount << std::endl;



    // Обратный ход расчета
    std::cout << std::endl << "~ ~ Обратный ход расчета ~ ~" << std::endl;
    std::cout << "Начинаем с " << end << ", заканчиваем " << start << ". Операции: -" << op_plus << ", /" << op_mult << std::endl;
    std::cout << "NB: Деление целочисленное, остаток отбрасывается" << std::endl << std::endl;

    branchCount = 0;

    std::function<void (int, int, std::string)> calc_reverse = [&calc_reverse, &branchCount](int x, int fin, std::string way)
    {
        branchCount++;
        if (x > fin)
        {
            calc_reverse(x - op_plus, fin, way + "-" + std::to_string(op_plus));
            if (x != 0 && x % op_mult == 0) // Избегаем бесконечных ветвлений + порверка на деление
                calc_reverse(x / op_mult, fin, way + "/" + std::to_string(op_mult));
        }
        else if (x == fin)
            std::cout << way << std::endl;
    };

    calc_reverse(end, start, "");
    std::cout << "Количество ветвлений:" << branchCount << std::endl;



    // Прямой ход расчета с выводом фазового пространства
    std::cout << std::endl << "~ ~ Прямой ход расчета с выводом фазового пространства ~ ~" << std::endl;
    std::cout << "Начинаем с " << start << ", заканчиваем " << end << ". Операции: +" << op_plus << ", *" << op_mult << std::endl << std::endl;

    branchCount = 0;
    std::map<int, int> phase;

    std::function<int (int, int)> calc_with_phase = [&calc_with_phase, &branchCount, &phase](int x, int fin)
    {
        branchCount++;

        if (x == fin)
            phase[x] = 1;


        if (phase.count(x))
            return phase[x];
        
        if (x < fin)
        {
            phase[x] = calc_with_phase(x + op_plus, fin) + calc_with_phase(x * op_mult, fin);
            return phase[x];
        }
        return 0;
    };

    calc_with_phase(start, end);

    std::cout << "Вектор фазового пространства:" << std::endl;
    for (auto& el : phase)
    {
        std::string t = "раз";
        if (el.second % 10 == 2 || el.second % 10 == 3 || el.second % 10 == 4)
            t += "а";
        std::cout << "Через " << el.first << " прошли " << el.second << " " << t << std::endl;
    }
    std::cout << "Количество ветвлений:" << branchCount << std::endl;
}