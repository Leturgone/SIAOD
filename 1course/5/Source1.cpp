#include <iostream>
using namespace std;
struct Node
{
    int data;//данные 
    Node* next;//адрес следуюущего
};

struct List
{
    Node* head=NULL; //"голова" связанного списка
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
    void insertNode(int x, int index) {//вставка элемента по индексу
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
            }//нахождение индекса предыдущего
            Node* newNode = new Node;//создаем новый узел
            newNode->data = x;
            newNode->next = privious->next;//задаем узлу данные и адрес следуюущего элемента из предыдущего
            privious->next = newNode;//предыдущему даем адрес новго объекта
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
    //Функции задачи
    void SortInsert(int a) {//упорядоченная вставка
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
        Node* current = head;//текущий
        Node* prev = nullptr;//предыдущий

        while (current)
        {
            if (current->data>val)
            {
                if (prev)
                {
                    prev->next = current->next;//замена адреса
                }
                else
                {
                    head = current->next;//продолжение
                }
                Node *tmp = current->next;//в временный записывается адрес следуюущего
                delete current;//удаление элемента
                current = tmp;// приваивается адрес на оставшийся
            }
            else// продолжение прохода по списку
            {
                prev = current;
                current = current->next;
            }
        }
    }
};


//Функции для создания копии и переворачивания односвязного списка
Node* reverseList(struct Node* node) {
    Node*head = node;//Головной элемент
    Node* n = nullptr;
    Node* next = nullptr;

    while (head) {
        next = head->next;
        head->next = n;
        n = head;
        head = next;
    }
    return n;//возвращаем новый головной элемент
}
Node* NewRverseList(Node* head)
{
    struct Node* current = head;// используется для перебора исходного списка
    struct Node* newList = NULL;// начало нового списка
    struct Node* tail = NULL;// указываем на последний узел в новом списке

    while (current != NULL)
    {
        // особый случай для первого нового узла
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
	cout << "Лабораторная работа №5 \"Однонаправленный динамический список.\". Яснецов Фёдор " << endl;
    cout << "Чтобы выйти введите не цифру" << endl;
    cout << "Введите количество элементов: " << endl;
    if (cin >> n) {
        for (int i = 0; i < n; i++) {
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
            cout << "Выберите функцию: " << endl;
            cout << "1)Вставить новое значение в список, сохраняя упорядоченность списка." << endl << "2)Удаляет из списка все узлы, значения в которых большие заданного." << endl
                << "3)Cоздать новый список из значений узлов списка, так что в списке узлы упорядочены в порядке убывания их значений." << endl;
            cout << "Чтобы выйти введите 4" << endl;
            cin >> b;
            if (b == 1) {
                while (true) {
                    cout << "Введите значение"<< endl;
                    if (cin >> a) {
                        L.SortInsert(a);
                        L.printList();
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
            else if(b==2){
                while (true) {
                    cout << "Введите значение" << endl;
                    if (cin >> a) {
                        L.deleteIf(a);
                        L.printList();
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
                    cout << "Введено неверно, повторите попытку" << endl;
                }
            }
        }
        
    }
    return 0;
}