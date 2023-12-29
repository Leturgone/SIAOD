//Вариант 8 
//Алгоритм простой сортировки	Алгоритм усовершенствованной сортировки     	Алгоритм слияния
//Простого выбора	            Турнирная сортировка	                            Простое слияние
//количества операций сравнения С и количества операций перемещения М. 
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
using namespace std;

//формирование кучи
void formKucha(int* numbers, int root, int bottom, long long int& C, long long int& M)
{
    int maxChild; // индекс максимального потомка
    int done = 0; // флаг того, что куча сформирована
    // Пока не дошли до последнего ряда
    while ((root * 2 <= bottom) && (!done))
    {
        if (root * 2 == bottom) {   // если мы в последнем ряду,
            C++;
            maxChild = root * 2;
        }// запоминаем левый потомок
        // иначе запоминаем больший потомок из двух
        else if (numbers[root * 2] > numbers[root * 2 + 1]) {
            C++;
            maxChild = root * 2;
        }
        else {
            maxChild = root * 2 + 1;
        }
        // если элемент вершины меньше максимального потомка
        if (numbers[root] < numbers[maxChild])
        {
            C++;
            M++;
            int temp = numbers[root]; // меняем их местами
            numbers[root] = numbers[maxChild];
            numbers[maxChild] = temp;
            root = maxChild;
        }
        else // иначе
            done = 1; // турнирная сетка сформирована
    }
}
// Функция сортировки на куче
void TurSort(int* arr, long long int n, long long int& C, long long int& M)
{
    // Формируем нижний ряд пирамиды
    for (int i = (n / 2); i >= 0; i--)
        formKucha(arr, i, n - 1, C,M);
    // Просеиваем через пирамиду остальные элементы
    for (int i = n - 1; i >= 1; i--)
    {
        M++;
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        formKucha(arr, 0, i - 1, C,M);
    }
}

