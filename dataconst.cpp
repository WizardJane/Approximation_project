#include <iostream>
#include <map>
#include <functional>
#include <vector>
#include <algorithm>
#include <numeric>
#include <fstream>
#include <utility>
#include <cmath>
#include "dataconst.hpp"

int randevu() { return rand() % 100 + 1; }

// Арифметические операции
long long fp(long long a, long long b) { return a + b; }
long long fm(long long a, long long b) { return a - b; }
std::vector<int> liberi(int a, int b)
{                                // a-количество мест, b-количество выживших
    std::vector<int> domi(b, 0); // domi-список с количеством потомков(сами себя не считаем)
    a -= b;
    for (int i = 1; i < b; i++)
    {
        domi[i - 1] += (a / 2);
        a -= (a / 2);
    }
    domi[b - 1] += a;
    return domi;
}
long long pactum(long long a, long long b)
{                                 // максимальная ошибка
    int passus = 100;             // шаг порога(делением)
    int summum_rating = 0;        // максимальное количество баллов
    int damna = 0;                // потеря
    std::vector<long long> limen; // пороги

    long long c = b - a;
    if (c < 0)
        c = -c;
    if (c > max_error)
        return 0;

    long long cur = max_error;
    while (cur > 0)
    {
        limen.push_back(cur);
        cur /= passus;
    }
    if (limen.back() != 1)
        limen.push_back(1);

    for (int i = 1; i < limen.size(); i++)
    {
        long long high = limen[i - 1];                               // верхняя граница интерала
        long long low = limen[i] + 1;                                // нижняя граница интервала
        long long len = high - low + 1;                              // его длина
        long long pondus = static_cast<long long>(limen.size() - i); // вес

        summum_rating += len * pondus;
        if (c >= low)
        {
            long long taken = std::min(c, high) - low + 1;
            damna += (taken * pondus);
        }
    }
    return summum_rating - damna;
}
int cogitatio = 3;
int champ = 10;
int supervivere = 30;
int mutatio = 35;
long long max_error = 10000000;