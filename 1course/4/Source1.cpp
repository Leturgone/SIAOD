#include <iostream>
#include <vector>
#include "Header1.h"
using namespace std;
void avto(Table&x) {
	for (int i = 0; i < x.l; i++) {
		STUDENT s1{ 201+i,"Ivanov I.I","IKBO-18-21",{4,2+i,3+i,4,5}};
		x.members.push_back(s1);
	}
}
void full_cin(Table& x) {
	for (int i = 0; i < x.l; i++) {
		cout << "Введите данные студента №" << i + 1 << endl;
		STUDENT s;
		cin_note(s);
		x.members.push_back(s);
	}
}

int main() {
	setlocale(0, "");
	int a, b, c;
	int N = 0;
	cout << "Лабораторная работа №4 \"Структуризация многоэлементных структур средствами struct.\". Яснецов Фёдор " << endl;
	while (true) {
		cout << "Введите количество студентов:" << endl;
		cout << "Чтобы выйти введите не цифру" << endl;
		if (cin >> a) {
			Table x;
			STUDENT s = {};
			x.l = a;
			while (true) {
				cout << "Выберите способ ввода: " << endl << "1-Автоматически" << endl << "2-Вручную" << endl;
				cout << "Чтобы выйти введите 3" << endl;
				cin >> b;
				if (b == 1 || b == 2) {
					if (b == 1) {
						avto(x);
					}
					if (b == 2) {
						full_cin(x);
					}
					cout_table(x);
					while (true) {
						cout << "Выберите функцию:" << endl;
						cout << "1)	Вставить новую запись в таблицу." << endl << "2)	Найти номер зачетной книжки студента(студентов) с максимальным средним баллом." << endl << "3)	Удалить из таблицы студентов заданной группы." << endl;
						cout << "Чтобы выйти введите 4" << endl;
						cin >> c;
						if (c == 1 || c == 2 || c == 3) {
							if (c == 1) {
								cin_new(x, s);
							}
							else if (c == 2) {
								cout << "Максимальный средний дал имеет студент с зачетной книжкой под номером " << find_best(x) << endl;
							}
							else if (c == 3) {
								char* gt = (char*)malloc(sizeof(char) * 12);
								cout << "Введите номер группы, разделяя тире" << endl;

								cin >> gt;
								delete_group(x, gt);
								free(gt);
							}
							cout_table(x);
						}
						else if (c == 4) {
							break;
						}
						else {
							cin.clear();
							while (cin.get() != '\n') {
								cout << "Введено неверно, повторите попытку" << endl;
							}
						}
					}
					break;
				}
				else if (b == 3) {
					break;
				}
				else {
					cin.clear();
					while (cin.get() != '\n') {
						cout << "Введено неверно, повторите попытку" << endl;
					}
				}
			}
			break;
		}
		else {
			break;
		}
	}
	return 0;
}