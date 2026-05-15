#include "Genome.hpp"
#include "dataconst.hpp"
#include <iostream>
#include <utility>
#include <cmath>

// Конструктор узла (нужно добавить, так как в классе только объявление)
Genom::uzel::uzel(char ch) : data(ch), next(nullptr) {}

// Конструктор
Genom::Genom() : head(nullptr), count(0) {}

// Конструктор копирования
Genom::Genom(const Genom &other) : head(nullptr), count(0)
{
    uzel *current = other.head;
    while (current)
    {
        statura(current->data);
        current = current->next;
    }
}

// Оператор присваивания
Genom &Genom::operator=(Genom other)
{
    swap(other);
    return *this;
}

// Swap
void Genom::swap(Genom &other) noexcept
{
    std::swap(head, other.head);
    std::swap(count, other.count);
}

// Деструктор
Genom::~Genom()
{
    while (head != nullptr)
    {
        uzel *temp = head;
        head = head->next;
        delete temp;
    }
}

// Добавление буквы в конец
void Genom::statura(char ch)
{
    uzel *n_uzel = new uzel(ch);
    if (head == nullptr)
    {
        head = n_uzel;
    }
    else
    {
        uzel *tut = head;
        while (tut->next != nullptr)
        {
            tut = tut->next;
        }
        tut->next = n_uzel;
    }
    count++;
}

// Вывод букв генома
void Genom::print()
{
    uzel *tut = head;
    while (tut != nullptr)
    {
        std::cout << tut->data << " ";
        tut = tut->next;
    }
    std::cout << std::endl;
}

// Размер
int Genom::size()
{
    return count;
}

// Функция мутации
Genom Genom::mutate(int mut_pr)
{
    Genom copy;
    uzel *tut = head;
    while (tut != nullptr)
    {
        if (randevu() <= mut_pr)
        {
            copy.statura(mut_param[randevu() % 4]);
        }
        else
        {
            copy.statura(tut->data);
        }
        tut = tut->next;
    }
    return copy;
}

// Кор механика
long long Genom::reed(long long a)
{
    uzel *tut = head;
    long long ch = 0;
    int n = 0;
    int sum, out_uno, out_dos, out_tres;
    while (tut != nullptr)
    {
        auto f_out = f_pm_1.find(tut->data);
        tut = tut->next;

        out_uno = numerus[tut->data] * 4;
        tut = tut->next;
        out_uno += numerus[tut->data] + 1;
        tut = tut->next;

        out_dos = numerus[tut->data] * 4;
        tut = tut->next;
        out_dos += numerus[tut->data] + 1;
        tut = tut->next;

        out_tres = numerus[tut->data] * 4;
        tut = tut->next;
        out_tres += numerus[tut->data] + 1;
        tut = tut->next;

        sum = numerus[tut->data] * 16;
        tut = tut->next;
        sum += numerus[tut->data] * 4;
        tut = tut->next;
        sum += numerus[tut->data];
        tut = tut->next;

        ch = f_out->second(ch, pow(a, n) * (out_uno * out_dos * out_tres + sum - 1));
        n++;
    }
    return ch;
}

// Вывод коэфф перед высшей степенью
long long Genom::Corona_Imperialis()
{
    int blocks = count / 10;
    uzel *tut = head;
    for (int i = 0; i < (blocks - 1) * 10; i++)
    {
        tut = tut->next;
    }
    char op = tut->data;
    tut = tut->next;
    int sum, out_uno, out_dos, out_tres;

    out_uno = numerus[tut->data] * 4;
    tut = tut->next;
    out_uno += numerus[tut->data] + 1;
    tut = tut->next;

    out_dos = numerus[tut->data] * 4;
    tut = tut->next;
    out_dos += numerus[tut->data] + 1;
    tut = tut->next;

    out_tres = numerus[tut->data] * 4;
    tut = tut->next;
    out_tres += numerus[tut->data] + 1;
    tut = tut->next;

    sum = numerus[tut->data] * 16;
    tut = tut->next;
    sum += numerus[tut->data] * 4;
    tut = tut->next;
    sum += numerus[tut->data];
    tut = tut->next;

    long long coeff = out_uno * out_dos * out_tres + sum - 1;
    bool is_plus = (op == 'A' || op == 'B');
    return is_plus ? coeff : -coeff;
}