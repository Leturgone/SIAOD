#include <iostream>
using namespace std;
struct Node
{
    int data;//������ 
    Node* next;//����� �����������
};

struct List
{
    Node* head=NULL; //"������" ���������� ������
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
    void insertNode(int x, int index) {//������� �������� �� �������
        if (index == 0) {
            Node *p = head;
            head = new Node;
            head->data = x;
            head->next=p;
        }
        else {
            Node* privious = this->head;
            for (int i = 0; i < index - 1; i++) {
                privious = privious->next;
            }//���������� ������� �����������
            Node* newNode = new Node;//������� ����� ����
            newNode->data = x;
            newNode->next = privious->next;//������ ���� ������ � ����� ����������� �������� �� �����������
            privious->next = newNode;//����������� ���� ����� ����� �������
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
    //������� ������
    void SortInsert(int a) {//������������� �������
        if (a<head->data){
            insertNode(a, 0);
        }
        else {
            Node* current = head;
            int i = 1;
            while (current->next != NULL) {
                current = current->next;
                if (current->data < a) {
                    i = i + 1;
                }
            }
            insertNode(a, i);
        }
    }
    void deleteIf(int val)
    {
        Node* current = head;//�������
        Node* prev = nullptr;//����������

        while (current)
        {
            if (current->data>val)
            {
                if (prev)
                {
                    prev->next = current->next;//������ ������
                }
                else
                {
                    head = current->next;//�����������
                }
                Node *tmp = current->next;//� ��������� ������������ ����� �����������
                delete current;//�������� ��������
                current = tmp;// ������������ ����� �� ����������
            }
            else// ����������� ������� �� ������
            {
                prev = current;
                current = current->next;
            }
        }
    }
};


//������� ��� �������� ����� � ��������������� ������������ ������
Node* reverseList(struct Node* node) {
    Node*head = node;//�������� �������
    Node* n = nullptr;
    Node* next = nullptr;

    while (head) {
        next = head->next;
        head->next = n;
        n = head;
        head = next;
    }
    return n;//���������� ����� �������� �������
}
Node* NewRverseList(Node* head)
{
    struct Node* current = head;// ������������ ��� �������� ��������� ������
    struct Node* newList = NULL;// ������ ������ ������
    struct Node* tail = NULL;// ��������� �� ��������� ���� � ����� ������

    while (current != NULL)
    {
        // ������ ������ ��� ������� ������ ����
        if (newList == NULL)
        {
            newList = (struct Node*)malloc(sizeof(struct Node));
            newList->data = current->data;
            newList->next = NULL;
            tail = newList;
        }
        else {
            tail->next = (struct Node*)malloc(sizeof(struct Node));
            tail = tail->next;
            tail->data = current->data;
            tail->next = NULL;
        }
        current = current->next;
    }
    return reverseList(newList);
}


int main()
{
    List L,L2;
    setlocale(0, "");
    int n,a,b,l;
	cout << "������������ ������ �5 \"���������������� ������������ ������.\". ������� Ը��� " << endl;
    cout << "����� ����� ������� �� �����" << endl;
    cout << "������� ���������� ���������: " << endl;
    if (cin >> n) {
        for (int i = 0; i < n; i++) {
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
            cout << "�������� �������: " << endl;
            cout << "1)�������� ����� �������� � ������, �������� ��������������� ������." << endl << "2)������� �� ������ ��� ����, �������� � ������� ������� ���������." << endl
                << "3)C������ ����� ������ �� �������� ����� ������, ��� ��� � ������ ���� ����������� � ������� �������� �� ��������." << endl;
            cout << "����� ����� ������� 4" << endl;
            cin >> b;
            if (b == 1) {
                while (true) {
                    cout << "������� ��������"<< endl;
                    if (cin >> a) {
                        L.SortInsert(a);
                        L.printList();
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
            else if(b==2){
                while (true) {
                    cout << "������� ��������" << endl;
                    if (cin >> a) {
                        L.deleteIf(a);
                        L.printList();
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
            else if(b==3){
                L2.head = NewRverseList(L.head);
                L2.printList();
            }
            else if (b == 4) {
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
    return 0;
}