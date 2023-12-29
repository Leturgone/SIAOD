#include <iostream>
using namespace std;
#include <vector>
#include <chrono>
#include <bitset>
void set_bit(unsigned int arr[], int num) {//Функция для установки бита
	//целочисленно делим и узнаем в каком элементе нужно поставить наш бит, бит узнаем с остатка
	arr[num>>5]= arr[num >> 5] | (1 << (num&(0x1f)));
}

const long int N = 10000000; // количество битов
unsigned int bit_arr[N / 32];//массив битов, то есть, у нас хранится в массиве 10**7/32= 312500 элементов,

int main() {
	setlocale(0, "");
	cout << "-----Задание 2----" << endl;
	/*
	* Реализовать задачу по сортировке данных файла, используя для представления
	данных файла (10 7 семизначных чисел) в памяти, массив битов.

	Примечание. Задача и алгоритм ее решения рассмотрены на практическом занятии.
	Файл не использовать, смоделируйте тест на последовательности, вводимой с клавиатуры.
	*/
	vector<int> number_arr;
	//const int N = 107;
	int n;
	cout << "Введите количество чисел: ";
	cin >> n;
	int k;
	int z=0;
	int temp;

	//в каждом из которых по 32 бита.

	cout << endl << "Введите числа: " << endl;

	//заполнение массива, который будем сортировать
	for (int i = 0; i < n; i++) {
		cin >> k;
		number_arr.push_back(k);
	}
	//Начинаем  процесс сортировки. Главное - каждому элементу массива числе должен соответстосвать бит под соответствующим номером.
	//Первое - заполняем массив битов
	auto start_time = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < n; i++) {//цикл по элементам массива
		set_bit(bit_arr, number_arr[i]);
	}

	//заполняем массив из битового
	for (int i = 0; i < N/32; i++) {
		for (int j = 0; j < 32; j++) {
			temp = 0;
			temp = temp+(1 << j);
			if ((bit_arr[i] & temp) == temp) {
				number_arr[z]=(i * 32 + j);
				z++;
			}
		}
	}
	auto end_time = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
	cout << "Время выполнения: " << duration.count() << " ms" << endl;
	cout << "Отсортированный массив: " << endl;
	for (int i = 0; i < number_arr.size(); i++) {
		cout << number_arr[i]<<"  ";
	}
	cout << endl;
	return 0;
}
