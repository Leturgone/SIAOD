#include <iostream>
#include <vector>
#include "hashtabfuctions.h"
using namespace std;

int main() {
    setlocale(0, "");
    Hash_Table table(100);
    const int keyCount = 5;
    int num;
    char keys[keyCount][10] = {
        "ABC123",
        "DEF124",
        "ABC245",
        "BHT763",
        "ABC222"};
    cout << "1.���� ������� ������ � ������� ��� �������� � � ���������: " << endl;
    // ������� ��������� � ���-�������
    for (int i = 0; i < keyCount; i++) {
        num = i + 1;
        if ((table.insert_el(keys[i],num)) == 0){
            cout << "���� " << keys[i] << " ������� �������� � �������" << endl;
        }
        else {
            cout << "������ ��� ������� ����� " << keys[i] << endl;
        }
    }
    table.print();
    // ����� ��������� � ���-�������
    cout << "2.���� ������ ������ � ��� �������: " << endl;
    for (int i = 0; i < keyCount; i++) {
        int result = table.search_el(keys[i]);
        if (result != -1) {
            cout << "������� � ������  " << keys[i] << " ������ � ��� ������� ��� �������� " << result << endl;
        }
        else {
            cout << "������� � ������ " << keys[i] << " �� ������" << endl;
        }
    }
    table.print();
    cout << "3.���� �������������� �������: " << endl;
    // ����� ����������� ���-�������
    cout << "---������� ��������������---" << endl;
    table.rehash();
    table.print();
    cout << "4.�������� ������ � �������: " << endl;
    // �������� ��������� �� ���-�������
    int result = table.delete_el(keys[0]);
    if (result == 0) {
        cout << "������� � ������ " << keys[0] << " ������� ������" << endl;
    }
    else {
        cout << "������ ��� �������� ����� " << keys[0] << endl;
    }
    table.print();
    cout << "5.����������� ���� ��� ������ � ������� �������: " << endl;
    result = table.search_el(keys[4]);
    if (result != -1) {
        cout << "������� � ������  " << keys[4] << " ������ � ��� �������" << endl;
    }
    else {
        cout << "������� � ������ " << keys[4] << " �� ������" << endl;
    }
    return 0;

}