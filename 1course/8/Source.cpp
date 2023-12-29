//������� 8 
//�������� ������� ����������	�������� ������������������� ����������     	�������� �������
//�������� ������	            ��������� ����������	                            ������� �������
//���������� �������� ��������� � � ���������� �������� ����������� �. 
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
using namespace std;

//������������ ����
void formKucha(int* numbers, int root, int bottom, long long int& C, long long int& M)
{
    int maxChild; // ������ ������������� �������
    int done = 0; // ���� ����, ��� ���� ������������
    // ���� �� ����� �� ���������� ����
    while ((root * 2 <= bottom) && (!done))
    {
        if (root * 2 == bottom) {   // ���� �� � ��������� ����,
            C++;
            maxChild = root * 2;
        }// ���������� ����� �������
        // ����� ���������� ������� ������� �� ����
        else if (numbers[root * 2] > numbers[root * 2 + 1]) {
            C++;
            maxChild = root * 2;
        }
        else {
            maxChild = root * 2 + 1;
        }
        // ���� ������� ������� ������ ������������� �������
        if (numbers[root] < numbers[maxChild])
        {
            C++;
            M++;
            int temp = numbers[root]; // ������ �� �������
            numbers[root] = numbers[maxChild];
            numbers[maxChild] = temp;
            root = maxChild;
        }
        else // �����
            done = 1; // ��������� ����� ������������
    }
}
// ������� ���������� �� ����
void TurSort(int* arr, long long int n, long long int& C, long long int& M)
{
    // ��������� ������ ��� ��������
    for (int i = (n / 2); i >= 0; i--)
        formKucha(arr, i, n - 1, C,M);
    // ���������� ����� �������� ��������� ��������
    for (int i = n - 1; i >= 1; i--)
    {
        M++;
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        formKucha(arr, 0, i - 1, C,M);
    }
}

