//Вид бинарного дерева определен в варианте.
//Сокращенние.ИСБД - Идеально сбалансированное бинарное дерево.
//1. Реализовать операции общие для вариантов :
//1) Создать бинарное дерево, в соответствии с заданием варианта.
//2) Отобразить дерево на экране, например, алгоритмом «повернув его на
//левый бок».
//2. Реализовать операции варианта.
//3. Разработать программу, демонстрирующую выполнение всех операций
//на ваших тестах и тестах преподавателя.

//28 Дерево выражения.
//Операнды числа.
//1) Вычислить значение выражения.
//2) Вывести формулу левого поддерева
//исходного дерева.
//3) Вывести постфиксную форму выражения дерева.
#include <iostream>
#include <string>
using namespace std;
struct Node_of_tree
{
    string data;              //значение узла
    Node_of_tree* left;    //указатель на левого потомка
    Node_of_tree* right;   //указатель на правого потомка
    Node_of_tree(string data)
    {
        this->data = data;
        this->left = nullptr;
        this->right = nullptr;
    }
    Node_of_tree(string data, Node_of_tree* left, Node_of_tree* right)
    {
        this->data = data;
        this->left = left;
        this->right = right;
    }
};

class Bin_Tree{
private:
    Node_of_tree* root;//корень дерева
public:
    Bin_Tree() {                      	//Конструктор
        root = nullptr;
    }
    ~Bin_Tree() {
        delete root;   	//Деструктор
    }
    Node_of_tree* createNode(string data) {
        Node_of_tree* newNode = new Node_of_tree(data);
        if (newNode == nullptr) {
            return nullptr;
        }
        return newNode;
    }
    bool is_operator(char s) {
        if (((static_cast<int>(s) >= 40 and static_cast<int>(s) <= 47))) {
            return true;
        }
        return false;
    }
    int get_precedence(char op) {
        if (op == '*' || op == '/') {
            return 2;
        }
        else if (op == '+' || op == '-') {
            return 1;
        }
        return 0;
    }
    Node_of_tree* construct_expression_tree(string expression, int start, int end) {
        if (start > end) {
            return nullptr;
        }

        Node_of_tree* newNode = nullptr;//создаем пустой узел
        int operatorCount = 0;// Счетчик операторов
        int lowestPrecedence = 100;// Наименьший приоритет оператора
        int lowestPrecedenceIndex = -1;// Индекс оператора с наименьшим приоритетом

        for (int i = start; i <= end; i++) {//избавляемся от скобок
            //Доходим до оператора который производит действие над скобкой
            if (expression[i] == '(') {
                operatorCount++;
            }
            else if (expression[i] == ')') {
                operatorCount--;
            }
            //если нашли оператор
            else if (operatorCount == 0 && is_operator(expression[i])) {//добрались до выражения в скобках
                int currentPrecedence = get_precedence(expression[i]);//получаем приоритет
                if (currentPrecedence <= lowestPrecedence) {
                    lowestPrecedence = currentPrecedence;
                    lowestPrecedenceIndex = i;
                }
            }
        }

        if (lowestPrecedenceIndex != -1) {// если уже в скобках и нашли оператор
            string new_node_data;
            new_node_data += expression[lowestPrecedenceIndex];//получаем символ оператора и преобразуем в строку
            newNode = createNode(new_node_data);// Создание нового узла с оператором

            //Для левой и правой ветви
            newNode->left = construct_expression_tree(expression, start, lowestPrecedenceIndex - 1);
            newNode->right = construct_expression_tree(expression, lowestPrecedenceIndex + 1, end);
        }
        else {
            // Если выражение находится внутри скобок
            if (expression[start] == '(' && expression[end] == ')') {
                return construct_expression_tree(expression, start + 1, end - 1);
            }
            //Если дошли до операндов(чисел)
            else {
                string operand;
                for (int i = start; i <= end; i++) {
                    operand+=expression[i];
                }
                newNode = createNode(operand);// Создание нового узла с операндом
            }
        }

        return newNode;
    }
    int evaluateExpression(Node_of_tree* node) {
        if (node == nullptr) {//если дерево пустое
            return 0;
        }
        if (node->left == nullptr && node->right == nullptr) {//если у дерева только один узел
            return stoi(node->data);
        }
        int leftValue = evaluateExpression(node->left);//рекурсивно считаем по правой ветке
        int rightValue = evaluateExpression(node->right);//рекурсивно считаем по левой ветке
        if (node->data == "+" ) {
            return leftValue + rightValue;
        }
        else if (node->data == "-") {
            return leftValue - rightValue;
        }
        else if (node->data == "*") {
            return leftValue * rightValue;
        }
        else {
            return leftValue / rightValue;
        }
    }

