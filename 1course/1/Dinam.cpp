//#include <iostream>
//using namespace std;
//void vstav(int *&a, int &n, int l) {//сдвиг;
//	for (int i = n;i >= 0; i--) {
//		a[i] = a[i - 1];
//	}
//	a[0] = l;
//	n++;
//	realloc(a, sizeof(int) * (n + 1));
//}
//void ruv(int *x,int n) {//ручное заполнение
//	setlocale(0, "");
//	cout << "Введите" << n << "чисел" << endl;
//	for (int i = 0; i < n; i++)
//	{
//		if (!(cin >> x[i])) {
//			cin.clear();//чистка
//			while (cin.get() != '\n') {
//				cout << "Введено неверно, потворите попытку" << endl;
//				if (i > 0) {
//					i = i - 1;
//				}
//			}
//		}
//	}
//}
//void mas_cout(int *x, int n) {//вывод массива
//	for (int i = 0; i<n; i++){	
//		cout << " " << x[i];
//	}
//}
//void rav(int * const a, const int l) {//случайное заполнение
//	for (int i = 0; i < l; i++)
//	{
//		srand(time(0));
//		for (i = 0; i < l; i++)
//		{
//			a[i] = 100 + rand() % 300;
//		}
//	}
//}
//
//bool arif(int *a, int n) {//проверка на прогрессию
//	int k = 0;
//	for (int i = 1; i <= n - 1; i++) {
//		if (2 * a[i] == a[i - 1] + a[i + 1]) {
//			k = k + 1;
//		}
//	}
//	if (k == n - 2) {
//		return true;
//	}
//	else {
//		return false;
//	}
//}
//bool equal(int n) {//проверка на одинаковые цифры
//	int k;
//	int g;
//	k = n;
//	do
//	{
//		g = k;
//		k /= 10;
//	} while (k);
//	if ((g == (n % 10)) and ((n / 10) != 0)) {
//		return true;
//	}
//	else {
//		return false;
//	}
//}
//void del(int *x, int &n, int j) {//удаление элемента
//	for (int i = j; i < n; i++) {
//		x[i] = x[i + 1];
//	}
//	n--;
//	realloc(x, sizeof(int) * n);
//}
//int main() {
//	int n = 100;
//	int el,a,z,n1;
//	bool pr=false;
//	bool zd = true;
//	int* dx = (int*)malloc(n*sizeof(int));
//	setlocale(0, "");
//	cout << "Лабораторная работа №1 \"Одномерный массив\". Яснецов Фёдор" << endl;
//	cout << "Задачи на динамическом массиве" << endl;
//	while (true) {
//		cout << "Веберите способ заполнения массива:" << endl << "1 - в ручную" <<endl<< "2 - генератор случайных чисел" << endl;
//		cout << "Введите номер варианта ответа (1/2) " << endl;
//		cout << "Чтобы выйти введите 3" << endl;
//		if ((cin >> a) && (a == 1 || a == 2)) {
//			cout << "Введите количество обрабатываемых элементов массива" << endl;
//			if ((cin >> n)&&(n > 0)){
//				pr = true;
//				if (a==1){
//					cout << "Для динамического" << endl;
//					ruv(dx, n);
//				}
//				else {
//					rav(dx, n);
//				}
//				cout << "Созданный масссив : " << endl;
//				mas_cout(dx, n);
//				while (true) {
//					cout << endl << "Введите номер задания " << endl << "1.Вставить новое значение в массив перед первым элементом массива." << endl <<
//						"2.Определить, образуют ли числа массива арифметическую прогрессию." << endl <<
//						"3.Удалить элементы массива, в значениях которых первая и последняя цифры одинаковы." << endl;
//					cout << "Чтобы выйти введите 4" << endl;
//					cin >> z;
//					if ((z == 1) || (z == 2) || (z == 3)) {
//						if (z == 1) {
//							cout << "Введите новое значение,которое нужно вставитьв массив перед первым элементом массива" << endl;
//							while (true) {
//								if (cin >> el) {
//									vstav(dx, n, el);
//									cout << "Динамический массив после вставки " << endl;
//									mas_cout(dx, n);
//									break;
//								}
//								else {
//									cin.clear();
//									while (cin.get() != '\n') {
//										cout << "Элемент должен быть целым числом,повторите попытку" << endl;
//									}
//								}
//							}
//						}
//						if (z==2){
//							if (arif(dx, n)) {
//								cout << "Числа  динамического массива образуют арифметическую прогрессию" << endl;
//							}
//							else {
//								cout << "Числа  динамического массива не образуют арифметическую прогрессию" << endl;
//							}
//						}
//						if (z==3){
//							n1 = 0;
//							for (int i = 0; i <= n; i++) {
//								for (int j = 0; j <= n; j++) {
//									if (equal(dx[j])) {
//										del(dx, n, j);
//										n1 = 1;
//									}
//								}
//							}
//							if (n1 == 1) {
//								cout << endl << "Динамический после удаления" << endl;
//								mas_cout(dx, n);
//							}
//
//							else {
//								cout << endl << "В динамическом массиве нет таких элемнтов" << endl;
//							}
//						}
//					}
//					else if (z == 4) {
//						break;
//					}
//					else {
//						cin.clear();
//						while (cin.get() != '\n') {
//							cout << "Нет задания с таким номером, повторите ввод" << endl;
//						}
//					}
//				}
//			}
//			else {
//				pr = false;
//				cin.clear();
//				while (cin.get() != '\n') {
//					cout << "n должно быть больше нуля,повторите попытку"<<endl;
//				}
//			}
//
//		}
//		else if (a == 3) {
//			break;
//		}
//		else {
//			cin.clear();
//			while (cin.get() != '\n') {
//				cout << "Введено некорректно, повторите попытку" << endl;
//			}
//		}
//	}
//	free(dx);
//	return 0;
//}