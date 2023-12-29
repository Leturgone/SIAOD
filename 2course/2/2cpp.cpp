#include <iostream>
#include <fstream>
#include "binfunctions.h"


int main() {
	setlocale(0, "");
	string tfile_name;
    string bfile_name = "bf.dat";
	cout << "������� ��� �����: " << endl;
	cin >> tfile_name;
	cout << "---���� ������ � �������� ������---" << endl;
    cout << "1. ������� �������� ����" << endl << "2. ��������� ������ ��������� � ��������� ����" << endl << "3. ����� ���� ������� ��������� �����" << endl << "4. �������� ������ � ������ �� ����������� ������" << endl << "5. ������� ������ � �������� ��������� �����" << endl << "6. ������������ ������ ��������� �� ���������� ��������� ������." << endl << "7. ��������� ����� ������ ����� �� ���� ���� �� ��������� ���� � �� �������� ������." << endl << "8. ����� �� ���������" << endl;
    while (true) {
        int n;
        cout << "�������� ����� ��������: ";
        if (cin >> n) {
            if (n == 1) {//�������� �����
                if (create_bin_file(tfile_name, bfile_name) == 0) {
                    cout << "���� ������� ������";
                }
                else {
                    cout << "������ ��� �������� �����";
                }
                cout << endl;
            }
            else if (n == 2) {//��������� ������ ��������� � ���������
                if (convert_bin_to_txt("bft.txt", bfile_name) == 0) {
                    cout << "���� ������� ������";
                }
                else {
                    cout << "������ ��� �������� �����";
                }
                cout << endl;
            }
            else if (n == 3) {
                if (print_bin_file(bfile_name) == 1) {
                    cout << "�� ������� ������� ����";
                }
                cout << endl;
            }
            else if (n == 4) {
                int i;
                cout << "������� ���������� ����� ������, ������ � ������� ������ ��������: ";
                if (cin >> i) {
                    if (i > 0) {
                        int z = get_access_to_rec(bfile_name,i-1);
                        if (z == 1) {
                            cout << "������ ��� ������ ����� � �������� " << i << endl;
                        }
                        else if (z == 2) {
                            cout << "�� ������� ������� ����" << endl;
                        }
                        else if (z == -3) {
                            cout << "���� ������" << endl;
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
                char i[10];
                cout << "������� �������� �����: ";
                cin >> i;
                int z = delete_rec_by_key(bfile_name, i);
                if (z == 0) {
                    cout << "������ ������� �������" << endl;
                }
                else if (z == -1) {
                    cout << "�� ������� ������� ����" << endl;
                }
                else if (z == -2) {
                    cout << "�� ������� ����� ������ � ������ " << i << " ��������� �������" << endl;
                }
                else if (z == -3) {
                    cout << "���� ����" << endl;
                }
            }
            else if (n == 6) {
                char num[10];
                string nbfile_name = "bf.dat";
                cout << "������ ����� ����������: " << endl;
                cin >> num;
                int z = form_violation_list(nbfile_name, num);
                if (z == 0) {
                    cout << "�������� ��������� �������" << endl;

                }
                else if (z == -2) {
                    cout << "��� ������ ��� ����� �������" << endl;
                }
                else if (z == -3) {
                    cout << "���� ����" << endl;
                }
                else {
                    cout << "�� ������� ������� ����" << endl;
                }
            }
            else if (n == 7) {
                double stat;
                char date[10];
                cout << "������� ����� ������: ";
                if (cin >> stat) {
                    cout << "������� ����: ";
                    cin >> date;
                    int z= double_fin_in_date(bfile_name, date,stat);
                    if (z== 0) {
                        cout << "�������� ��������� �������" << endl;
                    }
                    else if (z == -1) {
                        cout << "�� ������� ������� ����" << endl;
                    }
                    else if (z == -2) {
                        cout << "������ � ����������� ������� �� �������" << endl;
                    }
                    else {
                        cout << "�� ������� ������� ����" << endl;
                    }
                }
                else {
                    cin.clear();
                    while (cin.get() != '\n') {
                        cout << "����� ������ ������ �������, ��������� ����" << endl;
                    }
                }
            }
            else if (n == 7) {

            }
            else if (n == 8) {
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
	return 0;
}

