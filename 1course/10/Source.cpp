//1)	��� �����.����� ���������� ��������� �������� ��������� � �����.
//2)	��� �����.������� �� ������ ��� �������� ������� �� ���������� 00:00 �� 02 : 00. �� � ����� ���� �������� ����� ���� �� ������ �������.����������� �������� ������ - ����
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <windows.h>
#include <regex>
using namespace std;
int* prefixF(string s) {
    int n = s.size();
    int* pi = new int[n];
    memset(pi, 0, n * sizeof(int));
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) {
            j = pi[j - 1];
        }
        if (s[i] == s[j]) {
            j++;
        }
        pi[i] = j;
    }

    return pi;
}
int boyerMoore(string text, string pattern, int &C) {
    int n = text.size();
    int m = pattern.size();
    int* pi = prefixF(pattern);
    int i = 0, j = 0, count = 0;
    while (i < n) {
        if (text[i] == pattern[j]) {
            C++;
            i++;
            j++;
        }
        else {
            if (j == 0) {
                C++;
                i++;
            }
            else {
                j = pi[j - 1];
            }
        }
        if (j == m) {
            C++;
            count++;
            j = pi[j - 1];
        }
    }

    delete[] pi;
    return count;
}
string removeTime(string &text) {
    regex time_regex("(|(\s|\w))((00|01|02):[0-5][0-9])(\s|)");
    string result = std::regex_replace(text, time_regex, "");
    return result;
}
int main() {
    string text, sub;
    int a,C,count;
    setlocale(0, "");
    cout << "������������ ������ �10 \"����� � ����� �������. ���������. ������������� ����������..\". ������� Ը��� " << endl;
    while (true) {
        cout << "�������� �������" << endl;
        cout << "1) ��� �����.����� ���������� ��������� �������� ��������� � �����." << endl << "2)��� �����. ������� �� ������ ��� �������� ������� �� ���������� 00:00 �� 02 : 00. �� � ����� ���� �������� ����� ���� �� ������ �������." << endl;
        cout << "����� ����� ������� 3" << endl;
        cin >> a;
        if (a == 1) {
            //��������� �����
            string text;
            ifstream file("test.txt");
            if (file.is_open()) {
                getline(file, text);
                file.close();
            }

            else {
                cout << "������ ������ �����" << endl;
            }
            while (true) {
                for (long int i = 100000; i <= 500000; i = i + 100000) {
                    string searchText = text.substr(0, i);
                    C = 0;
                    cout << endl;
                    cout << "���������� ��������: " << i<< endl;
                    cout << "------�������� �����---------" << endl;
                    string pattern_1 = "�";
                    auto start = std::chrono::steady_clock::now();
                    count=boyerMoore(searchText, pattern_1, C);
                    auto end = std::chrono::steady_clock::now();
                    std::chrono::duration<double> elapsed_seconds1 = end - start;//�����������������
                    cout << "���������� ����������: " << count<< endl;
                    cout << "���������� ��������� C: " << C << endl;
                    cout<<"����� ������ "<< elapsed_seconds1.count()<<" c" << endl;
                    cout << endl;
                    cout << "------���������� �����---------" << endl;
                    pattern_1 = "1947830274145709";
                    start = std::chrono::steady_clock::now();
                    count = boyerMoore(searchText, pattern_1, C);
                    end = std::chrono::steady_clock::now();
                    elapsed_seconds1 = end - start;//�����������������
                    cout << "���������� ����������: " << count << endl;
                    cout << "���������� ��������� C: " << C << endl;
                    cout << "����� ������ " << elapsed_seconds1.count() << " c" << endl;
                    
                }
                break;

            }
        }
        if (a == 2) {
            string text;
            cout << "������� �����: ";
            cout << "������ �����" << endl;
            cout << "________________________________________________________________________________________" << endl;
            text = "08:00. I took a shower,01:24. Had breakfast, and started working. At 12:30, I went on a lunch break and returned to work at 01:00. I finished work at 19:00, had dinner, watched TV until 02:00, and then went to bed.";
            cout << text << endl;
            cout << "________________________________________________________________________________________" << endl;
            cout << "����� ��� �������� ������� �� ���������� 00:00 �� 02:00" << endl;;
            cout << removeTime(text) << endl;

        }
        if (a == 3) {
            break;
        }
    }
    return 0;
}
