#include <iostream>
#include <map>
#include <functional>
#include <vector>
#include <algorithm>
#include <numeric>
#include <fstream>
#include <utility>


// Псевдослучайный генератор
static unsigned long int z=7;
int rand(){
    z=z*1103515245 + 12345 + 1426;
    return (unsigned int)((z/65536)%32768)%100 + 1;}

// Арифметические операции
int fp(int a, int b){ return a + b;}
int fm(int a, int b){ return a - b;}


// Словари
std::map<char, int> numerus;                            //словрь букву в число
std::map<int, char> mut_param;                          //словарь для функции мутации(число с 1до4 -> буква)
std::map<char, std::function<int(int,int)>> f_pm_1;     //словарь функции многочлена
std::map<char, std::function<int(int,int)>> f_pm_2;     //словарь функции многочлена

//определяет количество потомков в зависисмоти от успешности
std::vector<int> liberi(int a, int b){                  //a-количество мест, b-количество выживших
    std::vector<int> domi(b,0);                         //domi-список с количеством потомков(сами себя не считаем)
    a-=b;
    for(int i=1; i<b; i++){
        domi[i-1]+=(a/2);
        a-=(a/2);}
    domi[b-1]+=a;
    return domi;}

//функция определения баллов по разнице получившихся значений
int srv(int a, int b){
    int c = b-a;
    if(c<0)c=-c;
    return (c>10000) ? 0 : 10000 - c;}
//возведение в степень
int stepen(int a, int n){
    int c=1;
    for(int i=0; i<n; i++)c*=a;
    return c;}

//класс генома
class Genom{
private:
    struct uzel{ //узел, тк реализован через односвязный список
        char data;
        uzel* next;
        uzel(char ch):data(ch),next(nullptr){}};
    uzel* head;
    int count;
public:
    Genom():head(nullptr),count(0){} //конструктор

    //три дипсичные функции для трушного копирвания(мне лень разбраться)
    Genom(const Genom& other) : head(nullptr), count(0) {
        uzel* current = other.head;
        while(current){
            add_End(current->data);
            current = current->next;
        }
    }
    Genom& operator=(Genom other) {
        swap(other);
        return *this;
    }
    void swap(Genom& other) noexcept {
        std::swap(head, other.head);
        std::swap(count, other.count);
    }

    ~Genom(){ //диструктор
        while(head != nullptr){
            uzel* temp = head;
            head = head->next;
            delete temp;}}

    void add_Start(char ch){
        uzel* n_uzel = new uzel(ch);
        n_uzel->next = head;
        head = n_uzel;
        count++;}
    void add_End(char ch){
        uzel* n_uzel = new uzel(ch);
        if(head == nullptr)head = n_uzel;
        else{
            uzel* tut = head;
            while(tut->next != nullptr)
                tut = tut->next;
            tut->next = n_uzel;}
        count++;}

    //вывод букв генома / передача значений размера
    void print(){
        uzel* tut = head;
        while(tut != nullptr){
            std::cout<<tut->data<<" ";
            tut = tut->next;}
        std::cout << std::endl;}
    int size(){return count;}

    //функция мутации, с заданным параметром изменяет значение 1 из букв(не обязательно на новую)
    Genom mutate(int mut_pr){
        Genom copy;
        uzel* tut = head;
        while(tut != nullptr){
            if(rand() <= mut_pr)copy.add_End(mut_param[rand() % 4]);
            else copy.add_End(tut->data);
            tut = tut->next;}
        return copy;}
    //кор механика
    int reed(int a){
        uzel* tut = head;
        int ch=0;                   //число к которому будут прибовляться части       
        int n=0;                    //степень члена
        int in,out;                 //слогаемое внутри и множитель снаружи
        while(tut != nullptr){
            auto f_out = f_pm_1.find(tut->data);
            auto f_in = f_pm_2.find(tut->data);
            tut = tut->next;

            in=numerus[tut->data]*16; tut = tut->next;
            in+=numerus[tut->data]*4; tut = tut->next;
            in+=numerus[tut->data]  ; tut = tut->next;

            out=numerus[tut->data]*1024; tut = tut->next;
            out+=numerus[tut->data]*256; tut = tut->next;
            out+=numerus[tut->data]*64 ; tut = tut->next;
            out+=numerus[tut->data]*16 ; tut = tut->next;
            out+=numerus[tut->data]*4  ; tut = tut->next;
            out+=numerus[tut->data]    ; tut = tut->next;

            ch=f_out->second(ch, stepen(f_in->second(a,in),n)*out);
            n++;}
        return ch;}
};

