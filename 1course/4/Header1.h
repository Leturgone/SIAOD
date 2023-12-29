#pragma once
#include <iostream>
#include <vector>
using namespace std;
struct STUDENT{
	int BookNum;
	char name[20];
	char group[11];
	int marks[5];
};
struct Table {//��������� �������� ������ �� �������
	int l;
	vector<STUDENT> members;
};
float sr_b(int x[]) {//������� ����
	float s = 0;
	for (int i = 0; i < 5; i++) {
		s = s + x[i];
	}
	return s / 5;
}
void cin_note(STUDENT& n) {//��������� ��������� ������ � ����������
	cout << "������� ����� �������� ������ ��������" << endl;
	cin >> n.BookNum;
	cout << "������� ��� ��������" << endl;
	cin.get();
	cin.getline(n.name, 300);
	cout << "������� ����� ������ ��������" << endl;
	cin.getline(n.group, 300);
	cout << "������� ������ �� ������ ��������" << endl;
	for (int i = 0; i < 5; i++) {
		cin >> n.marks[i];
	}
	cout << "���������" << endl;
}
void struct_sort(Table& x) {
	for (int i = 0; i < x.l - 1; i++)
		for (int j = i; j < x.l; j++)
		{
			if (x.members[i].BookNum > x.members[j].BookNum)
			{
				STUDENT tmpStud = x.members[i];
				x.members[i] = x.members[j];
				x.members[j] = tmpStud;
			}
		}
}

void cout_table(Table& x) {//����� ������� �� �����
	cout << "________________________________________________________________________________________________" << endl;
	cout << "��������" << endl;
	struct_sort(x);
	cout << "����� �������� ������\t" << "��� �������� \t" << "������ �������� \t" << "������� ���� ��������" << endl;
	for (int i = 0; i < x.members.size(); i++)
	{
		cout << x.members[i].BookNum << "\t\t\t" << x.members[i].name << "\t" << x.members[i].group << "\t\t" << sr_b(x.members[i].marks) << endl;
	}
	cout << "________________________________________________________________________________________________" << endl;
}

void cin_new(Table& x, STUDENT n) {//�������� ����� ������ � ������� �������� ��������������� ���������� � ������� ����������� �����
	cin_note(n);
	x.members.push_back(n);
	x.l = x.l + 1;
	struct_sort(x);
}
int find_best(Table a) {//����� ����� �������� ������ �������� � ������������ ������� ������.
	int maxBook = 0;
	double maxM = 0;
	for (int i = 0; i < a.l; i++) {
		if (sr_b(a.members[i].marks) > maxM) {
			maxM = sr_b(a.members[i].marks);
			maxBook = a.members[i].BookNum;
		}
	}
	return maxBook;
}
void delete_group(Table& x, char* g) {//������� �� ������� ��������� �������� ������.
	int count=0;
	for (int i = 0; i < x.members.size(); i++)
	{
		count = 0;
		for (int j = 0; j < 10; j++) {
			if (x.members[i].group[j] == g[j]) {
				count = count + 1;
				if (count == 10) {
					x.members.erase(x.members.begin() + i);;
					x.l = x.l - 1;
					i = 0;
				}
			}
		}
	}
	if (count==0) {
		cout << "��� ������ � ����� �������,����� ������ ������ �������� �� 10 ��������"<<endl;
	}

}