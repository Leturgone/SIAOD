#include <iostream>
#include <string>
using namespace std;
#include<string>;
bool CheckNumChar(char *s) {
	int i = 0;
	int k = 0;
	int l = strlen(s);
	while (i<l)
	{
		if (s[i] >= '0' && s[i] <= '9') { 
			k++;
		}
		i++;
	}
	if (k == l){
		return true;
	}
	else {
		return false;
	}
}
char* ReverseC(char* x) {//переворот строки
	int length = strlen(x);
	int temp, i, j;
	for (i = 0, j = length - 1; i < j; i++, j--) {
		temp = x[i];
		x[i] = x[j];
		x[j] = temp;
	}
	return x;
}
string ReverseS(string x) {//переворот строки
	int length = x.length();
	int temp, i, j;
	for (i = 0, j = length - 1; i < j; i++, j--) {
		temp = x[i];
		x[i] = x[j];
		x[j] = temp;
	}
	return x;
}
string SumStr(string x, string y) {
	int i, su, ost, peren = 0; //сумма, остаток и перенос
	string s1,s2;
	int len1 = x.length();
	int len2 = y.length();
	if (len1 >= len2) { //выбор длинны числа
		s1 = ReverseS(x); //чтобы младшие разряды в числах при обработке в цикле совпадали. 
		s2 = ReverseS(y); }//x>=y
	else { 
		s1 = ReverseS(y); 
		s2 = ReverseS(x); 
		i = len1; //меняем длинны местами
		len1 = len2;
		len2 = i; 
	}
	string res(len1 + 1, '\0'); //+1 перенос в старший разряд

	for (i = 0; i < len1; i++)
	{
		int si1 = s1[i] - 48;
		su = si1 + peren;//складывание с переносом

		if (i < len2)//смотрим чтобы разряд был меньше длинны второго числа
		{
			int si2 = s2[i] - 48;
			su += si2;
		}

		peren = su / 10;    //раздробление полученного числа на остаток и то что нужно
		ost = su % 10;
		res[i] = ost + 48;//в число
	}

	if (peren > 0) { 
		res[i] = '1'; 
		res[i + 1] = '\0'; 
	}//возможнo увеличениe
	else {
		res[i] = '\0';
	}

	return ReverseS(res);
}
char* SumChar(char* x, char* y) {
	int i, su, ost, peren = 0; //сумма, остаток и перенос
	char* s1, * s2;
	int len1 = strlen(x);
	int len2 = strlen(y);
	if (len1 >= len2) { //выбор длинны числа
		s1 = ReverseC(x); //чтобы младшие разряды в числах при обработке в цикле совпадали. 
		s2 = ReverseC(y);
	}//x>=y
	else {
		s1 = ReverseC(y);
		s2 = ReverseC(x);
		i = len1; //меняем длинны местами
		len1 = len2;
		len2 = i;
	}
	char* res = new char[len1 + 1]; //+1 перенос в старший разряд

	for (i = 0; i < len1; i++)
	{
		int si1 = s1[i] - 48;
		su = si1 + peren;//складывание с переносом

		if (i < len2)//смотрим чтобы разряд был меньше длинны второго числа
		{
			int si2 = s2[i] - 48;
			su += si2;
		}

		peren = su / 10;    //раздробление полученного числа на остаток и то что нужно
		ost = su % 10;
		res[i] = ost + 48;//в число
	}

	if (peren > 0) {
		res[i] = '1';
		res[i + 1] = '\0';
	}//возможнo увеличениe
	else {
		res[i] = '\0';
	}

	return ReverseC(res);
}
bool CheckNumStr(string s) {
	int i = 0;
	int k = 0;
	int l = s.length();
	while (i < l)
	{
		if (s[i] >= '0' && s[i] <= '9') {
			k++;
		}
		i++;
	}
	if (k == l) {
		return true;
	}
	else {
		return false;
	}
}

int main() {
	const int len = 100;
	char* x = (char*)malloc(sizeof(char) * 100);
	char* y = (char*)malloc(sizeof(char) * 100);
	string sx;
	string sy;
	int z;
	setlocale(0, "");
	cout << "Лабораторная работа №3 \"Структура данных – строка\". Яснецов Фёдор" << endl;
	while (true) {
		cout << "Выберите структуру данных:" << endl << "1-нуль терминальная строка" << endl << "2-строка string " << endl << "Чтобы выйти введите 3" << endl;
		cin >> z;
		if (z == 1) {
			cout << "Введите первую строку" << endl;
			cin >> x;
			cout << "Введите вторую строку" << endl;
			cin >> y;
			if (CheckNumChar(x) and CheckNumChar(y)) {
				cout << "Сумма равна: " << SumChar(x, y)<<endl;
			}
			else {
				cout << "В в строках нет чисел" << endl;
			}
		}
		else if (z == 2) {
			cout << "Введите первую строку" << endl;
			cin >> sx;
			cout << "Введите вторую строку" << endl;
			cin >> sy;
			if (CheckNumStr(sx) and CheckNumStr(sy)) {
				cout << "Сумма равна: " << SumStr(sx, sy) << endl;
			}
			else {
				cout << "В в строках нет чисел" << endl;
			}
		}
		else if (z == 3) {
			break;
		}
		else {
			cin.clear();
			while (cin.get() != '\n') {
				cout << "Введено некорректно, повторите попытку" << endl;
			}
		}
	}
	free(x);
	free(y);
	return 0;
}