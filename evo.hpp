#pragma once
#include <iostream>
#include <map>
#include <functional>
#include <vector>
#include <algorithm>
#include <numeric>
#include <fstream>
#include <utility>
#include <cmath>
#include "Genome.hpp"
#include "dataconst.hpp"
class inter_vitam_et_mortem
{
private:
    std::vector<Genom> spatium;      // вектор геномов
    std::vector<long long> food;     // количество баллов, которые набрал геном
    int liquatorium;                 // колличество геномов, прошедших эпоху
    int magnitudo;                   // места
    int muton;                       // вероятность мутации буквы в гене
    std::vector<int> numeri_heredes; // вектор мест, которые будут занимать выжившие в зависимости от их успешности
    int N;                           // колличество точек
    std::vector<long long> X;        // координата x
    std::vector<long long> Y;        // координата y

public:
    // конструктор
    inter_vitam_et_mortem(int mestes, int vivus, int percent, int n, std::vector<long long> x, std::vector<long long> y);

    // создание первых геномов
    void creo(int musa);

    // вывод food
    void foot();

    // первичное заполнение баллов
    void conflictatio();

    // вывод значений на промежутки лучшего генома
    std::vector<int> sensus_vitae(int a1, int a2);

    // лучший геном
    Genom Victoria();

    void Aula_Caelestis();
};