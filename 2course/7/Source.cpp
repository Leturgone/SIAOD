//28 �������� ������� ������ �� ���������, 
//������������� �� ����� ����� �� ������
//����������� ���� �� �����.�������� �����
//���������� ������ �� 1 �� N.�������
//�������� ����� �� �������� � ������� 1. ��
//����� �������� ������ �� ���������� �� 1 ��
//K ���������, ������ �� ��������.�� ������
//�������� �������� ����� ������������ ����
//����������� � ��������.����������, ���
//����� ������� ���������, ����� ���������
//��� ����� ������ �������.

//������������ ����������������
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;
void dinamic_method(int N, int K,vector<int>frogs) {
    vector<int> dp(N + 1, 10000);//������ ��� �������� ��������� ���������� ��������
    vector<int> jumps(N + 1, 0); //������ ��� �������� �������
    dp[1] = 0;
    int P=0;
    //������� ������� � �������
    for (int i = 2; i <= N; i++) {
        int frog = frogs[i];
        for (int j = 1; j <= K; j++) {
            if (j < i) {
                //������� ���� �������
                if (dp[i] > dp[i - j] + frog) {//���� ��������� ������ �������� ��������, �� ���������
                    dp[i] = dp[i - j] + frog;
                    jumps[i] = j; // ��������� ����� ������
                }
            }
            P = P + 1;
        }
    }
    cout << "������� ������� (����� ������������� ���������������): ";
    int cur = N;
    while (cur > 1) {
        cout << jumps[cur] << " ";
        cur -= jumps[cur];
    }
    cout << endl;
    cout << "���������� ��������� (����� ������������� ���������������): "<<P << std::endl;
}

int brute_force_method(int N, int K, vector<int>& frogs, vector<int>& jumps,int& P) {
    if (N <= 1) {
        return 0;
    }

    int min_frogs = 10000;//���������� ����������� �������

    for (int i = 1; i <= K; i++) {
        P = P + 1;
        if (i < N) {

            //��� ��������� ���������� ����������� ��� ������� N - i � ����������� � ����������� �������.
            //���� ��� ��������� ������ �������� �������� min_frogs, �� ��� �����������, � ����� ������ i ����������� � ������� jumps ��� ������� N.
            int curr_frogs = brute_force_method(N - i, K, frogs, jumps,P) + frogs[N];
            if (curr_frogs < min_frogs) {
                min_frogs = curr_frogs;
                jumps[N] = i;
            }
        }
    }

    return min_frogs;
}

void brute_force_method(int N, int K, vector<int>& frogs) {
    vector<int> jumps(N + 1, 0); // ������ ��� �������� �������
    int P = 0;
    brute_force_method(N, K, frogs, jumps,P);

    cout << "������� ������� (����� ������ ����): ";
    int cur = N;
    while (cur > 1) {
        cout << jumps[cur] << " ";
        cur -= jumps[cur];
    }
    cout << endl;
    cout << "���������� ��������� (����� ������ ����): " << P << endl;
}

int main() {
    setlocale(0, "");
    int N, K;
    while (true) {
        cout << "������� ���������� ��������� (N) � ������������ ����� ������ (K): ";
        if (cin >> N >> K) {
            srand(time(0)); // ������������� ���������� ��������� �����
            vector<int>frogs(N + 1, 0);
            for (int i = 2; i <=N; i++) {
                frogs[i] = rand() % 2;
            }
            cout << "������������ �������: " << endl;
            cout << "�������� ";
            for (int i = 1; i <=N; i++) {
                cout << i << " ";
            }
            cout << endl;
            cout << "�������  ";
            for (int i = 1; i <=N ; i++) {
                cout<<frogs[i]<<" ";
            }
            cout << endl;
            dinamic_method(N, K,frogs);
            brute_force_method(N, K, frogs);
            return 0;
        }
        else {
            cin.clear();
            while (cin.get() != '\n') {
                cout << "������� �������, ��������� �������" << endl;

            }
        }
    }
}
