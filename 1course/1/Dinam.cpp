//#include <iostream>
//using namespace std;
//void vstav(int *&a, int &n, int l) {//�����;
//	for (int i = n;i >= 0; i--) {
//		a[i] = a[i - 1];
//	}
//	a[0] = l;
//	n++;
//	realloc(a, sizeof(int) * (n + 1));
//}
//void ruv(int *x,int n) {//������ ����������
//	setlocale(0, "");
//	cout << "�������" << n << "�����" << endl;
//	for (int i = 0; i < n; i++)
//	{
//		if (!(cin >> x[i])) {
//			cin.clear();//������
//			while (cin.get() != '\n') {
//				cout << "������� �������, ��������� �������" << endl;
//				if (i > 0) {
//					i = i - 1;
//				}
//			}
//		}
//	}
//}
//void mas_cout(int *x, int n) {//����� �������
//	for (int i = 0; i<n; i++){	
//		cout << " " << x[i];
//	}
//}
//void rav(int * const a, const int l) {//��������� ����������
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
//bool arif(int *a, int n) {//�������� �� ����������
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
//bool equal(int n) {//�������� �� ���������� �����
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
//void del(int *x, int &n, int j) {//�������� ��������
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
//	cout << "������������ ������ �1 \"���������� ������\". ������� Ը���" << endl;
//	cout << "������ �� ������������ �������" << endl;
//	while (true) {
//		cout << "�������� ������ ���������� �������:" << endl << "1 - � ������" <<endl<< "2 - ��������� ��������� �����" << endl;
//		cout << "������� ����� �������� ������ (1/2) " << endl;
//		cout << "����� ����� ������� 3" << endl;
//		if ((cin >> a) && (a == 1 || a == 2)) {
//			cout << "������� ���������� �������������� ��������� �������" << endl;
//			if ((cin >> n)&&(n > 0)){
//				pr = true;
//				if (a==1){
//					cout << "��� �������������" << endl;
//					ruv(dx, n);
//				}
//				else {
//					rav(dx, n);
//				}
//				cout << "��������� ������� : " << endl;
//				mas_cout(dx, n);
//				while (true) {
//					cout << endl << "������� ����� ������� " << endl << "1.�������� ����� �������� � ������ ����� ������ ��������� �������." << endl <<
//						"2.����������, �������� �� ����� ������� �������������� ����������." << endl <<
//						"3.������� �������� �������, � ��������� ������� ������ � ��������� ����� ���������." << endl;
//					cout << "����� ����� ������� 4" << endl;
//					cin >> z;
//					if ((z == 1) || (z == 2) || (z == 3)) {
//						if (z == 1) {
//							cout << "������� ����� ��������,������� ����� ��������� ������ ����� ������ ��������� �������" << endl;
//							while (true) {
//								if (cin >> el) {
//									vstav(dx, n, el);
//									cout << "������������ ������ ����� ������� " << endl;
//									mas_cout(dx, n);
//									break;
//								}
//								else {
//									cin.clear();
//									while (cin.get() != '\n') {
//										cout << "������� ������ ���� ����� ������,��������� �������" << endl;
//									}
//								}
//							}
//						}
//						if (z==2){
//							if (arif(dx, n)) {
//								cout << "�����  ������������� ������� �������� �������������� ����������" << endl;
//							}
//							else {
//								cout << "�����  ������������� ������� �� �������� �������������� ����������" << endl;
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
//								cout << endl << "������������ ����� ��������" << endl;
//								mas_cout(dx, n);
//							}
//
//							else {
//								cout << endl << "� ������������ ������� ��� ����� ��������" << endl;
//							}
//						}
//					}
//					else if (z == 4) {
//						break;
//					}
//					else {
//						cin.clear();
//						while (cin.get() != '\n') {
//							cout << "��� ������� � ����� �������, ��������� ����" << endl;
//						}
//					}
//				}
//			}
//			else {
//				pr = false;
//				cin.clear();
//				while (cin.get() != '\n') {
//					cout << "n ������ ���� ������ ����,��������� �������"<<endl;
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
//				cout << "������� �����������, ��������� �������" << endl;
//			}
//		}
//	}
//	free(dx);
//	return 0;
//}