void simple_selection_sort(int* arr, long long int n, long long int& C, long long int& M) {
    int min, temp; // для поиска минимального элемента и для обмена
    for (int i = 0; i < n - 1; i++)
    {
        min = i; // запоминаем индекс текущего элемента
        // ищем минимальный элемент чтобы поместить на место i-ого
        for (int j = i + 1; j < n; j++)  // для остальных элементов после i-ого
        {
            C++;
            if (arr[j] < arr[min]) // если элемент меньше минимального,
                min = j;       // запоминаем его индекс в min
        }
        M++;
        temp = arr[i];      // меняем местами i-ый и минимальный элементы
        arr[i] = arr[min];
        arr[min] = temp;
    }
}
void merge_sort(int* arr, long long int n, long long int& C, long long int& M) {
    int mid = n / 2; // находим середину сортируемой последовательности
    if (n % 2 == 1)
        mid++;
    int h = 1; // шаг
    // выделяем память под формируемую последовательность
    int* c = (int*)malloc(n * sizeof(int));
    int step;
    while (h < n)
    {
        step = h;
        int i = 0;   // индекс первого пути
        int j = mid; // индекс второго пути
        int k = 0;   // индекс элемента в результирующей последовательности
        while (step <= mid)
        {
            while ((i < step) && (j < n) && (j < (mid + step)))
            { // пока не дошли до конца пути
              // заполняем следующий элемент формируемой последовательности
              // меньшим из двух просматриваемых
                C++;
                if (arr[i] < arr[j])
                {
                    M++;
                    c[k] = arr[i];
                    i++; k++;
                }
                else {
                    M++;
                    c[k] = arr[j];
                    j++; k++;
                }
            }
            while (i < step)
            { // переписываем оставшиеся элементы первого пути (если второй кончился раньше)
                M++;
                c[k] = arr[i];
                i++; k++;
            }
            while ((j < (mid + step)) && (j < n))
            {  // переписываем оставшиеся элементы второго пути (если первый кончился раньше)
                M++;
                c[k] = arr[j];
                j++; k++;
            }
            step = step + h; // переходим к следующему этапу
        }
        h = h * 2;
        // Переносим упорядоченную последовательность (промежуточный вариант) в исходный массив
        for (i = 0; i < n; i++)
            M++;
            arr[i] = c[i];
    }
}
void reversesort(int *arr, long long int n) {
    for (int i = 0; i < n/2; i++) {
        int temp = arr[i];

        arr[i] = arr[n - 1 - i];

        arr[n- 1 - i] = temp;
    }
}
void fillMas(int* arr, long long int N) {
    for (long long int i = 0; i < N; i++)
        arr[i] = rand() % 100000000;
}
void copyMas(int* arr, long long int N, int* mas2) {
    for (int i = 0; i < N; i++) {
        mas2[i] = arr[i];
    }
}
void printMas(int* arr, long long int N) {
    for (int i = 0; i < N; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main(){
    int a,b,c;
    setlocale(0, "");
    cout << "Лабораторная работа №8 \"Эффективные алгоритмы сортировки.\". Яснецов Фёдор " << endl;
    while (true) {
        cout << "Чтобы выйти введите не число" << endl;
        cout << "Ведите диапазон и величину увеличения: " << endl;
        if (cin >> a >> b>>c) {
            for (long long int N = a; N <= b; N += c) {
                cout << "______________________________________________" << endl;
                cout <<"Количество элементов " << N << endl;
                int* mas1 = new int[N], * mas2 = new int[N], * mas3 = new int[N];
                fillMas(mas1, N);
                copyMas(mas1, N, mas2);
                copyMas(mas1, N, mas3);
                //printMas(mas1, N);
                long long int C1 = 0, M1 = 0, C2 = 0, M2 = 0, C3 = 0, M3 = 0;

                //avg
                auto start = std::chrono::steady_clock::now();
                simple_selection_sort(mas1, N, C1, M1);
                auto end = std::chrono::steady_clock::now();
                std::chrono::duration<double> elapsed_seconds1 = end - start;//продолжительность

                start = std::chrono::steady_clock::now();
                TurSort(mas2, N, C2, M2);
                end = std::chrono::steady_clock::now();
                std::chrono::duration<double> elapsed_seconds2 = end - start;

                start = std::chrono::steady_clock::now();
                merge_sort(mas3, N, C3, M3);
                end = chrono::steady_clock::now();
                chrono::duration<double> elapsed_seconds3 = end - start;
                //printMas(mas3, N);
                cout << "Заполненный случайно массив: Простого выбора  C= " << C1 << "\t M= " << M1 << "\tt=" << elapsed_seconds1.count() << endl;
                cout << "Заполненный случайно массив: Тур. сортировка  C= " << C2 << "\t M=" << M2 << "\tt=" << elapsed_seconds2.count() << endl;
                cout << "Заполненный случайно массив: Простое слияние  C= " << C3 << "\t M= " << M3 << "\tt=" << elapsed_seconds3.count() << endl;

                //Л
                C1 = 0;
                C2 = 0; 
                C3 = 0; 
                M1 = 0; 
                M2 = 0; 
                M3 = 0;
                start = std::chrono::steady_clock::now();
                simple_selection_sort(mas1, N, C1, M1);
                end = std::chrono::steady_clock::now();
                elapsed_seconds1 = end - start;

                start = std::chrono::steady_clock::now();
                TurSort(mas2, N, C2, M2);
                end = std::chrono::steady_clock::now();
                elapsed_seconds2 = end - start;

                start = std::chrono::steady_clock::now();
                merge_sort(mas3, N, C3, M3);
                end = std::chrono::steady_clock::now();
                elapsed_seconds3 = end - start;
                cout << "......................................" << endl;
                cout << "Отсортированный массив: Простого выбора  C= " << C1 << "\t M= " << M1 << "\tt=" << elapsed_seconds1.count() << endl;
                cout << "Отсортированный массив: Тур. сортировка  C= " << C2 << "\t M= " << M2 << "\tt=" << elapsed_seconds2.count() << endl;
                cout << "Отсортированный массив: Простое слияние  C= " << C3 <<"\t M = " << M3 << "\tt = " << elapsed_seconds3.count() << endl;


                //Худший случай, когда массив реверсивен
                C1 = 0;
                C2 = 0;
                C3 = 0;
                M1 = 0;
                M2 = 0;
                M3 = 0;
                reversesort(mas1, N);
                reversesort(mas2, N);
                reversesort(mas3, N);

                start = std::chrono::steady_clock::now();
                simple_selection_sort(mas1, N, C1, M1);
                end = std::chrono::steady_clock::now();
                elapsed_seconds1 = end - start;

                start = std::chrono::steady_clock::now();
                TurSort(mas2, N, C2, M2);
                end = std::chrono::steady_clock::now();
                elapsed_seconds2 = end - start;

                start = std::chrono::steady_clock::now();
                merge_sort(mas3, N, C3, M3);
                end = std::chrono::steady_clock::now();
                elapsed_seconds3 = end - start;
                cout << "......................................" << endl;
                cout << "Отсортированный а обр. порядке массив: Простого выбора  C= " << C1 << "\t M= " << M1 << "\tt=" << elapsed_seconds1.count() << endl;
                cout << "Отсортированный а обр. порядке массив: Тур. сортировка  C= " << C2 << "\t M= " << M2 << "\tt=" << elapsed_seconds2.count() << endl;
                cout << "Отсортированный а обр. порядке массив: Простое слияние  C= " << C3 << "\t M= " << M3 << "\tt=" << elapsed_seconds3.count() << endl;
            }
        }
        else {
            break;
        }
    }
    return 0;
}