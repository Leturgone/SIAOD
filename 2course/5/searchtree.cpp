#include <iostream>
#include <string>
#include "TreeAndFile.h"
using namespace std;


int main() {
    setlocale(0, "");
    string tfile_name;
    string bfile_name = "bf.dat";
    cout << "������� ��� �����: " << endl;
    cin >> tfile_name;
    cout << "---���� ������ � �������� ������---" << endl;
    cout << "1. ������� �������� ���� � ������������ ������ ������" << endl << "2.����� ������" << endl << "3.����� ������ �� ����� ��������� ������ ������" << endl <<"4. ������� ������ �� ����� ��������� ������ ������" <<endl<< "5. ����� ���� ������� ��������� �����" << endl << "6. ����� �� ���������" << endl;
    Bin_Tree tree;
    while (true) {
        int n;
        cout << "�������� ����� ��������: ";
        if (cin >> n) {
            if (n == 1) {//�������� �����
                if (create_bin_file(tfile_name, bfile_name) == 0) {
                    cout << "���� ������� ������"<< endl;
                    if (create_tree_from_file(bfile_name, tree) == 0) {
                        cout << "������ ������ ������� �������";
                    }
                    else {
                        cout << "������ ��� �������� ������ ������";
                    }
                }
                else {
                    cout << "������ ��� �������� �����";
                }
                cout << endl;
            }
            else if (n == 2) {//����� ������
                tree.printBinTree2("", tree.get_root(), false);
                
            }
            else if (n == 3) {
                string key;
                cout << "������� ���� ������, ������ � ������� ������ ��������: ";
                if (cin >> key) {
                    int z = search_in_file_by_tree(bfile_name, key,tree);
                    if (z == 1) {
                        cout << "������ ��� ������ ������ � ������ " << key << endl;
                    }
                    else if (z == 2) {
                        cout << "�� ������� ������� ����" << endl;
                    }
                    else if (z == -3) {
                        cout << "���� ������" << endl;
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
                string i;
                cout << "������� �������� �����: ";
                cin >> i;
                int z = delete_in_file_by_tree(bfile_name, i,tree);
                if (z == 0) {
                    cout << "������ ������� �������" << endl;
                }
                else if (z == -1) {
                    cout << "�� ������� ������� ������ � ������ " << i << " �� ����� ��������� �������" << endl;
                }
                else if (z == -2) {
                    cout << "�� ������� ������� ������ � ������ " << i << " �� ������ ��������� �������" << endl;
                }
            }
            else if (n == 5) {
                if (print_bin_file(bfile_name) == 1) {
                    cout << "�� ������� ������� ����";
                }
                cout << endl;
            }
            else if (n == 6) {
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
