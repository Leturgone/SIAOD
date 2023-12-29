#include <iostream>
using namespace std;
#include <vector>
#include <chrono>
#include <bitset>
void set_bit(unsigned int arr[], int num) {//������� ��� ��������� ����
	//������������ ����� � ������ � ����� �������� ����� ��������� ��� ���, ��� ������ � �������
	arr[num>>5]= arr[num >> 5] | (1 << (num&(0x1f)));
}

const long int N = 10000000; // ���������� �����
unsigned int bit_arr[N / 32];//������ �����, �� ����, � ��� �������� � ������� 10**7/32= 312500 ���������,

int main() {
	setlocale(0, "");
	cout << "-----������� 2----" << endl;
	/*
	* ����������� ������ �� ���������� ������ �����, ��������� ��� �������������
	������ ����� (10 7 ����������� �����) � ������, ������ �����.

	����������. ������ � �������� �� ������� ����������� �� ������������ �������.
	���� �� ������������, ������������ ���� �� ������������������, �������� � ����������.
	*/
	vector<int> number_arr;
	//const int N = 107;
	int n;
	cout << "������� ���������� �����: ";
	cin >> n;
	int k;
	int z=0;
	int temp;

	//� ������ �� ������� �� 32 ����.

	cout << endl << "������� �����: " << endl;

	//���������� �������, ������� ����� �����������
	for (int i = 0; i < n; i++) {
		cin >> k;
		number_arr.push_back(k);
	}
	//��������  ������� ����������. ������� - ������� �������� ������� ����� ������ ��������������� ��� ��� ��������������� �������.
	//������ - ��������� ������ �����
	auto start_time = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < n; i++) {//���� �� ��������� �������
		set_bit(bit_arr, number_arr[i]);
	}

	//��������� ������ �� ��������
	for (int i = 0; i < N/32; i++) {
		for (int j = 0; j < 32; j++) {
			temp = 0;
			temp = temp+(1 << j);
			if ((bit_arr[i] & temp) == temp) {
				number_arr[z]=(i * 32 + j);
				z++;
			}
		}
	}
	auto end_time = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
	cout << "����� ����������: " << duration.count() << " ms" << endl;
	cout << "��������������� ������: " << endl;
	for (int i = 0; i < number_arr.size(); i++) {
		cout << number_arr[i]<<"  ";
	}
	cout << endl;
	return 0;
}