void simple_selection_sort(int* arr, long long int n, long long int& C, long long int& M) {
    int min, temp; // ��� ������ ������������ �������� � ��� ������
    for (int i = 0; i < n - 1; i++)
    {
        min = i; // ���������� ������ �������� ��������
        // ���� ����������� ������� ����� ��������� �� ����� i-���
        for (int j = i + 1; j < n; j++)  // ��� ��������� ��������� ����� i-���
        {
            C++;
            if (arr[j] < arr[min]) // ���� ������� ������ ������������,
                min = j;       // ���������� ��� ������ � min
        }
        M++;
        temp = arr[i];      // ������ ������� i-�� � ����������� ��������
        arr[i] = arr[min];
        arr[min] = temp;
    }
}
void merge_sort(int* arr, long long int n, long long int& C, long long int& M) {
    int mid = n / 2; // ������� �������� ����������� ������������������
    if (n % 2 == 1)
        mid++;
    int h = 1; // ���
    // �������� ������ ��� ����������� ������������������
    int* c = (int*)malloc(n * sizeof(int));
    int step;
    while (h < n)
    {
        step = h;
        int i = 0;   // ������ ������� ����
        int j = mid; // ������ ������� ����
        int k = 0;   // ������ �������� � �������������� ������������������
        while (step <= mid)
        {
            while ((i < step) && (j < n) && (j < (mid + step)))
            { // ���� �� ����� �� ����� ����
              // ��������� ��������� ������� ����������� ������������������
              // ������� �� ���� ���������������
                C++;
                if (arr[i] < arr[j])
                {
                    M++;
                    c[k] = arr[i];
                    i++; k++;
                }
                else {
                    M++;
                    c[k] = arr[j];
                    j++; k++;
                }
            }
            while (i < step)
            { // ������������ ���������� �������� ������� ���� (���� ������ �������� ������)
                M++;
                c[k] = arr[i];
                i++; k++;
            }
            while ((j < (mid + step)) && (j < n))
            {  // ������������ ���������� �������� ������� ���� (���� ������ �������� ������)
                M++;
                c[k] = arr[j];
                j++; k++;
            }
            step = step + h; // ��������� � ���������� �����
        }
        h = h * 2;
        // ��������� ������������� ������������������ (������������� �������) � �������� ������
        for (i = 0; i < n; i++)
            M++;
            arr[i] = c[i];
    }
}
void reversesort(int *arr, long long int n) {
    for (int i = 0; i < n/2; i++) {
        int temp = arr[i];

        arr[i] = arr[n - 1 - i];

        arr[n- 1 - i] = temp;
    }
}
void fillMas(int* arr, long long int N) {
    for (long long int i = 0; i < N; i++)
        arr[i] = rand() % 100000000;
}
void copyMas(int* arr, long long int N, int* mas2) {
    for (int i = 0; i < N; i++) {
        mas2[i] = arr[i];
    }
}
void printMas(int* arr, long long int N) {
    for (int i = 0; i < N; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main(){
    int a,b,c;
    setlocale(0, "");
    cout << "������������ ������ �8 \"����������� ��������� ����������.\". ������� Ը��� " << endl;
    while (true) {
        cout << "����� ����� ������� �� �����" << endl;
        cout << "������ �������� � �������� ����������: " << endl;
        if (cin >> a >> b>>c) {
            for (long long int N = a; N <= b; N += c) {
                cout << "______________________________________________" << endl;
                cout <<"���������� ��������� " << N << endl;
                int* mas1 = new int[N], * mas2 = new int[N], * mas3 = new int[N];
                fillMas(mas1, N);
                copyMas(mas1, N, mas2);
                copyMas(mas1, N, mas3);
                //printMas(mas1, N);
                long long int C1 = 0, M1 = 0, C2 = 0, M2 = 0, C3 = 0, M3 = 0;

                //avg
                auto start = std::chrono::steady_clock::now();
                simple_selection_sort(mas1, N, C1, M1);
                auto end = std::chrono::steady_clock::now();
                std::chrono::duration<double> elapsed_seconds1 = end - start;//�����������������

                start = std::chrono::steady_clock::now();
                TurSort(mas2, N, C2, M2);
                end = std::chrono::steady_clock::now();
                std::chrono::duration<double> elapsed_seconds2 = end - start;

                start = std::chrono::steady_clock::now();
                merge_sort(mas3, N, C3, M3);
                end = chrono::steady_clock::now();
                chrono::duration<double> elapsed_seconds3 = end - start;
                //printMas(mas3, N);
                cout << "����������� �������� ������: �������� ������  C= " << C1 << "\t M= " << M1 << "\tt=" << elapsed_seconds1.count() << endl;
                cout << "����������� �������� ������: ���. ����������  C= " << C2 << "\t M=" << M2 << "\tt=" << elapsed_seconds2.count() << endl;
                cout << "����������� �������� ������: ������� �������  C= " << C3 << "\t M= " << M3 << "\tt=" << elapsed_seconds3.count() << endl;

                //�
                C1 = 0;
                C2 = 0; 
                C3 = 0; 
                M1 = 0; 
                M2 = 0; 
                M3 = 0;
                start = std::chrono::steady_clock::now();
                simple_selection_sort(mas1, N, C1, M1);
                end = std::chrono::steady_clock::now();
                elapsed_seconds1 = end - start;

                start = std::chrono::steady_clock::now();
                TurSort(mas2, N, C2, M2);
                end = std::chrono::steady_clock::now();
                elapsed_seconds2 = end - start;

                start = std::chrono::steady_clock::now();
                merge_sort(mas3, N, C3, M3);
                end = std::chrono::steady_clock::now();
                elapsed_seconds3 = end - start;
                cout << "......................................" << endl;
                cout << "��������������� ������: �������� ������  C= " << C1 << "\t M= " << M1 << "\tt=" << elapsed_seconds1.count() << endl;
                cout << "��������������� ������: ���. ����������  C= " << C2 << "\t M= " << M2 << "\tt=" << elapsed_seconds2.count() << endl;
                cout << "��������������� ������: ������� �������  C= " << C3 <<"\t M = " << M3 << "\tt = " << elapsed_seconds3.count() << endl;


                //������ ������, ����� ������ ����������
                C1 = 0;
                C2 = 0;
                C3 = 0;
                M1 = 0;
                M2 = 0;
                M3 = 0;
                reversesort(mas1, N);
                reversesort(mas2, N);
                reversesort(mas3, N);

                start = std::chrono::steady_clock::now();
                simple_selection_sort(mas1, N, C1, M1);
                end = std::chrono::steady_clock::now();
                elapsed_seconds1 = end - start;

                start = std::chrono::steady_clock::now();
                TurSort(mas2, N, C2, M2);
                end = std::chrono::steady_clock::now();
                elapsed_seconds2 = end - start;

                start = std::chrono::steady_clock::now();
                merge_sort(mas3, N, C3, M3);
                end = std::chrono::steady_clock::now();
                elapsed_seconds3 = end - start;
                cout << "......................................" << endl;
                cout << "��������������� � ���. ������� ������: �������� ������  C= " << C1 << "\t M= " << M1 << "\tt=" << elapsed_seconds1.count() << endl;
                cout << "��������������� � ���. ������� ������: ���. ����������  C= " << C2 << "\t M= " << M2 << "\tt=" << elapsed_seconds2.count() << endl;
                cout << "��������������� � ���. ������� ������: ������� �������  C= " << C3 << "\t M= " << M3 << "\tt=" << elapsed_seconds3.count() << endl;
            }
        }
        else {
            break;
        }
    }
    return 0;
}