// -----------------------------------
// Основной класс эволюции
class inter_vitam_et_mortem {
private:
    std::vector<Genom> spatium;
    std::vector<long int> food;
    int liquatorium;
    int magnitudo;
    int muton;
    std::vector<int> numeri_heredes;
    int N;
    std::vector<int> X;
    std::vector<int> Y;

public:
    inter_vitam_et_mortem(int count, int a, int b, int n,
                          std::vector<int> x, std::vector<int> y)
        : spatium(count), food(count, 0),
          liquatorium(count * a / 100),
          magnitudo(count),
          muton(b),
          numeri_heredes(liberi(count, count * a / 100)),
          N(n), X(x), Y(y) {}

    void create(int d) {
        for (int i = 0; i < magnitudo; i++) {
            for (int j = 0; j < d; j++)
                spatium[i].add_End(mut_param[rand() % 4]);
        }
    }

    void hereditatem(int mors, int vita) {
        spatium[mors] = spatium[vita].mutate(muton);
    }

    void setFoodValue(size_t index, int value) {
        food[index] += value;
    }

    int getFoodValue(int index) {
        return food[index];
    }

    void foot() {
        for (int i = 0; i < magnitudo; i++)
            std::cout << food[i] << " ";
        std::cout << std::endl;
    }

    std::vector<int> semita_vitae(int c) {
        std::vector<int> exitus(magnitudo);
        for (int i = 0; i < magnitudo; i++)
            exitus[i] = spatium[i].reed(c);
        return exitus;
    }

    void conflictatio() {
        for (int i = 0; i < magnitudo; i++) {
            for (int j = 0; j < N; j++) {
                food[i] += srv(spatium[i].reed(X[j]), Y[j]);
            }
        }
    }

    void print_best_lines(int k) {
        if (k > magnitudo) k = magnitudo;
    
        // Сортируем индексы по убыванию food
        std::vector<int> indices(magnitudo);
        std::iota(indices.begin(), indices.end(), 0);
        std::partial_sort(indices.begin(), indices.begin() + k, indices.end(),
            [this](int i, int j) { return food[i] > food[j]; });
    
        std::cout << "\n=== Топ-" << k << " успешных линий ===\n";
        for (int i = 0; i < k; ++i) {
            int idx = indices[i];
            std::cout << "Место " << i+1 << ", очки: " << food[idx] << " -> геном: ";
            spatium[idx].print();   // выводит последовательность символов
        }
        std::cout << "================================\n";
    }

    void Aula_Caelestis() {
        foot();

        std::vector<int> indices(magnitudo);
        std::iota(indices.begin(), indices.end(), 0);
        std::partial_sort(indices.begin(), indices.begin() + liquatorium, indices.end(),
            [this](int i, int j) { return food[i] > food[j]; });
        std::vector<int> favorites(indices.begin(), indices.begin() + liquatorium);
        std::vector<int> mortuos(indices.begin() + liquatorium, indices.end());

        // Обнуляем оценки, чтобы пересчитать для потомков
        for (int i : mortuos) food[i] = 0;

        int temp = 0;
        int index = 0;
        for (int i : mortuos){
            if (temp == numeri_heredes[index]) {
                temp = 0;
                index++;
            }
            spatium[i] = spatium[favorites[index]].mutate(muton);
            // if(temp%7==0)spatium[i] = spatium[favorites[index]].mutate(5);
            // else spatium[i] = spatium[favorites[index]].mutate(muton);
            // Пересчитываем food для нового потомка
            for (int j = 0; j < N; j++){
                food[i] += srv(spatium[i].reed(X[j]), Y[j]);
            }
            temp++;
        }
    }
};


int main(){
    numerus['A'] = 0; numerus['B'] = 1; numerus['C'] = 2; numerus['D'] = 3;
    mut_param[3] = 'A'; mut_param[2] = 'B'; mut_param[1] = 'C'; mut_param[0] = 'D';
    f_pm_1['A'] = fp; f_pm_1['B'] = fp; f_pm_1['C'] = fm; f_pm_1['D'] = fm;
    f_pm_2['A'] = fp; f_pm_2['B'] = fm; f_pm_2['C'] = fp; f_pm_2['D'] = fm;
    // Чтение данных из файла
    std::ifstream file("1234.txt");
    int n;
    file >> n;
    std::vector<int> first(n), second(n);
    for (int i = 0; i < n; i++)
        file >> first[i] >> second[i];
    // Создание и запуск эволюции
    inter_vitam_et_mortem pole(50, 10, 42, n, first, second);
    pole.create(40);
    pole.conflictatio();
    for (int k = 0; k < 200000; k++)
        pole.Aula_Caelestis();
    pole.print_best_lines(5);

    return 0;
}





//cd.. 2раза
//ls
//cd info
//g++ main.cpp
//./a.exe
