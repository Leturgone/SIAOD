//Фибоначчи поиск
//Регистрация земельного участка в СНТ: кадастровый номер – целое число, адрес СНТ, ФИО
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <random>
#pragma warning (disable : 4996)
using namespace std;

struct record {
    int YNum;//участковый номер
    char adress[20];//дрес снт
    char name[30];//ФИО
};
int random(int a, int b)
{
    srand(time(NULL));
    if (a > 0) return a + rand() % (b - a);
    else return a + rand() % (abs(a) + b);
}
void genarr(record* arr, int N)
{
    for (int i = 0; i < N; i++) {
        srand(time(0));
        arr[i].YNum = random(1, 40);
        string adr = "Bailalskia " + to_string(random(1, 40));
        strcpy(arr[i].adress, adr.c_str());
        string firstNames[] = { "Andrew", "Alexander", "Michael", "Nicholas", "Dmitry", "Ivan", "Sergey", "Artem", "Alexey", "Maxim" };
        string lastNames[] = { "Ivanov", "Petrov", "Sidorov", "Kuznetsov", "Smirnov", "Vasiliev", "Kovalev", "Morozov", "Novikov", "Romanov" };
        int firstNameIndex = rand() % 10;
        int lastNameIndex = rand() % 10;
        string firstName = firstNames[firstNameIndex];
        string lastName = lastNames[lastNameIndex];
        string ndr = firstNames[firstNameIndex]+" " + lastNames[lastNameIndex] + " " + "Ivanovich";
        strcpy(arr[i].name, ndr.c_str());
    }
}

record getlastrecord(FILE* fp, int N)//получение последней записи
{
    fseek(fp, (N - 1) * sizeof(record), SEEK_SET);
    record temp;
    fread(&temp, sizeof(record), 1, fp);//new fp
    string result;// = temp.YNum + temp.adress + temp.name;
    return temp;
}

struct searchrecord
{
    int key;
    int pos;//byte/i
};
int compare(const void* x1, const void* x2)
{
    return (*(int*)x1 - *(int*)x2);
}
void createsearchtable(searchrecord*& table, int N,FILE* fp)
{
    table = new searchrecord[N];
    record temp;
    int i = 0;
    while (i < N)
    {
        size_t r = fread(&temp, sizeof(record), 1, fp);
        table[i].key = temp.YNum;
        table[i].pos = i;
        i++;
    }
    qsort(table, N, sizeof(searchrecord), compare);
}


record* linearsearch(FILE* fp, int N, int YNum)
{
    record temp;
    int i = 0;
    while (i < N)
    {
        size_t r = fread(&temp, sizeof(record), 1, fp);
        if (temp.YNum == YNum)
            return &temp;
        if (r == 0)
            return NULL;
        i++;
    }
    return NULL;
}

record getrecord(FILE* fp, int pos)
{
    fseek(fp, (pos) * sizeof(record), SEEK_SET);
    record temp;
    fread(&temp, sizeof(record), 1, fp);
    return temp;
}
searchrecord fibonacci_search(searchrecord*& data, int N ,int key) {
    int n = N;
    int fib2 = 0; // значение n-2 числа Фибоначчиss
    int fib1 = 1; // значение n-1 числа Фибоначчи
    int fib = fib1 + fib2; // значение текущего числа Фибоначчи

    // Находим ближайшее число Фибоначчи, которое больше или равно n
    while (fib < n) {
        fib2 = fib1;
        fib1 = fib;
        fib = fib1 + fib2;
    }
    int offset = -1; // смещение для записи в файле
    // Пока не проверили все элементы структуры данных
    while (fib > 1) {
        int i = min(offset + fib2, n - 1);

        // Если ключ меньше, чем значение i-го элемента структуры данных, то ищем в левой части
        if (data[i].key > key) {
            fib = fib2;
            fib1 = fib1 - fib2;
            fib2 = fib - fib1;
        }
        // Если ключ больше, чем значение i-го элемента структуры данных, то ищем в правой части
        else if (data[i].key < key) {
            fib = fib1;
            fib1 = fib2;
            fib2 = fib - fib1;
            offset = i;
        }
        // Если ключ равен значению i+1-го элемента структуры данных, то нашли нужную запись в файле
        else {
            return data[i+1];
        }
    }
}
int main()
{
    int N;
    setlocale(0, "");
    cout << "Лабораторная работа №9 \"Поиск записей в файле.\". Яснецов Фёдор " << endl;
    while (true) {
        cout << "Введите количество записей" << endl;
        cout << "Чтобы выйти введите не число" << endl;
        if (cin >> N) {
            const char* fname = "unique_name.bin";
            record* recarr = new record[N];
            genarr(recarr, N);
            FILE* fp = fopen(fname, "wb");//открытие файла для записи
            if (fp != NULL) { //проверка, был ли файл успешно открыт
                fwrite(recarr, sizeof(record), N, fp);//запись в файл
                ifstream file("unique_name.bin", ios::in | ios::binary);//поиск ращзмера файла
                file.seekg(0, ios::end);
                int size = file.tellg();
                file.close();
                fclose(fp); //закрытие файла
                fp = fopen(fname, "rb"); //открытие файла для чтения
                record last = getlastrecord(fp, N);//получение последней записи

                cout << "Задание 1" << endl;
                cout << "Количество элементов " << N << endl << "Размер " << size << " байт" << endl << "Последняя запись: " << last.YNum << " " << last.adress << " " << last.name;
                cout << endl;
                fclose(fp);

                cout << "Задание 2" << endl;
                int key;
                fp = fopen(fname, "rb");
                cout << "Введите ключ " << endl;
                cin >> key;
                cout << "Линейный поиск" << endl;
                auto start = std::chrono::steady_clock::now();
                record r=*(linearsearch(fp, N, key));
                cout << r.YNum << " " << r.adress << " " << r.name << endl;
                auto end = std::chrono::steady_clock::now();
                std::chrono::duration<double /*std::milli*/> elapsed_seconds3 = end - start;
                cout << "Время " << elapsed_seconds3.count()<<" c";
                cout << endl;
                fclose(fp); //закрытие файла после использования

                cout << "Задание 3" << endl;
                searchrecord* table = NULL;
                cout << "Создание таблицы" << endl;
                start = std::chrono::steady_clock::now();
                fp = fopen(fname, "rb");
                createsearchtable(table, N, fp);
                end = std::chrono::steady_clock::now();
                elapsed_seconds3 = end - start;
                fclose(fp);
                cout << "Время " << elapsed_seconds3.count() << " c" << endl;
                cout << "Бинарный поиск" << endl;
                start = std::chrono::steady_clock::now();
                start = std::chrono::steady_clock::now();
                fp = fopen(fname, "rb");
                searchrecord sr = fibonacci_search(table, key, N);
                end = std::chrono::steady_clock::now();
                elapsed_seconds3 = end - start;
                cout << "Время " << elapsed_seconds3.count() << " c"<<endl;

                record n = getrecord(fp, sr.pos);
                cout << n.YNum<<" "<< n.adress <<" "<< n.name << endl;
                fclose(fp);
            }
            else {
                cout << "Ошибка открытия файла" << endl;
            }
        }
        else {
            break;
        }
    }
}

