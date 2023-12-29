#include <iostream>
using namespace std;
//���� ������� �������� n*m � ������. �������� ������� �� ������.
const int Rows = 100;
const int	Cols = 100;
void mcout(int a[Rows][Cols], int x, int y) {//����� �������
	for (int i = 0; i < x; i++) {
		for (int j = 0; j <y; j++) {
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
}
void  clav(int a[Rows][Cols], int x, int y) {//���������� � ����������
	for (int i = 0; i <x; i++) {
		cout << "������� �������� " << i << " ������ " << endl;
		for (int j = 0; j <y; j++) {
			if (!(cin >> a[i][j])) {
				cin.clear();//������
				while (cin.get() != '\n') {
					cout << "������� �������, ��������� �������" << endl;
					j = j - 1;
				}
			}
		}
	}
}
void mrand(int a[Rows][Cols], int x, int y) {//��������� ����������
	srand(time(0));
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			a[i][j] = 100 + rand() % 300;
		}
	}
}

void vcout(int a[Cols], int x) {//����� �������
	for (int i = 0; i < x; i++) {
		cout << a[i] << endl;
	}
}
void  vclav(int a[Cols], int x) {//���������� � ����������
	cout << "������� �������� ������" << endl;
	for (int j = 0; j < x; j++) {
		if (!(cin >> a[j])) {
			cin.clear();//������
			while (cin.get() != '\n') {
				cout << "������� �������, ��������� �������" << endl;
				j = j - 1;
			}
		}
	}
}
void vrand(int a[Cols], int x) {//��������� ����������
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
	cout << "������� ����� ���������: " << endl;
	mcout(a, x, y);
}
int main() {
	int m[Rows][Cols];
	int v[Cols];
	int r, c, a;
	setlocale(0, "");
	cout << "������������ ������ �2 \"��������� ������\". ������� Ը���" << endl;
	cout << "������ ����������� �������" << endl;
	while (true) {
		cout << "����� ����� ������� ����� ������ ������" << endl;
		cout << "������� ���������� ����� : ";
		if (cin >> r) {
			cout << "������� ���������� ��������: ";
			if (cin >> c) {
				while (true) {
					cout << "_______���� �������_______" << endl;
					cout << "�������� ������ ����������: " << endl;
					cout << "���� ������ ����� ������� 3" << endl;
					cout << "1.� ������" << endl << "2.��������" << endl;
					cin >> a;
					if (a == 1 || a == 2) {
						if (a == 1) {
							clav(m, r, c);
						}
						else {
							mrand(m, r, c);
						}
						cout << "����������� �������: " << endl;
						mcout(m, r, c);
						while (true) {
							cout << "_______���� �������_______" << endl;
							cout << "��������� ������ ������� " << c << ": " << endl;
							cout << "�������� ������ ����������: " << endl;
							cout << "���� ������ ����� ������� 3" << endl;
							cout << "1.� ������" << endl << "2.��������" << endl;
							cin >> a;
							if (a == 1 || a == 2) {
								if (a == 1) {
									vclav(v, c);
								}
								else {
									vrand(v, c);
								}
								cout << "����������� ������: " << endl;
								vcout(v, c);
								veconmat(m, v, r, c);;
							}
							else if (a == 3) {
								break;
							}
							else {
								cin.clear();
								while (cin.get() != '\n') {
									cout << "������� �������, ��������� �������" << endl;
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
							cout << "������� �������, ��������� �������" << endl;
						}
					}
				}

			}
			else {
				cin.clear();
				while (cin.get() != '\n') {
					cout << "������� �������, ��������� �������" << endl;
				}
			}
		}
		else {
			break;
		}
	}
	return 0;
}