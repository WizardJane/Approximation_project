#include <iostream>
#include <map>
#include <functional>
#include <vector>
#include <algorithm>
#include <numeric>
#include <fstream>
#include <utility>
#include <cmath>
#include <fstream>
#include <sstream>
#include <cctype>
#include <string>
#include "dataconst.hpp"
#include <matplot/matplot.h>
#include "evo.hpp"

double curve(double x, std::vector<long long> &coefs)
{
    double y = 0;
    double x_deg = 1; // Исправление: int → double
    for (int i = 0; i < cogitatio; i++)
    {
        y += x_deg * coefs[i];
        x_deg *= x;
    }
    return y;
}

bool rectus(const std::string &filename)
{
    auto isInt = [](const std::string &s) -> bool
    {
        if (s.empty())
            return false;
        size_t i = (s[0] == '-') ? 1 : 0;
        if (i >= s.size())
            return false;
        for (; i < s.size(); i++)
        {
            if (!std::isdigit(s[i]))
                return false;
        }
        return true;
    };

    std::ifstream file(filename);
    if (!file.is_open())
        return false;

    std::string line;
    int lineNum = 0;

    while (std::getline(file, line))
    {
        if (line.empty())
            continue;
        lineNum++;

        std::istringstream iss(line);

        if (lineNum == 1)
        {
            // Первая строка: одно число (количество точек)
            std::string num;
            if (!(iss >> num) || !isInt(num))
                return false;

            // Проверяем, что нет лишних символов
            std::string extra;
            if (iss >> extra)
                return false;

            // Проверяем, что число положительное
            int count = std::stoi(num);
            if (count <= 0)
                return false;
        }
        else
        {
            // Остальные строки: два числа (x и y)
            std::string num1, num2;
            if (!(iss >> num1 >> num2))
                return false;

            if (!isInt(num1) || !isInt(num2))
                return false;

            // Проверяем, что нет лишних символов
            std::string extra;
            if (iss >> extra)
                return false;
        }
    }

    // Должна быть хотя бы одна строка с точками (всего минимум 2 строки)
    return lineNum >= 2;
}
int main()
{
    numerus['A'] = 0;
    numerus['B'] = 1;
    numerus['C'] = 2;
    numerus['D'] = 3;
    mut_param[3] = 'A';
    mut_param[2] = 'B';
    mut_param[1] = 'C';
    mut_param[0] = 'D';
    f_pm_1['A'] = fp;
    f_pm_1['B'] = fp;
    f_pm_1['C'] = fm;
    f_pm_1['D'] = fm;

    std::string tochki_filename = "tochki_2.txt";
    if (rectus(tochki_filename))
    {
        std::ifstream file(tochki_filename);

        int n;
        file >> n;
        std::vector<long long> first(n), second(n);
        for (int i = 0; i < n; i++)
            file >> first[i] >> second[i];

        std::vector<long long> residuals = second;
        std::vector<long long> multiplicator(cogitatio);
        for (int k = cogitatio - 1; k >= 0; k--)
        {
            inter_vitam_et_mortem stage(champ, supervivere, mutatio, n, first, residuals);
            stage.creo((k + 1) * 10);
            stage.conflictatio();
            for (int g = 0; g < 5000 * (k + 2); g++)
                stage.Aula_Caelestis();
            Genom best = stage.Victoria();
            multiplicator[k] = best.Corona_Imperialis();
            for (int i = 0; i < n; i++)
                residuals[i] -= multiplicator[k] * pow(first[i], k);
        }
        for (int k = cogitatio - 1; k >= 0; k--)
            std::cout << multiplicator[k] << " ";

        std::ofstream outFile("numbers.txt"); // открываем файл на запись
        if (!outFile)
        {
            std::cerr << "didn't manage\n";
            return 1;
        }
        for (int value : multiplicator)
            outFile << value << '\n';

        outFile.close();

        // отрисовка графика

        std::vector<double> points_x(n, 0);
        std::vector<double> points_y(n, 0);
        for (int i = 0; i < n; i++)
        {
            points_x[i] = (double) first[i];
            points_y[i] = (double) second[i];
        }

        using namespace matplot;
        long long min_x = *std::min_element(points_x.begin(), points_x.end());
        long long max_x = *std::max_element(points_x.begin(), points_x.end());

        std::vector<double> x = linspace(min_x - 1, max_x + 1, 100);
        std::vector<double> y(x.size(), 0);
        for (int i = 0; i < x.size(); i++)
        {
            y[i] = curve(x[i], multiplicator);
        }
        
        auto p = plot(x, y);
        p->line_width(4);
        p->color("black");
        hold(on);


        auto s = scatter(points_x, points_y);
        s->marker_color("red");
        s->marker_face_color("red");
        s->marker_size(2);
    


        title("Approximation");
        xlabel("x");
        ylabel("y");
        legend({"Approximation line", "Start points"});
        show();
    }
    else
    {
        std::cout << "uncorrect file";
    }

    return 0;
}