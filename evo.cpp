#include "evo.hpp"
#include "dataconst.hpp"
#include <algorithm>
#include <numeric>
#include <iostream>

inter_vitam_et_mortem::inter_vitam_et_mortem(int mestes, int vivus, int percent, int n,
                                             std::vector<long long> x, std::vector<long long> y)
    : spatium(mestes),
      food(mestes, 0),
      liquatorium(mestes * vivus / 100),
      magnitudo(mestes),
      muton(percent),
      numeri_heredes(liberi(mestes, mestes * vivus / 100)),
      N(n), X(x), Y(y) {}

void inter_vitam_et_mortem::creo(int musa)
{
    for (int i = 0; i < magnitudo; i++)
    {
        for (int j = 0; j < musa; j++)
        {
            spatium[i].statura(mut_param[randevu() % 4]);
        }
    }
}

void inter_vitam_et_mortem::foot()
{
    for (int i = 0; i < magnitudo; i++)
    {
        std::cout << food[i] * 1000 / (pactum(0, 0) * 100) << " ";
    }
    std::cout << std::endl;
}

void inter_vitam_et_mortem::conflictatio()
{
    for (int i = 0; i < magnitudo; i++)
    {
        for (int j = 0; j < N; j++)
        {
            food[i] += pactum(spatium[i].reed(X[j]), Y[j]);
        }
    }
}

std::vector<int> inter_vitam_et_mortem::sensus_vitae(int a1, int a2)
{
    int melior = std::max_element(food.begin(), food.end()) - food.begin();
    std::vector<int> apricots;
    for (int x = a1; x <= a2; x++)
    {
        apricots.push_back(spatium[melior].reed(x));
    }
    return apricots;
}

Genom inter_vitam_et_mortem::Victoria()
{
    auto Satietas = std::max_element(food.begin(), food.end());
    int melior = std::distance(food.begin(), Satietas);
    return spatium[melior];
}

void inter_vitam_et_mortem::Aula_Caelestis()
{
    //foot();

    std::vector<int> indices(magnitudo);
    std::iota(indices.begin(), indices.end(), 0);
    std::partial_sort(indices.begin(), indices.begin() + liquatorium, indices.end(),
                      [this](int i, int j)
                      { return food[i] > food[j]; });
    std::vector<int> favorites(indices.begin(), indices.begin() + liquatorium);
    std::vector<int> mortuos(indices.begin() + liquatorium, indices.end());

    for (int i : mortuos)
        food[i] = 0;
    int temp = 0;
    int index = 0;
    for (int i : mortuos)
    {
        if (temp == numeri_heredes[index])
        {
            temp = 0;
            index++;
        }
        spatium[i] = spatium[favorites[index]].mutate(muton);
        for (int j = 0; j < N; j++)
        {
            food[i] += pactum(spatium[i].reed(X[j]), Y[j]);
        }
        temp++;
    }
}