#include <iostream>
#include <vector>
using namespace std;
void vstav(vector<int>& a, int& n, int l) {
	a.emplace(a.begin(),l);//������� ��������
	n = n + 1;
}

void ruv(vector<int> &x, int n) {//������ ����������
	setlocale(0, "");
	cout << "�������" << n << "�����" << endl;
	for (int i = 0; i < n; i++)
	{
		if (!(cin >> x[i])) {
			cin.clear();//������
			while (cin.get() != '\n') {
				cout << "������� �������, ��������� �������" << endl;
				if (i > 0) {
					i = i - 1;
				}
			}
		}
	}
}
void mas_cout(vector<int> x, int n) {//����� �������
	for (int i = 0; i < n; i++) {
		cout << " " << x[i];
	}
}
void rav(vector<int> &a, const int l) {//��������� ����������
	for (int i = 0; i < l; i++)
	{
		srand(time(0));
		for (i = 0; i < l; i++)
		{
			a[i] = 100 + rand() % 300;
		}
	}
}
void del(vector<int> &x, int &n, int j) {//�������� ��������
	x.erase(x.begin() + j);
	n = n - 1;
}
bool arif(vector<int> a, int n) {//�������� �� ����������
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
bool equal(int n) {//�������� �� ���������� �����
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
	cout << "������������ ������ �1 \"���������� ������\". ������� Ը���" << endl;
	cout << "������ �� �������" << endl;
	while (true) {
		cout << "�������� ������ ���������� �������:" << endl << "1 - � ������" << endl << "2 - ��������� ��������� �����" << endl;
		cout << "������� ����� �������� ������ (1/2) " << endl;
		cout << "����� ����� ������� 3" << endl;
		if ((cin >> a) && (a == 1 || a == 2)) {
			cout << "������� ���������� �������������� ��������� �������" << endl;
			if ((cin >> n) && (n > 0)) {
				if (a == 1) {
					cout << "��� �������" << endl;
					ruv(vx, n);
				}
				else {
					rav(vx, n);
				}
				cout << "��������� ������ : " << endl;
				mas_cout(vx, n);
				while (true) {
					cout << endl << "������� ����� ������� " << endl << "1.�������� ����� �������� � ������ ����� ������ ��������� �������." << endl <<
						"2.����������, �������� �� ����� ������� �������������� ����������." << endl <<
						"3.������� �������� �������, � ��������� ������� ������ � ��������� ����� ���������." << endl;
					cout << "����� ����� ������� 4" << endl;
					cin >> z;
					if ((z == 1) || (z == 2) || (z == 3)) {
						if (z == 1) {
							cout << "������� ����� ��������,������� ����� �������� � ������ ����� ������ ��������� �������" << endl;
							while (true) {
								if (cin >> el) {
									vstav(vx, n, el);
									cout << "������ ����� ������� " << endl;
									mas_cout(vx, n);
									break;
								}
								else {
									cin.clear();
									while (cin.get() != '\n') {
										cout << "������� ������ ���� ����� ������,��������� �������" << endl;
									}
								}
							}
						}
						if (z == 2) {
							if (arif(vx, n)) {
								cout << "�����  ������� �������� �������������� ����������" << endl;
							}
							else {
								cout << "�����  ������� �� �������� �������������� ����������" << endl;
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
								cout << endl << "������ ����� ��������" << endl;
								mas_cout(vx, n);
							}

							else {
								cout << endl << "� ������� ��� ����� ��������" << endl;
							}
						}
					}
					else if (z == 4) {
						break;
					}
					else {
						cin.clear();
						while (cin.get() != '\n') {
							cout << "��� ������� � ����� �������, ��������� ����" << endl;
						}
					}
				}
			}
			else {
				cin.clear();
				while (cin.get() != '\n') {
					cout << "n ������ ���� ������ ����,��������� �������" << endl;
				}
			}

		}
		else if (a == 3) {
			break;
		}
		else {
			cin.clear();
			while (cin.get() != '\n') {
				cout << "������� �����������, ��������� �������" << endl;
			}
		}
	}
	return 0;
}