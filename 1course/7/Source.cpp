#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;
class Queue1 {//на однонаправленном списке
private:
    struct Node {
        int data;
        Node* next;
    };
    Node* head;//указателььна первый
    Node* tail;//указатель на последний
public:
    Queue1() {
        head = nullptr;
        tail = nullptr;
    }
    ~Queue1() {
        clear();
    }
    void push(int data) {//втолкнуть элемент в очередь;
        Node* node = new Node;//новый элемент
        node->data = data;
        node->next = nullptr;
        if (head == nullptr) {//если первый
            head = node;
            tail = node;
        }
        else {
            tail->next = node;
            tail = node;//лобавляется в конец
        }
    }
    //В методе push, создается новый узел, содержащий значение переданного элемента. Если очередь пуста, то созданный узел становится началом и концом очереди, 
    //иначе он добавляется в конец, а указатель на конец очереди изменяется на этот новый узел.

    void pop() {//вытолкнуть элемент из очереди;
        if (head == nullptr) {
            return;
        }
        Node* node = head;
        head = head->next;
        delete node;
    }
    //В методе pop, удаляется узел в начале очереди и изменяется указатель на начало очереди.

    int front() {//вернуть значение элемента в вершине очереди;
        if (head == nullptr) {//вернуть значение элемента в вершине очереди;
            return 0;
        }
        return head->data;
    }

    bool empty() {//проверить, пуста ли очередь;
        if (head == nullptr) {
            return true;
        }
        else {
            return false;
        }
    }
    void clear() {//сделать очередь пустой.
        while (head != nullptr) {
            Node* node = head;
            head = head->next;
            delete node;
        }
        tail = nullptr;
    }
    void printList()//метод, выводящий связанный список на экран
    {
        Node* current = head;
        if (head == NULL) {
            cout << "Очередь пуста " << endl;
        }
        else {
            cout << "Созданная очередь: " << endl;
            while (current != NULL)
            {
                cout << current->data << endl;
                current = current->next;
            }
        }
    }
};

class Queue2 {//на массиве
private:
    int* arr; // динамический массив
    int front; // индекс первого элемента
    int last; // индекс последнего элемента
    int size; // размер очереди
public:
    Queue2(int size) {
        arr = new int[size];
        front = -1;//первый
        last = -1;//последний
        this->size = size;
    } // конструктор

    ~Queue2() {
        delete[] arr;
    } // деструктор
    void pushAr(int value) {
        if (last == size - 1) {
            cout << "Очередь полная" << endl;
        }
        else {
            if (front == -1) {
                front = 0;
            }
            last++;
            arr[last] = value;//добавление элемента в конец
        }
    } // добавление элемента в очередь
    //Если очередь полная, метод выводит сообщение об ошибке. Иначе, если очередь пуста, метод устанавливает значение front в 0, 
    //а затем увеличивает значение last и добавляет элемент в конец очереди.

    int popAr() {
        int value;
        if (isEmptyAr()) {
            cout << "Очередь пустая!" << endl;
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
    } //вытолкнуть элемент из очереди;
    int head() {
        if (isEmptyAr()) {
            cout << "Очередь пустая" << endl;
            return -1;
        }
        else {
            return front;
        }
    } // получение значения элемента в вершине очереди
    bool isEmptyAr() {
        if (front == -1 || front > last) {
            return true;
        }
        else {
            return false;
        }
    } // определение пустоты очереди
    void clearAr() {
        front = -1;
        last = -1;

    }// очистка очереди
};

void QFromKeyboard(Queue1& q) {
    int n;
    cout << "Введите количество элементов: ";
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int elem;
        cout << "Введите элемент: ";
        cin >> elem;
        q.push(elem);
    }
}
void QRandomNumbers(Queue1 &q) {
    int n;
    cout << "Введите количество элементов: ";
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

    cout << "а) ";
    for (int i = 0; i < bracketPairs.size(); i++) {
        cout << bracketPairs[i].first << " " << bracketPairs[i].second << "; ";
    }
    cout << endl;
    sort(bracketPairs.begin(), bracketPairs.end());
    cout << "б) ";
    for (int i = 0; i < bracketPairs.size(); i++) {
        cout << bracketPairs[i].first << " " << bracketPairs[i].second << "; ";
    }
    cout << endl;

}

int main() {
    setlocale(0, "");
    int n, n2,n3,elem;
    string s;
    cout << "Лабораторная работа №7 \"Применение стека и очереди при преобразовании и вычислении арифметических выражений.\". Яснецов Фёдор " << endl;
    cout << "Чтобы выйти введите любое другое значение" << endl;
    cout << "Введите номер задания (1/2): " << endl;
    while (true) {
        Queue1 q;
        cout << "Выберите задание: " << endl;
        cout << "1) Выполненить операций над очередью" << endl
            << "2) Для каждой пары соответствующих открывающей и закрывающей скобок, упорядоченно  вывести номера их позиций в тексте" << endl;
        cin >> n;
        if (n == 1) {
            while (true) {
                cout << "Выберите способ заполнения очереди" << endl << "1) Автоматически" <<endl<<"2) В ручную" << endl<<"Чтобы выйти введите любую другю цифру"<<endl;
                if (cin >> n3) {
                    if (n3 == 2) {
                        QFromKeyboard(q);
                    }
                    if (n3 == 1) {
                        QRandomNumbers(q);
                    }
                    q.printList();
                    while (true) {

                        cout << "Выберите функцию: " << endl;
                        cout << "1) Втолкнуть элемент в очередь" << endl << "2) Вытолкнуть элемент из очереди" << endl << "3) Вернуть значение элемента в вершине очереди"<<endl
                            << "4) Cделать очередь пустой" << endl << "5) Определить пуста ли очередь " << endl << "Чтобы выйти из программы введите 6" << endl;
                        if (cin >> n2) {
                            if (n2 == 1) {
                                cout << "Введите элемент: " << endl;
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
                                    cout << "Очередь пуста" << endl;
                                }
                            }
                            if (n2 == 5) {
                                if (q.empty()) {
                                    cout << "Очередь пуста" << endl;
                                }
                                else {
                                    cout<< "Очередь не пуста" << endl;
                                }
                            }
                            if (n2 == 6) {
                                break;

                            }
                        }
                        else {
                            cin.clear();
                            while (cin.get() != '\n') {
                                cout << "Введено неверно, повторите попытку" << endl;
                            }
                        }
                    }
                }
                else {
                    cin.clear();
                    while (cin.get() != '\n') {
                        cout << "Введено неверно, повторите попытку" << endl;
                    }
                }
            }
        }
        else if (n == 2) {
            string expression;
            cout << "Введите строку" << endl;
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
