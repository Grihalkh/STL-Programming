#pragma once

#include <iostream>
#include <functional>
#include <string>
#include <vector>
#include <map>
#include <locale>

// � ������� �������� ��������, ��� ������ ��� +3 � *4 ������ ����� �� 5 �� 40
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

    // ������ ��� �������
    std::cout << "~ ~ ������ ��� ������� ~ ~" << std::endl;
    std::cout << "�������� � " << start << ", ����������� " << end << ". ��������: +" << op_plus << ", *" << op_mult << std::endl << std::endl;

    int branchCount = 0;

    std::function<void (int, int, std::string)> calc = [&calc, &branchCount](int x, int fin, std::string way)
    {
        branchCount++;
        if (x < fin)
        {
            calc(x + op_plus, fin, way + "+" + std::to_string(op_plus));
            if (x != 0) // �������� ����������� ���������
                calc(x * op_mult, fin, way + "*" + std::to_string(op_mult));
        }
        else if (x == fin)
            std::cout << way << std::endl;
    };
    
    calc(start, end, "");
    std::cout << "���������� ���������:" << branchCount << std::endl;



    // ������ ��� ������� � �������������. ���������� ������ ��������� ����� ���� �� ���� �� �����-�������������
    std::cout << std::endl << "~ ~ ������ ��� ������� � ������������� ~ ~" << std::endl;
    std::cout << "�������� � " << start << ", ����������� " << end << ". ����������� = " << vector_to_string(restrictions) << 
        ". ��������: +" << op_plus << ", *" << op_mult << std::endl << std::endl;

    branchCount = 0;

    std::function<void (int, int, std::string, const std::vector<int>&, bool, std::vector<int>)> calc_restricted =
        [&calc_restricted, &branchCount]
        (int x, int fin, std::string way, const std::vector<int>& restrictions, bool okToPrint, std::vector<int> metConditions)
    {
        branchCount++;

        for (auto& el : restrictions)
            if (x == el) // ���� ���� �������� ����� ���� �� �������� - �����������
            {
                okToPrint = true;
                metConditions.push_back(el);
            }

        if (x < fin)
        {
            calc_restricted(x + op_plus, fin, way + "+" + std::to_string(op_plus), restrictions, okToPrint, metConditions);
            if (x != 0) // �������� ����������� ���������
                calc_restricted(x * op_mult, fin, way + "*" + std::to_string(op_mult), restrictions, okToPrint, metConditions);
        }
        else if (x == fin && okToPrint)
            std::cout << way << ", ���� ������ ����� " << vector_to_string(metConditions) << std::endl;
    };

    calc_restricted(start, end, "", restrictions, false, std::vector<int>());
    std::cout << "���������� ���������:" << branchCount << std::endl;



    // �������� ��� �������
    std::cout << std::endl << "~ ~ �������� ��� ������� ~ ~" << std::endl;
    std::cout << "�������� � " << end << ", ����������� " << start << ". ��������: -" << op_plus << ", /" << op_mult << std::endl;
    std::cout << "NB: ������� �������������, ������� �������������" << std::endl << std::endl;

    branchCount = 0;

    std::function<void (int, int, std::string)> calc_reverse = [&calc_reverse, &branchCount](int x, int fin, std::string way)
    {
        branchCount++;
        if (x > fin)
        {
            calc_reverse(x - op_plus, fin, way + "-" + std::to_string(op_plus));
            if (x != 0 && x % op_mult == 0) // �������� ����������� ��������� + �������� �� �������
                calc_reverse(x / op_mult, fin, way + "/" + std::to_string(op_mult));
        }
        else if (x == fin)
            std::cout << way << std::endl;
    };

    calc_reverse(end, start, "");
    std::cout << "���������� ���������:" << branchCount << std::endl;



    // ������ ��� ������� � ������� �������� ������������
    std::cout << std::endl << "~ ~ ������ ��� ������� � ������� �������� ������������ ~ ~" << std::endl;
    std::cout << "�������� � " << start << ", ����������� " << end << ". ��������: +" << op_plus << ", *" << op_mult << std::endl << std::endl;

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

    std::cout << "������ �������� ������������:" << std::endl;
    for (auto& el : phase)
    {
        std::string t = "���";
        if (el.second % 10 == 2 || el.second % 10 == 3 || el.second % 10 == 4)
            t += "�";
        std::cout << "����� " << el.first << " ������ " << el.second << " " << t << std::endl;
    }
    std::cout << "���������� ���������:" << branchCount << std::endl;
}