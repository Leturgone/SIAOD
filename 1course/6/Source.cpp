#include <iostream>
using namespace std;
//1.	Найти n - ое число Фибоначчи.
//2.	В однонаправленном списке из n элементов найти элемент с заданным значением и вернуть на него указатель.
struct Node
{
    int data;//данные 
    Node* next;//адрес следуюущего
};

struct List
{
    Node* head = NULL; //"голова" связанного списка
    void addNode(int d)//добавление в конец элемента
    {
        Node* nd = new Node; //динамически создаем новый узел
        nd->data = d;        //задаем узлу данные
        nd->next = NULL;     //новый узел в конце, поэтому NULL
        if (head == NULL)     //если создаем первый узел
            head = nd;
        else                 //если узел уже не первый
        {
            Node* current = head;
            //ищем в цикле предшествующий последнему узел
            while (current->next != NULL)
                current = current->next;
            //предшествующий указывает на последний
            current->next = nd;
        }
    }
    void printList()//метод, выводящий связанный список на экран
    {
        Node* current = head;
        if (head == NULL) {
            cout << "Список пуст " << endl;
        }
        else {
            cout << "Созданный список: " << endl;
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
        return nullptr; // Если список пустой
    }
    else if (head->data == value) {
        return head; // Если значение найдено
    }
    else {
        return FindElem(head->next, value); // Рекурсивный вызов для следующего элемента списка
    }
}
int main() {
    int a,n,x,l,m;
    List L;
    setlocale(0,"");
    cout << "Лабораторная работа №6 \"Рекурсивные алгоритмы и их реализация.\". Яснецов Фёдор " << endl;
    while (true) {
        cout << "1) Найти n-ое число Фибоначчи." << endl << "2)В однонаправленном списке из n элементов найти элемент с заданным значением и вернуть на него указатель." << endl;
        cout << "Чтобы выйти введите 3" << endl;
        cout << "Выберите номер задания " << endl;
        cin >> a;
        if (a == 1) {
            while (true) {
                cout << "Введите число n" << endl;
                cout << "Чтобы выйти введите не число" << endl;
                if (cin >> n) {
                    cout << "Результат итерационного алгоритма: " << IterFib(n) << endl << "Результат рекурсивного алгоритма: " << RecFib(n) << endl;
                }
                else {
                    break;
                }
            }
        }
        if (a == 2) {
            cout << "Введите количество элементов в списке" << endl;
            cout << "Чтобы выйти введите не число" << endl;
            while (true) {
                if (cin >> x) {
                    for (int i = 0; i < x; i++) {
                        while (true) {
                            cout << "Введите элемент №" << i + 1 << endl;
                            if (cin >> l) {
                                L.addNode(l);
                                break;
                            }
                            else {
                                cin.clear();
                                while (cin.get() != '\n') {
                                    cout << "Введено неверно, повторите попытку" << endl;
                                }
                            }
                        }
                    }
                    L.printList();
                    while (true) {
                        cout << "Введите элемент,указатель на который хотите получить" << endl;
                        cout << "Чтобы выйти введите не число" << endl;
                        if (cin >> m) {
                            Node* pointer = FindElem(L.head, m);
                            if (pointer == nullptr) {
                                cout << "Элемент не найден" << endl;
                            }
                            else {
                                cout << "Указатель на элемент : " << pointer << endl;
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
                cout << "Введено неверно, повторите попытку" << endl;
            }
        }
    }
	return 0;
}