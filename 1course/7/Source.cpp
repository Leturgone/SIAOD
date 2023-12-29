#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;
class Queue1 {//�� ���������������� ������
private:
    struct Node {
        int data;
        Node* next;
    };
    Node* head;//������������ ������
    Node* tail;//��������� �� ���������
public:
    Queue1() {
        head = nullptr;
        tail = nullptr;
    }
    ~Queue1() {
        clear();
    }
    void push(int data) {//��������� ������� � �������;
        Node* node = new Node;//����� �������
        node->data = data;
        node->next = nullptr;
        if (head == nullptr) {//���� ������
            head = node;
            tail = node;
        }
        else {
            tail->next = node;
            tail = node;//����������� � �����
        }
    }
    //� ������ push, ��������� ����� ����, ���������� �������� ����������� ��������. ���� ������� �����, �� ��������� ���� ���������� ������� � ������ �������, 
    //����� �� ����������� � �����, � ��������� �� ����� ������� ���������� �� ���� ����� ����.

    void pop() {//���������� ������� �� �������;
        if (head == nullptr) {
            return;
        }
        Node* node = head;
        head = head->next;
        delete node;
    }
    //� ������ pop, ��������� ���� � ������ ������� � ���������� ��������� �� ������ �������.

    int front() {//������� �������� �������� � ������� �������;
        if (head == nullptr) {//������� �������� �������� � ������� �������;
            return 0;
        }
        return head->data;
    }

    bool empty() {//���������, ����� �� �������;
        if (head == nullptr) {
            return true;
        }
        else {
            return false;
        }
    }
    void clear() {//������� ������� ������.
        while (head != nullptr) {
            Node* node = head;
            head = head->next;
            delete node;
        }
        tail = nullptr;
    }
    void printList()//�����, ��������� ��������� ������ �� �����
    {
        Node* current = head;
        if (head == NULL) {
            cout << "������� ����� " << endl;
        }
        else {
            cout << "��������� �������: " << endl;
            while (current != NULL)
            {
                cout << current->data << endl;
                current = current->next;
            }
        }
    }
};

class Queue2 {//�� �������
private:
    int* arr; // ������������ ������
    int front; // ������ ������� ��������
    int last; // ������ ���������� ��������
    int size; // ������ �������
public:
    Queue2(int size) {
        arr = new int[size];
        front = -1;//������
        last = -1;//���������
        this->size = size;
    } // �����������

    ~Queue2() {
        delete[] arr;
    } // ����������
    void pushAr(int value) {
        if (last == size - 1) {
            cout << "������� ������" << endl;
        }
        else {
            if (front == -1) {
                front = 0;
            }
            last++;
            arr[last] = value;//���������� �������� � �����
        }
    } // ���������� �������� � �������
    //���� ������� ������, ����� ������� ��������� �� ������. �����, ���� ������� �����, ����� ������������� �������� front � 0, 
    //� ����� ����������� �������� last � ��������� ������� � ����� �������.

    int popAr() {
        int value;
        if (isEmptyAr()) {
            cout << "������� ������!" << endl;
            return -1;
        }
        else {
            value = front;
            if (front == last) {
                front = -1;
                last = -1;
            }
            else {
                front++;
            }
            return value;
        }
    } //���������� ������� �� �������;
    int head() {
        if (isEmptyAr()) {
            cout << "������� ������" << endl;
            return -1;
        }
        else {
            return front;
        }
    } // ��������� �������� �������� � ������� �������
    bool isEmptyAr() {
        if (front == -1 || front > last) {
            return true;
        }
        else {
            return false;
        }
    } // ����������� ������� �������
    void clearAr() {
        front = -1;
        last = -1;

    }// ������� �������
};

void QFromKeyboard(Queue1& q) {
    int n;
    cout << "������� ���������� ���������: ";
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int elem;
        cout << "������� �������: ";
        cin >> elem;
        q.push(elem);
    }
}
void QRandomNumbers(Queue1 &q) {
    int n;
    cout << "������� ���������� ���������: ";
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int elem = rand() % 100;
        q.push(elem);
    }
}

