#include <iostream>
using namespace std;
//1.	����� n - �� ����� ���������.
//2.	� ���������������� ������ �� n ��������� ����� ������� � �������� ��������� � ������� �� ���� ���������.
struct Node
{
    int data;//������ 
    Node* next;//����� �����������
};

struct List
{
    Node* head = NULL; //"������" ���������� ������
    void addNode(int d)//���������� � ����� ��������
    {
        Node* nd = new Node; //����������� ������� ����� ����
        nd->data = d;        //������ ���� ������
        nd->next = NULL;     //����� ���� � �����, ������� NULL
        if (head == NULL)     //���� ������� ������ ����
            head = nd;
        else                 //���� ���� ��� �� ������
        {
            Node* current = head;
            //���� � ����� �������������� ���������� ����
            while (current->next != NULL)
                current = current->next;
            //�������������� ��������� �� ���������
            current->next = nd;
        }
    }
    void printList()//�����, ��������� ��������� ������ �� �����
    {
        Node* current = head;
        if (head == NULL) {
            cout << "������ ���� " << endl;
        }
        else {
            cout << "��������� ������: " << endl;
            while (current != NULL)
            {
                cout << current->data << endl;
                current = current->next;
            }
        }
    }
};

int IterFib(int n){
    int a = 0;
    int b = 1;
    int c;
    if (n == 0) {
        return a;
    }
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}
int RecFib(int n){
    if (n <= 1) {
        return n;
    }
    return RecFib(n - 1) + RecFib(n - 2);
}
Node* FindElem(Node* head, int value) {
    if (head == nullptr) {
        return nullptr; // ���� ������ ������
    }
    else if (head->data == value) {
        return head; // ���� �������� �������
    }
    else {
        return FindElem(head->next, value); // ����������� ����� ��� ���������� �������� ������
    }
}
int main() {
    int a,n,x,l,m;
    List L;
    setlocale(0,"");
    cout << "������������ ������ �6 \"����������� ��������� � �� ����������.\". ������� Ը��� " << endl;
    while (true) {
        cout << "1) ����� n-�� ����� ���������." << endl << "2)� ���������������� ������ �� n ��������� ����� ������� � �������� ��������� � ������� �� ���� ���������." << endl;
        cout << "����� ����� ������� 3" << endl;
        cout << "�������� ����� ������� " << endl;
        cin >> a;
        if (a == 1) {
            while (true) {
                cout << "������� ����� n" << endl;
                cout << "����� ����� ������� �� �����" << endl;
                if (cin >> n) {
                    cout << "��������� ������������� ���������: " << IterFib(n) << endl << "��������� ������������ ���������: " << RecFib(n) << endl;
                }
                else {
                    break;
                }
            }
        }
        if (a == 2) {
            cout << "������� ���������� ��������� � ������" << endl;
            cout << "����� ����� ������� �� �����" << endl;
            while (true) {
                if (cin >> x) {
                    for (int i = 0; i < x; i++) {
                        while (true) {
                            cout << "������� ������� �" << i + 1 << endl;
                            if (cin >> l) {
                                L.addNode(l);
                                break;
                            }
                            else {
                                cin.clear();
                                while (cin.get() != '\n') {
                                    cout << "������� �������, ��������� �������" << endl;
                                }
                            }
                        }
                    }
                    L.printList();
                    while (true) {
                        cout << "������� �������,��������� �� ������� ������ ��������" << endl;
                        cout << "����� ����� ������� �� �����" << endl;
                        if (cin >> m) {
                            Node* pointer = FindElem(L.head, m);
                            if (pointer == nullptr) {
                                cout << "������� �� ������" << endl;
                            }
                            else {
                                cout << "��������� �� ������� : " << pointer << endl;
                            }
                        }
                        else {
                            break;
                        }
                    }
                }
                else {
                    break;
                }
            }
        }
        if (a == 3) {
            break;
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