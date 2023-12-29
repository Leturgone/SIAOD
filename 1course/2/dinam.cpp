#include <iostream>
using namespace std;
//Дана матрица размером n*m и вектор. Умножить матрицу на вектор.
void dmcout(int **a, int x, int y) {//вывод массива
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
}
void  dclav(int **a, int x, int y) {//заполнение с клавиатуры
	for (int i = 0; i < x; i++) {
		cout << "Введите элементы " << i << " строки " << endl;
		for (int j = 0; j < y; j++) {
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
void dmrand(int **a, int x, int y) {//случайное заполнение
	srand(time(0));
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			a[i][j] = 100 + rand() % 300;
		}
	}
}

void dvcout(int *a, int x) {//вывод массива
	for (int i = 0; i < x; i++) {
		cout << a[i] << endl;
	}
}
void  dvclav(int *a, int x) {//заполнение с клавиатуры
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
void dvrand(int *a, int x) {//случайное заполнение
	srand(time(0));
	for (int i = 0; i < x; i++)
	{
		a[i] = 100 + rand() % 300;
	}
}
void dveconmat(int** a, int *v, int x, int y) {
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			a[i][j] = a[i][j] * v[j];
		}
	}
	cout << "Матрица после умножения: " << endl;
	dmcout(a, x, y);

}
int main() {
	int r, c, a;
	int** dm=nullptr;//nullptr — ключевое слово, введенное в C++11 для описания константы нулевого указателя.
	int* dv=nullptr;
	setlocale(0, "");
	cout << "Лабораторная работа №2 \"Двумерный массив\". Яснецов Фёдор" << endl;
	cout << "Задача на динамическом массиве" << endl;
	while (true) {
		cout << "Чтобы выйти введите любой другой символ" << endl;
		cout << "Введите количество строк : ";
		if (cin >> r) {
			cout << "Введите количество столбцов: ";
			if (cin >> c) {
				dm = new int* [r];//указывает на область памяти, содержащей rows элементов, 
				//каждый из которых имеет тип int * и указывает на некоторую область памяти, пока еще не выделенную.
				for (int i = 0; i < r; ++i)
				{
					dm[i] = new int[c];//делаем все dm[i] указателями на область памяти из cols элементов типа int: 
				}
				dv = new int[r];//вектор для умножения
				while (true) {
					cout << "_______Меню матрицы_______" << endl;
					cout << "Выберите способ заполнения: " << endl;
					cout << "Если хотите выйти введите 3" << endl;
					cout << "1.В ручную" << endl << "2.Случайно" << endl;
					cin >> a;
					if (a == 1 || a == 2) {
						if (a == 1) {
							dclav(dm, r, c);
						}
						else {
							dmrand(dm, r, c);
						}
						cout << "Заполненная матрица: " << endl;
						dmcout(dm, r, c);
						while (true) {
							cout << "_______Меню вектора_______" << endl;
							cout << "Заполните вектор размера " << c << ": " << endl;
							cout << "Выберите способ заполнения: " << endl;
							cout << "Если хотите выйти введите 3" << endl;
							cout << "1.В ручную" << endl << "2.Случайно" << endl;
							cin >> a;
							if (a == 1 || a == 2) {
								if (a == 1) {
									dvclav(dv, c);
								}
								else {
									dvrand(dv, c);
								}
								cout << "Заполненный вектор: " << endl;
								dvcout(dv, c);
								dveconmat(dm, dv, r, c);;
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
			for (int i = 0; i < r; i++) {//Удаление строк
				delete[] dm[i];
			}
			delete[] dm;
			delete[] dv;
			break;

		}
	}
	return 0;
}