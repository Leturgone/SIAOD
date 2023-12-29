#include <iostream>
#include <string>
#include <chrono>
#include "hashtabfuctions.h"
#include "SearchTree.h"
#include "BalanceTree.h"
#include "binfunctions.h"
using namespace std;

//1) ��������� ������ �� ����� � �������� ������� � �������(�������
//�������� : ���� � ����� ������ � ���� ������ � �����, � ��� ������ �
//�������� ���������� �������� �������������� ����).
//2) ������� ������ �� ������� ��� �������� �������� ����� � �������������� �� �����.
//3) ����� ������ � ����� �� �������� �����(����� ���� � ��� - �������,
//�������� ����� ������ � ���� ������ � �����, ��������� ������ ������
//� ������ �� �� ������).
//

int insert_rec_from_file(string& namebf, Hash_Table& table) {
    int numRecord = 0;
    fstream ibf(namebf, ios::in | ios::out | ios::binary);
    if (!ibf) {
        return -1;
    }
    violation_record r;
    while ((ibf.read(reinterpret_cast<char*>(&r), sizeof(violation_record)))) {
        if (table.search_el(r.car_num) == -1) {
            table.insert_el(r.car_num, numRecord);
            numRecord++;
        }
        else {
            return -1;
        }
    }
    ibf.close();
    return 0;
}
int delete_rec_from_file(char key[], string namebf, Hash_Table& table) {
    if (table.search_el(key) != -1) {
        int z = delete_rec_by_key(namebf, key);
        return table.delete_el(key);
    }
    else {
        return -1;
    }
}

int find_rec_by_key_hash(char key[], string namebf, Hash_Table& table) {
    int key_num = table.search_el(key);//�������� ����� ������
    if (key_num != -1) {
        return get_access_to_rec(namebf, key_num);//�������� ������ � ������ �� ��� ������

    }
    else {
        return -1;
    }
}
int create_balance_tree_from_file(string namebf, Bal_Bin_Tree& tree) {
    fstream ibf(namebf, ios::in | ios::binary);
    if (ibf.is_open()) {
        violation_record r;
        int n = 0;
        int c = 0;
        while (ibf.read((char*)&r, sizeof(r))) {
            n++;
            if (tree.insert_key_in_balance_tree(tree.get_root(), r.car_num, n, c) == -2) {
                return -2;
            }
        }
        cout << "������� ����� ���������  ��� ������� ����� : " << double(c) / double(n) << endl;
        ibf.close();
        return 0;
    }
    ibf.close();
    return 1;

}

//����� ������ � ����� � �������������� ���

int search_in_file_by_balance_tree(string namebf, string key, Bal_Bin_Tree& tree) {
    fstream ibf(namebf, ios::in | ios::binary);
    if (ibf.is_open()) {
        Node_of_btree* rec = tree.search_key_in_balance_tree(tree.get_root(), key);
        if (rec != nullptr) {
            get_access_to_rec(namebf, rec->data - 1);
            ibf.close();
            return 0;
        }
        else {
            ibf.close();
            return 1;
        }
    }
    ibf.close();
    return 1;

}

int delete_in_file_by_balance_tree(string namebf, string key, Bal_Bin_Tree& tree) {
    if (tree.delete_key_from_balance_tree(tree.get_root(), key) != 0) {
        return -2;
    }
    char charkey[10];
    key.copy(charkey, 10);
    charkey[6] = '\0';
    if (delete_rec_by_key(namebf, charkey) != 0) {
        return -1;
    }
    return 0;
}
int create_tree_from_file(string namebf, Bin_Tree& tree) {
    fstream ibf(namebf, ios::in | ios::binary);
    if (ibf.is_open()) {
        violation_record r;
        int n = 0;
        while (!ibf.eof()) {
            ibf.read((char*)&r, sizeof(r));
            n++;
            tree.insert_node_in_tree(tree.get_root(), r.car_num, n);
        }
        ibf.close();
        return 0;
    }
    ibf.close();
    return 1;

}

//����� ������ � ����� � �������������� ���

int search_in_file_by_tree(string namebf, string key, Bin_Tree& tree) {
    fstream ibf(namebf, ios::in | ios::binary);
    if (ibf.is_open()) {
        Node_of_tree* rec = tree.search_key_in_tree(tree.get_root(), key);
        if (rec != nullptr) {
            get_access_to_rec(namebf, rec->data - 1);
            ibf.close();
            return 0;
        }
        else {
            ibf.close();
            return 1;
        }
    }
    ibf.close();
    return 1;

}

