#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include<vector>
#include "functions.h"
int main() {
    setlocale(0, "");
    ofstream otf;
    string file_name;
    string file_name1 = "t2.txt";
    cout << "������� �������� ����� " << endl;
    cin >> file_name;
    cout << "---���� ������ � ������---" << endl;
    cout <<"1. ������� ����� ����" <<endl<< "2. ������� ���������� ���������� �����" << endl << "3. �������� ����� ������ � ����� �����;" << endl << "4. ��������� �������� �����, ������ ��� ���������� ����� � �����, � ������� ��� ��������" << endl << "5. ���������� ���������� ����� � �����" << endl << "6. ������� ��� ����� ����� � ����������� ������" << endl << "7. ����� �� ���������" << endl;
    while (true) {
        int n;
        cout << "�������� ����� ��������: ";
        if (cin >> n) {
            if (n == 1) {//�������� �����
                if (create_file(file_name)==0) {
                    cout << "���� ������� ������";
                }
                else {
                    cout << "������ ��� �������� �����";
                }
                cout << endl;
            }
            else if (n == 2) {//����� �����
                print_file(file_name);
                cout << endl;
            }
            else if (n == 3) {
                int new_num;
                cout << "������� �����, ������� ������ �������� � ����� �����: ";
                if (cin >> new_num) {
                    if (add_to_file(file_name, new_num)==0) {
                        cout << "����� " << new_num << " ������� ��������� � ����" << endl;
                    }
                    else {
                        cout << "�� ������� ������� ����" << endl;
                    }
                }
                else {
                    cin.clear();
                    while (cin.get() != '\n') {
                        cout << "������� �������, ��������� �������" << endl;

                    }
                }
            }
            else if (n == 4) {
                int i;
                cout << "������� ���������� ����� �����, �������� �������� ������ ��������: ";
                if (cin >> i) {
                    if (i > 0) {
                        int z = get_number(file_name, i);
                        if (z >= 0) {
                            cout << "����� ��� ������� " << i << ": " << z << endl;
                        }
                        else if (z == -1) {
                            cout << "�� ������� ������� ����" << endl;
                        }
                        else {
                            cout << "������ ��� ������ ����� � �������� " << i << endl;
                        }
                    }
                    else {
                        cout << "���������� ����� �� ����� ���� ���������������, ��������� �������" << endl;
                    }
                }
                else {
                    cin.clear();
                    while (cin.get() != '\n') {
                        cout << "������� �������, ��������� �������" << endl;

                    }
                }
            }
            else if (n == 5) {
                int c = count_num_in_file(file_name);
                if (c >= 0) {
                    cout << "���������� ����� � �����: " << c << endl;
                }
                else {
                    cout << "�� ������� ������� ����" << endl;
                }
            }
            else if (n == 6) {
                if (var_func(file_name) == 0) {
                    cout << "�������� ��������� �������" << endl;
                }
                else {
                    cout << "�� ������� ������� ����" << endl;
                }
            }
            else if (n == 7) {
                cout << "�������� ����� �� ���������" << endl;
                return 0;
            }
            else {
                cout << "�������� ��� ����� ������� ��� � ������, ��������� ����" << endl;
            }
        }
        else {
            cin.clear();
            while (cin.get() != '\n') {
                cout << "������� �������, ��������� �������" << endl;

            }
        }
    }
}