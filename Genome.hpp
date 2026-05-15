#pragma once
class Genom
{
private:
    struct uzel
    {
        char data;
        uzel *next;
        uzel(char ch);
    }; // узел, тк реализован через односвязный список
    uzel *head;
    int count;

public:
    Genom(); // конструктор

    // три дипсичные функции для трушного копирвания(мне лень разбраться)
    Genom(const Genom &other);

    Genom &operator=(Genom other);

    void swap(Genom &other) noexcept;
    void statura(char ch);
    void print();
    int size();
    Genom mutate(int mut_pr);
    long long reed(long long a);
    long long Corona_Imperialis();

    // деструктор
    ~Genom();
};