int delete_in_file_by_tree(string namebf, string key, Bin_Tree& tree) {
    if (tree.delete_node(tree.get_root(), key) != 0) {
        return -2;
    }
    char charkey[10];
    key.copy(charkey, 10);
    charkey[6] = '\0';
    if (delete_rec_by_key(namebf, charkey) != 0) {
        return -1;
    }
    return 0;
}

int main() {
    setlocale(0, "");
    Hash_Table table(150);
    string tfile_name;
    string bfile_name = "bf.dat";
    cout << "������� ��� �����: " << endl;
    cin >> tfile_name;
    cout << "---���� ������ � �������� ������ ---" << endl;
    cout << "1. ������� �������� ����" << endl << "2. ����� ���� ������� ��������� �����" << endl << "---������� ������ � ������ ��� ������ ��� �������---" << endl << "3. ��������� ������ �� ����� � �������� �������� � �������" << endl <<  "4.  ����� ������ � ����� �� �������� �����" << endl << "6. ������� �������� ��� �������" << endl << "---������� ������ � ������ ��� ������ ������ ������---" << endl<< "7. ������� �������� ���� � ������������ ������ ������" << endl << "8.����� ������" << endl << "9.����� ������ �� ����� ��������� ������ ������" << endl<<"---������� ������ � ������ ��� ������ ������ ������ ������---" << endl << "10. ������� �������� ���� � ������������ ������ ������" << endl << "11. ����� ������" << endl << "12. ����� ������ �� ����� ��������� ������ ������" << endl << "13. ����� �� ���������" << endl;
    Bin_Tree tree;
    Bal_Bin_Tree tree1;
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
            else if (n == 2) {
                if (print_bin_file(bfile_name) == 1) {
                    cout << "�� ������� ������� ����";
                }
                cout << endl;
            }
            else if (n == 3) {
                int z = insert_rec_from_file(bfile_name, table);
                if (z == 0) {
                    cout << "��� ������� ������������" << endl;
                }
                else {
                    cout << "����� �� ����� ��� �������� � ��� �������" << endl;
                }
            }
            else if (n == 4) {
                char num[10];
                cout << "������� ���� ������ ( ����� ����������) , ������� ������ ����� � �����:" << endl;
                cin >> num;
                int z;
                auto start = std::chrono::steady_clock::now();
                z = find_rec_by_key_hash(num, bfile_name, table);
                auto end = std::chrono::steady_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                cout << "����� ������� " << duration << " ��" << endl;
                // ��������� ����� ������� � �������������

                if (z == -1) {
                    cout << "� ��� ������� ��� ������ � ����� ������" << endl;
                }
                else if (z != 0) {
                    cout << "������ ��� ��������� �������" << endl;
                }
            }
            else if (n == 6) {
                table.print();
            }
            else if (n == 7) {//�������� �����
                if (create_bin_file(tfile_name, bfile_name) == 0) {
                    cout << "���� ������� ������" << endl;
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
            else if (n == 8) {//����� ������
                tree.printBinTree2("", tree.get_root(), false);

            }
            else if (n == 9) {
                string key;
                cout << "������� ���� ������, ������ � ������� ������ ��������: ";
                if (cin >> key) {
                    auto start = std::chrono::steady_clock::now();
                    int z = search_in_file_by_tree(bfile_name, key, tree);
                    auto end = std::chrono::steady_clock::now();
                    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                    cout << "����� ������� " << duration << " ��" << endl;
                    // ��������� ����� ������� � �������������
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
            else if (n == 10) {//�������� �����
                if (create_bin_file(tfile_name, bfile_name) == 0) {
                    cout << "���� ������� ������" << endl;
                    if (create_balance_tree_from_file(bfile_name, tree1) == 0) {
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
            else if (n == 11) {//����� ������
                tree1.printBinTree2("", tree1.get_root(), false);

            }
            else if (n == 12) {
                string key;
                cout << "������� ���� ������, ������ � ������� ������ ��������: ";
                if (cin >> key) {
                    auto start = std::chrono::steady_clock::now();
                    int z = search_in_file_by_balance_tree(bfile_name, key, tree1);
                    auto end = std::chrono::steady_clock::now();
                    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                    cout << "����� ������� " << duration << " ��" << endl;
                    // ��������� ����� ������� � �������������
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

            else if (n ==13 ) {
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
    return 1;
}