void printMatchingPairs(string expression) {
    setlocale(0, "");
    stack<int> openBrackets;
    vector<pair<int, int>> bracketPairs;

    for (int i = 0; i < expression.length(); i++) {
        if (expression[i] == '(') {
            openBrackets.push(i + 1);
        }
        else if (expression[i] == ')') {
            if (!openBrackets.empty()) {
                int openBracketPos = openBrackets.top();
                openBrackets.pop();
                bracketPairs.push_back(make_pair(openBracketPos, i + 1));
            }
        }
    }

    sort(bracketPairs.begin(), bracketPairs.end(), [](const auto& x, const auto& y) { return x.second < y.second; });

    cout << "�) ";
    for (int i = 0; i < bracketPairs.size(); i++) {
        cout << bracketPairs[i].first << " " << bracketPairs[i].second << "; ";
    }
    cout << endl;
    sort(bracketPairs.begin(), bracketPairs.end());
    cout << "�) ";
    for (int i = 0; i < bracketPairs.size(); i++) {
        cout << bracketPairs[i].first << " " << bracketPairs[i].second << "; ";
    }
    cout << endl;

}

int main() {
    setlocale(0, "");
    int n, n2,n3,elem;
    string s;
    cout << "������������ ������ �7 \"���������� ����� � ������� ��� �������������� � ���������� �������������� ���������.\". ������� Ը��� " << endl;
    cout << "����� ����� ������� ����� ������ ��������" << endl;
    cout << "������� ����� ������� (1/2): " << endl;
    while (true) {
        Queue1 q;
        cout << "�������� �������: " << endl;
        cout << "1) ����������� �������� ��� ��������" << endl
            << "2) ��� ������ ���� ��������������� ����������� � ����������� ������, ������������  ������� ������ �� ������� � ������" << endl;
        cin >> n;
        if (n == 1) {
            while (true) {
                cout << "�������� ������ ���������� �������" << endl << "1) �������������" <<endl<<"2) � ������" << endl<<"����� ����� ������� ����� ����� �����"<<endl;
                if (cin >> n3) {
                    if (n3 == 2) {
                        QFromKeyboard(q);
                    }
                    if (n3 == 1) {
                        QRandomNumbers(q);
                    }
                    q.printList();
                    while (true) {

                        cout << "�������� �������: " << endl;
                        cout << "1) ��������� ������� � �������" << endl << "2) ���������� ������� �� �������" << endl << "3) ������� �������� �������� � ������� �������"<<endl
                            << "4) C������ ������� ������" << endl << "5) ���������� ����� �� ������� " << endl << "����� ����� �� ��������� ������� 6" << endl;
                        if (cin >> n2) {
                            if (n2 == 1) {
                                cout << "������� �������: " << endl;
                                cin >> elem;
                                q.push(elem);
                                q.printList();
                            }
                            if (n2 == 2) {
                                q.pop();
                                q.printList();
                            }
                            if (n2 == 3) {
                                cout << q.front() << endl;
                            }
                            if (n2 == 4) {
                                q.clear();
                                if (q.empty()) {
                                    cout << "������� �����" << endl;
                                }
                            }
                            if (n2 == 5) {
                                if (q.empty()) {
                                    cout << "������� �����" << endl;
                                }
                                else {
                                    cout<< "������� �� �����" << endl;
                                }
                            }
                            if (n2 == 6) {
                                break;

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
                else {
                    cin.clear();
                    while (cin.get() != '\n') {
                        cout << "������� �������, ��������� �������" << endl;
                    }
                }
            }
        }
        else if (n == 2) {
            string expression;
            cout << "������� ������" << endl;
            cin >> expression;
            printMatchingPairs(expression);
            cout << endl;
        }
        else {
            break;
        }
    }
    return 0;
}
