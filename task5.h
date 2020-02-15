#pragma once

#include <iostream>
#include <functional>
#include <string>
#include <map>

const int start = 2, end = 8;

void task()
{
    // Прямой ход расчета
    int breanchCount = 0; // Счётчик просмотренных веток дерева
    std::function<int(int, int, std::string)> calc = [&calc, &breanchCount](int x, int fin, std::string way)
    {
        breanchCount++;
        if (x < fin) return calc(x + 1, fin, way + " +1") + calc(x * 2, fin, way + " *2");
        else
            if (x == fin) {
                std::cout << way << std::endl;
                return 1;
            }
        return 0;
    };
    std::cout << "Forward\nCount: " << calc(start, end, "") << std::endl;
    std::cout << "breanchCount:" << breanchCount << std::endl;
    breanchCount = 0;
}