    void print_postfix_form(Node_of_tree* node) {
        if (node == nullptr) {
            return;
        }
        print_postfix_form(node->left);
        print_postfix_form(node->right);
        cout << node->data << " ";
    }
    //void printBinTree(Node_of_tree* node, int level) {
    //    int i;
    //    if (node) {
    //        printBinTree(node->right, level + 1);
    //        for (i = 1; i <= level * 3; i++) {
    //            cout << ' ';
    //        }
    //        cout << node->data << endl;
    //        printBinTree(node->left, level + 1);
    //    }
    //}
    string print_left_subtree(Node_of_tree* root) {
        if (root == nullptr) {
            return "";
        }
        string left_subtree = print_left_subtree(root->left);
        string right_subtree = print_left_subtree(root->right);
        string expression = "";
        expression += "(";
        if (left_subtree != "") {

            expression += left_subtree;
        }
        expression += root->data;
        if (right_subtree != "") {
            expression += right_subtree;
        }
        expression += ")";
        return expression;
    }
    void printBinTree2(const string& prefix, const Node_of_tree* node, bool isLeft) {
        if (node != nullptr)
        {
            cout << prefix;

            cout << (isLeft ? "|--" : "|__");//если правое то выводится первое выражение, если нет то второе

            cout << node->data << std::endl;

            printBinTree2(prefix + (isLeft ? "|   " : "    "), node->left, true);
            printBinTree2(prefix + (isLeft ? "|   " : "    "), node->right, false);
        }
    }
};
bool chek_expression(string s) {
    for (int i = 0; i <s.size(); i++) {
        if (!((static_cast<int>(s[i]) >= 40 and static_cast<int>(s[i]) <= 47) or (static_cast<int>(s[i]) >= 48 and static_cast<int>(s[i]) <= 57))) {
            return false;
        }
    }
    return true;
}

int main() {
    string expression;
    setlocale(0, "");
    while (true) {
        cout << "Введите выражение:" << endl;
        cin >> expression;
        if (chek_expression(expression)) {
            int n;
            Bin_Tree tree;
            Node_of_tree* root = tree.construct_expression_tree(expression, 0, expression.length() - 1);
            //tree.printBinTree(root,0);
            cout << "-----Бинарное дерево выражений-----" << endl;
            //tree.print_tree(root, 0);
            tree.printBinTree2("", root, false);
            cout << "------------------------------------" << endl;
            cout << "1) Вычислить значение выражения."<<endl;
            cout << "2) Вывести формулу левого поддерева исходного дерева."<<endl;
            cout << "3) Вывести постфиксную форму выражения дерева."<<endl;
            cout << "4) Выйти из программы" << endl;
            while (true) {
                cout << "Выберите функцию: " << endl;
                if (cin >> n) {
                    if (n == 1) {
                        cout << "Результат вычисления выражения: " << tree.evaluateExpression(root);
                    }
                    else if (n == 2) {
                        cout<<tree.print_left_subtree(root->left);
                    }
                    else if (n == 3) {
                        cout << "Постфиксная форма выражения: ";
                        tree.print_postfix_form(root);
                    }
                    if (n == 4) {
                        cout << "Выполнен выход из программы" << endl;
                        return 0;

                    }
                    cout << endl;
                }
                else {
                    cin.clear();
                    if (cin.get() == '\n') {
                        cout << "Введено неверно, повторите попытку" << endl;
                    }
                }
            }
        }
        else {
            cin.clear();
            if (cin.get() == '\n') {
                cout << "Введено неверно, повторите попытку" << endl;
            }
        }

    }
}
