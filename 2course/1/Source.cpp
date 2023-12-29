#include <iostream>
#include <bitset>

using namespace std;

void fun1() {
	//5-��, 11-��, 3 - �� � �������� 1 ��������� ��������������� ����� � ����������� ��������
	unsigned int digit = 0x1000;//4096 � ����������, 1000000000000 � ��������
	unsigned int mask = 0x0828;
	cout << "�����     : " << digit << "    " << bitset<16>(digit).to_string() << endl;
	cout << "�����     : " << mask << "    " << bitset<16>(mask).to_string() << endl;
	digit = digit | mask;
	cout << "��������� : " << (digit) << "    " << bitset<16>(digit).to_string() << endl;
}

void fun2() {
	//������ ������� ���� � �������� 0 ��������� ��������������� ����� � ����������� ��������
	unsigned int digit;
	cout << "������� �����: ";
	cin >> digit;
	unsigned int mask = (0xfffffff);//00001111111111111111111111111111 � ��������
	cout << "�����     : " << digit << "    " << bitset<32>(digit).to_string() << endl;
	cout << "�����     : " << mask << "    " << bitset<32>(mask).to_string() << endl;
	digit = digit & mask;
	cout << "��������� : " << (digit) << "    " << bitset<32>(digit).to_string() << endl;

}

void fun3() {
	//����������� �������� ������������ � ��������� ������� �������� �������� ���������� �� ����� 32 ��������� ��������������� ����������� ��������
	unsigned int digit;
	cout << "������� �����: ";
	cin >> digit;
	//����� �������� �������� ����� �� 32. �������������,��� ����� �������� �������� ����� ����� �� 2 � ������� 5
	cout << "�����     : " << digit << "    " << bitset<16>(digit).to_string() << endl;
	cout << "��������� : " << (digit<<5) << "    " << bitset<16>((digit << 5)).to_string() << endl;
}

void fun4() {
	//����������� �������� ������������ � ��������� ������� ����� �������� ���������� �� ����� 32 ��������� ��������������� ����������� ��������
	unsigned int digit;
	cout << "������� �����: ";
	cin >> digit;
	//��� ���������� ��������, �� �������� �������� ����� ������� �� 5, �� ���� �������
	cout << "�����     : " << digit << "    " << bitset<16>(digit).to_string() << endl;
	cout << "��������� : " << (digit >> 5) << "    " << bitset<16>((digit >> 5)).to_string() << endl;
}


void fun5() {
	//����������� �������� ������������ � ���������, � ������� ������������ 
	//������ ����������� ��������.� ��������� ������������ ����� � ����������.
	//�������� n-�� ���, ��������� �����(��� 2). ����� ���������������� �������� � ������� �������
	unsigned int digit;
	unsigned int mask;
	unsigned int nbite;
	cout << "������� �����: ";
	cin >> digit;
	cout << "������� ��� ����� ����, ������� ������ ��������: ";
	cin >> nbite;
	mask = 1 << 31;
	mask = mask>>(31-nbite);
	cout << "�����     : " << digit << "    " << bitset<32>(digit).to_string() << endl;
	cout << "�����     : " << mask << "    " << bitset<32>(mask).to_string() << endl;
	cout << "��������� : " << (digit&(~mask)) << "    " << bitset<32>((digit & (~mask))).to_string() << endl;
}



int main() {
	setlocale(0, "");
	cout << "-----������� 1---" << endl;
	cout << "���������� 1" << endl;
	fun1();
	cout << endl << "���������� 2" << endl;
	fun2();
	cout << endl << "���������� 3" << endl;
	fun3();
	cout << endl << "���������� 4" << endl;
	fun4();
	cout << endl << "���������� 5" << endl;
	fun5();
	return 0;
}
