#pragma once
#include <map>
#include <vector>
#include <functional>
int randevu();

// Арифметические операции
extern long long fp(long long a, long long b);
extern long long fm(long long a, long long b);

// Словари
inline std::map<char, int> numerus;   // словрь букву в число
inline std::map<int, char> mut_param; // словарь для функции мутации(число с 1до4 -> буква)
inline std::map<char, std::function<long long(long long, long long)>> f_pm_1;
// Константы
long long pactum(long long a, long long b);
std::vector<int> liberi(int a, int b);
extern int cogitatio;
extern int champ;
extern int supervivere;
extern int mutatio;
extern long long max_error;
