#include <iostream>
#include <vector>
using namespace std;
void vstav(vector<int>& a, int& n, int l) {
	a.emplace(a.begin(),l);//вставка элемента
	n = n + 1;
}

void ruv(vector<int> &x, int n) {//ручное заполнение
	setlocale(0, "");
	cout << "Введите" << n << "чисел" << endl;
	for (int i = 0; i < n; i++)
	{
		if (!(cin >> x[i])) {
			cin.clear();//чистка
			while (cin.get() != '\n') {
				cout << "Введено неверно, потворите попытку" << endl;
				if (i > 0) {
					i = i - 1;
				}
			}
		}
	}
}
void mas_cout(vector<int> x, int n) {//вывод массива
	for (int i = 0; i < n; i++) {
		cout << " " << x[i];
	}
}
void rav(vector<int> &a, const int l) {//случайное заполнение
	for (int i = 0; i < l; i++)
	{
		srand(time(0));
		for (i = 0; i < l; i++)
		{
			a[i] = 100 + rand() % 300;
		}
	}
}
void del(vector<int> &x, int &n, int j) {//удаление элемента
	x.erase(x.begin() + j);
	n = n - 1;
}
bool arif(vector<int> a, int n) {//проверка на прогрессию
	int k = 0;
	for (int i = 1; i <= n - 1; i++) {
		if (2 * a[i] == a[i - 1] + a[i + 1]) {
			k = k + 1;
		}
	}
	if (k == n - 2) {
		return true;
	}
	else {
		return false;
	}
}
bool equal(int n) {//проверка на одинаковые цифры
	int k;
	int g;
	k = n;
	do
	{
		g = k;
		k /= 10;
	} while (k);
	if ((g == (n % 10)) and ((n / 10) != 0)) {
		return true;
	}
	else {
		return false;
	}
}
int main() {
	int n = 100;
	int el, a, z, n1;
	vector<int>vx(n);
	setlocale(0, "");
	cout << "Лабораторная работа №1 \"Одномерный массив\". Яснецов Фёдор" << endl;
	cout << "Задачи на векторе" << endl;
	while (true) {
		cout << "Веберите способ заполнения вектора:" << endl << "1 - в ручную" << endl << "2 - генератор случайных чисел" << endl;
		cout << "Введите номер варианта ответа (1/2) " << endl;
		cout << "Чтобы выйти введите 3" << endl;
		if ((cin >> a) && (a == 1 || a == 2)) {
			cout << "Введите количество обрабатываемых элементов вектора" << endl;
			if ((cin >> n) && (n > 0)) {
				if (a == 1) {
					cout << "Для вектора" << endl;
					ruv(vx, n);
				}
				else {
					rav(vx, n);
				}
				cout << "Созданный вектор : " << endl;
				mas_cout(vx, n);
				while (true) {
					cout << endl << "Введите номер задания " << endl << "1.Вставить новое значение в массив перед первым элементом массива." << endl <<
						"2.Определить, образуют ли числа массива арифметическую прогрессию." << endl <<
						"3.Удалить элементы массива, в значениях которых первая и последняя цифры одинаковы." << endl;
					cout << "Чтобы выйти введите 4" << endl;
					cin >> z;
					if ((z == 1) || (z == 2) || (z == 3)) {
						if (z == 1) {
							cout << "Введите новое значение,которое нужно вставить в вектор перед первым элементом вектора" << endl;
							while (true) {
								if (cin >> el) {
									vstav(vx, n, el);
									cout << "Вектор после вставки " << endl;
									mas_cout(vx, n);
									break;
								}
								else {
									cin.clear();
									while (cin.get() != '\n') {
										cout << "Элемент должен быть целым числом,повторите попытку" << endl;
									}
								}
							}
						}
						if (z == 2) {
							if (arif(vx, n)) {
								cout << "Числа  вектора образуют арифметическую прогрессию" << endl;
							}
							else {
								cout << "Числа  вектора не образуют арифметическую прогрессию" << endl;
							}
						}
						if (z == 3) {
							n1 = 0;
							for (int i = 0; i <= n; i++) {
								for (int j = 0; j <= n; j++) {
									if (equal(vx[j])) {
										del(vx, n, j);
										n1 = 1;
									}
								}
							}
							if (n1 == 1) {
								cout << endl << "Вектор после удаления" << endl;
								mas_cout(vx, n);
							}

							else {
								cout << endl << "В векторе нет таких элемнтов" << endl;
							}
						}
					}
					else if (z == 4) {
						break;
					}
					else {
						cin.clear();
						while (cin.get() != '\n') {
							cout << "Нет задания с таким номером, повторите ввод" << endl;
						}
					}
				}
			}
			else {
				cin.clear();
				while (cin.get() != '\n') {
					cout << "n должно быть больше нуля,повторите попытку" << endl;
				}
			}

		}
		else if (a == 3) {
			break;
		}
		else {
			cin.clear();
			while (cin.get() != '\n') {
				cout << "Введено некорректно, повторите попытку" << endl;
			}
		}
	}
	return 0;
}