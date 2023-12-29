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
char* ReverseC(char* x) {//��������� ������
	int length = strlen(x);
	int temp, i, j;
	for (i = 0, j = length - 1; i < j; i++, j--) {
		temp = x[i];
		x[i] = x[j];
		x[j] = temp;
	}
	return x;
}
string ReverseS(string x) {//��������� ������
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
	int i, su, ost, peren = 0; //�����, ������� � �������
	string s1,s2;
	int len1 = x.length();
	int len2 = y.length();
	if (len1 >= len2) { //����� ������ �����
		s1 = ReverseS(x); //����� ������� ������� � ������ ��� ��������� � ����� ���������. 
		s2 = ReverseS(y); }//x>=y
	else { 
		s1 = ReverseS(y); 
		s2 = ReverseS(x); 
		i = len1; //������ ������ �������
		len1 = len2;
		len2 = i; 
	}
	string res(len1 + 1, '\0'); //+1 ������� � ������� ������

	for (i = 0; i < len1; i++)
	{
		int si1 = s1[i] - 48;
		su = si1 + peren;//����������� � ���������

		if (i < len2)//������� ����� ������ ��� ������ ������ ������� �����
		{
			int si2 = s2[i] - 48;
			su += si2;
		}

		peren = su / 10;    //������������ ����������� ����� �� ������� � �� ��� �����
		ost = su % 10;
		res[i] = ost + 48;//� �����
	}

	if (peren > 0) { 
		res[i] = '1'; 
		res[i + 1] = '\0'; 
	}//�������o ���������e
	else {
		res[i] = '\0';
	}

	return ReverseS(res);
}
char* SumChar(char* x, char* y) {
	int i, su, ost, peren = 0; //�����, ������� � �������
	char* s1, * s2;
	int len1 = strlen(x);
	int len2 = strlen(y);
	if (len1 >= len2) { //����� ������ �����
		s1 = ReverseC(x); //����� ������� ������� � ������ ��� ��������� � ����� ���������. 
		s2 = ReverseC(y);
	}//x>=y
	else {
		s1 = ReverseC(y);
		s2 = ReverseC(x);
		i = len1; //������ ������ �������
		len1 = len2;
		len2 = i;
	}
	char* res = new char[len1 + 1]; //+1 ������� � ������� ������

	for (i = 0; i < len1; i++)
	{
		int si1 = s1[i] - 48;
		su = si1 + peren;//����������� � ���������

		if (i < len2)//������� ����� ������ ��� ������ ������ ������� �����
		{
			int si2 = s2[i] - 48;
			su += si2;
		}

		peren = su / 10;    //������������ ����������� ����� �� ������� � �� ��� �����
		ost = su % 10;
		res[i] = ost + 48;//� �����
	}

	if (peren > 0) {
		res[i] = '1';
		res[i + 1] = '\0';
	}//�������o ���������e
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
	cout << "������������ ������ �3 \"��������� ������ � ������\". ������� Ը���" << endl;
	while (true) {
		cout << "�������� ��������� ������:" << endl << "1-���� ������������ ������" << endl << "2-������ string " << endl << "����� ����� ������� 3" << endl;
		cin >> z;
		if (z == 1) {
			cout << "������� ������ ������" << endl;
			cin >> x;
			cout << "������� ������ ������" << endl;
			cin >> y;
			if (CheckNumChar(x) and CheckNumChar(y)) {
				cout << "����� �����: " << SumChar(x, y)<<endl;
			}
			else {
				cout << "� � ������� ��� �����" << endl;
			}
		}
		else if (z == 2) {
			cout << "������� ������ ������" << endl;
			cin >> sx;
			cout << "������� ������ ������" << endl;
			cin >> sy;
			if (CheckNumStr(sx) and CheckNumStr(sy)) {
				cout << "����� �����: " << SumStr(sx, sy) << endl;
			}
			else {
				cout << "� � ������� ��� �����" << endl;
			}
		}
		else if (z == 3) {
			break;
		}
		else {
			cin.clear();
			while (cin.get() != '\n') {
				cout << "������� �����������, ��������� �������" << endl;
			}
		}
	}
	free(x);
	free(y);
	return 0;
}