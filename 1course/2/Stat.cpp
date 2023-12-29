#include <iostream>
using namespace std;
//Дана матрица размером n*m и вектор. Умножить матрицу на вектор.
const int Rows = 100;
const int	Cols = 100;
void mcout(int a[Rows][Cols], int x, int y) {//вывод массива
	for (int i = 0; i < x; i++) {
		for (int j = 0; j <y; j++) {
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
}
void  clav(int a[Rows][Cols], int x, int y) {//заполнение с клавиатуры
	for (int i = 0; i <x; i++) {
		cout << "Введите элементы " << i << " строки " << endl;
		for (int j = 0; j <y; j++) {
			if (!(cin >> a[i][j])) {
				cin.clear();//чистка
				while (cin.get() != '\n') {
					cout << "Введено неверно, повторите попытку" << endl;
					j = j - 1;
				}
			}
		}
	}
}
void mrand(int a[Rows][Cols], int x, int y) {//случайное заполнение
	srand(time(0));
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			a[i][j] = 100 + rand() % 300;
		}
	}
}

void vcout(int a[Cols], int x) {//вывод массива
	for (int i = 0; i < x; i++) {
		cout << a[i] << endl;
	}
}
void  vclav(int a[Cols], int x) {//заполнение с клавиатуры
	cout << "Введите элементы вектор" << endl;
	for (int j = 0; j < x; j++) {
		if (!(cin >> a[j])) {
			cin.clear();//чистка
			while (cin.get() != '\n') {
				cout << "Введено неверно, повторите попытку" << endl;
				j = j - 1;
			}
		}
	}
}
void vrand(int a[Cols], int x) {//случайное заполнение
	srand(time(0));
	for (int i = 0; i < x; i++)
	{
		a[i] = 100 + rand() % 300;
	}
}
void veconmat(int a[Rows][Cols], int v[Cols],int x,int y) {
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			a[i][j]= a[i][j] *v[j];
		}
	}
	cout << "Матрица после умножения: " << endl;
	mcout(a, x, y);
}
int main() {
	int m[Rows][Cols];
	int v[Cols];
	int r, c, a;
	setlocale(0, "");
	cout << "Лабораторная работа №2 \"Двумерный массив\". Яснецов Фёдор" << endl;
	cout << "Задача статическом массиве" << endl;
	while (true) {
		cout << "Чтобы выйти введите любой другой символ" << endl;
		cout << "Введите количество строк : ";
		if (cin >> r) {
			cout << "Введите количество столбцов: ";
			if (cin >> c) {
				while (true) {
					cout << "_______Меню матрицы_______" << endl;
					cout << "Выберите способ заполнения: " << endl;
					cout << "Если хотите выйти введите 3" << endl;
					cout << "1.В ручную" << endl << "2.Случайно" << endl;
					cin >> a;
					if (a == 1 || a == 2) {
						if (a == 1) {
							clav(m, r, c);
						}
						else {
							mrand(m, r, c);
						}
						cout << "Заполненная матрица: " << endl;
						mcout(m, r, c);
						while (true) {
							cout << "_______Меню вектора_______" << endl;
							cout << "Заполните вектор размера " << c << ": " << endl;
							cout << "Выберите способ заполнения: " << endl;
							cout << "Если хотите выйти введите 3" << endl;
							cout << "1.В ручную" << endl << "2.Случайно" << endl;
							cin >> a;
							if (a == 1 || a == 2) {
								if (a == 1) {
									vclav(v, c);
								}
								else {
									vrand(v, c);
								}
								cout << "Заполненный вектор: " << endl;
								vcout(v, c);
								veconmat(m, v, r, c);;
							}
							else if (a == 3) {
								break;
							}
							else {
								cin.clear();
								while (cin.get() != '\n') {
									cout << "Введено неверно, повторите попытку" << endl;
								}
							}
						}
					}
					else if (a == 3) {
						break;
					}
					else {
						cin.clear();
						while (cin.get() != '\n') {
							cout << "Введено неверно, повторите попытку" << endl;
						}
					}
				}

			}
			else {
				cin.clear();
				while (cin.get() != '\n') {
					cout << "Введено неверно, повторите попытку" << endl;
				}
			}
		}
		else {
			break;
		}
	}
	return 0;
}