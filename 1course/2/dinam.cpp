#include <iostream>
using namespace std;
//���� ������� �������� n*m � ������. �������� ������� �� ������.
void dmcout(int **a, int x, int y) {//����� �������
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
}
void  dclav(int **a, int x, int y) {//���������� � ����������
	for (int i = 0; i < x; i++) {
		cout << "������� �������� " << i << " ������ " << endl;
		for (int j = 0; j < y; j++) {
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
void dmrand(int **a, int x, int y) {//��������� ����������
	srand(time(0));
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			a[i][j] = 100 + rand() % 300;
		}
	}
}

void dvcout(int *a, int x) {//����� �������
	for (int i = 0; i < x; i++) {
		cout << a[i] << endl;
	}
}
void  dvclav(int *a, int x) {//���������� � ����������
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
void dvrand(int *a, int x) {//��������� ����������
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
	cout << "������� ����� ���������: " << endl;
	dmcout(a, x, y);

}
int main() {
	int r, c, a;
	int** dm=nullptr;//nullptr � �������� �����, ��������� � C++11 ��� �������� ��������� �������� ���������.
	int* dv=nullptr;
	setlocale(0, "");
	cout << "������������ ������ �2 \"��������� ������\". ������� Ը���" << endl;
	cout << "������ �� ������������ �������" << endl;
	while (true) {
		cout << "����� ����� ������� ����� ������ ������" << endl;
		cout << "������� ���������� ����� : ";
		if (cin >> r) {
			cout << "������� ���������� ��������: ";
			if (cin >> c) {
				dm = new int* [r];//��������� �� ������� ������, ���������� rows ���������, 
				//������ �� ������� ����� ��� int * � ��������� �� ��������� ������� ������, ���� ��� �� ����������.
				for (int i = 0; i < r; ++i)
				{
					dm[i] = new int[c];//������ ��� dm[i] ����������� �� ������� ������ �� cols ��������� ���� int: 
				}
				dv = new int[r];//������ ��� ���������
				while (true) {
					cout << "_______���� �������_______" << endl;
					cout << "�������� ������ ����������: " << endl;
					cout << "���� ������ ����� ������� 3" << endl;
					cout << "1.� ������" << endl << "2.��������" << endl;
					cin >> a;
					if (a == 1 || a == 2) {
						if (a == 1) {
							dclav(dm, r, c);
						}
						else {
							dmrand(dm, r, c);
						}
						cout << "����������� �������: " << endl;
						dmcout(dm, r, c);
						while (true) {
							cout << "_______���� �������_______" << endl;
							cout << "��������� ������ ������� " << c << ": " << endl;
							cout << "�������� ������ ����������: " << endl;
							cout << "���� ������ ����� ������� 3" << endl;
							cout << "1.� ������" << endl << "2.��������" << endl;
							cin >> a;
							if (a == 1 || a == 2) {
								if (a == 1) {
									dvclav(dv, c);
								}
								else {
									dvrand(dv, c);
								}
								cout << "����������� ������: " << endl;
								dvcout(dv, c);
								dveconmat(dm, dv, r, c);;
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
			for (int i = 0; i < r; i++) {//�������� �����
				delete[] dm[i];
			}
			delete[] dm;
			delete[] dv;
			break;

		}
	}
	return 0;
}