#include <iostream>
#include <string>
using namespace std;
struct Node_of_btree
{
    string key;
    int data;
    Node_of_btree* left;    //указатель на левого потомка
    Node_of_btree* right;   //указатель на правого потомка
    Node_of_btree(string key, int data)
    {
        this->key = key;
        this->data = data;
        this->left = nullptr;
        this->right = nullptr;
    }
    Node_of_btree(string key, int data, Node_of_btree* left, Node_of_btree* right)
    {
        this->key = key;
        this->data = data;
        this->left = left;
        this->right = right;
    }
};

class Bal_Bin_Tree {
private:
    Node_of_btree* Root;//корень дерева
public:
    Bal_Bin_Tree() {                      	//Конструктор
        Root = nullptr;
    }
    ~Bal_Bin_Tree() {
        delete Root;   	//Деструктор
    }
    Node_of_btree*& get_root() {
        return Root;
    }
    void set_root(Node_of_btree* Root) {
        this->Root = Root;
    }

    Node_of_btree* createNode(string key, int data) {
        Node_of_btree* newNode = new Node_of_btree(key, data);
        if (newNode == nullptr) {
            return nullptr;
        }
        return newNode;
    }
    void printBinTree2(const string& prefix, const Node_of_btree* node, bool isLeft) {
        if (node != nullptr)
        {
            cout << prefix;

            cout << (isLeft ? "|--" : "|__");//если правое то выводится первое выражение, если нет то второе

            cout << node->key << std::endl;

            printBinTree2(prefix + (isLeft ? "|   " : "    "), node->left, true);
            printBinTree2(prefix + (isLeft ? "|   " : "    "), node->right, false);
        }
    }
    // Служебная функция для разворота поддерева с корнем y вправо.
    Node_of_btree* rightRotate(Node_of_btree*& x)
    {
        //x - перемещаемый элемент 
        Node_of_btree* y = x->left;
        x->left = y->right;
        y->right = x;
        return y;
    }
    // Служебная функция для разворота поддерева с корнем x влево 
    Node_of_btree* leftRotate(Node_of_btree*& x)
    {
        //x - перемещаемый элемент
        Node_of_btree* y = x->right;
        x->right = y->left;
        y->left = x;
        return y;
    }
    Node_of_btree* splay(Node_of_btree*& root, string key, int& C) {
        if (root == nullptr || root->key == key)
            return root;
        if (key < root->key)// Ключ лежит в левом поддереве
        {
            if (root->left == nullptr) {// Ключа нет в дереве, мы закончили
                return root;
            }
            // Zig-Zig (Левый-левый) 
            if (root->left->key > key) {
                root->left->left = splay(root->left->left, key, C);//Рекурсивно идем до ключа который нужно найти
                C = C + 1;
                root = rightRotate(root);//первый разворот для root->left, потом  еще будет воторой поворот в ретерне после else

            }
            // Zig-Zag (Левый-правый) 
            else if (root->left->key < key) {
                root->left->right = splay(root->left->right, key, C);//Сначала рекурсивно поднимаем ключ как корень left-right

                if (root->left->right != nullptr) {
                    C = C + 1;
                    root->left = leftRotate(root->left); // Выполняем первый разворот для root->left
                }
            }
            if (root->left == nullptr) {
                return root;
            }
            else {
                C = C + 1;
                root = rightRotate(root);
                return root;
            }// Выполняем второй разворот для корня, или если не прошло по предыдущим условием, т.е в случае когда интересуемый узел левый
        }
        else {
            if (root->right == nullptr) return root;

            // Zag-Zig (Правый-левый)
            if (root->right->key > key) {
                root->right->left = splay(root->right->left, key, C); //идем до нужного элемента аналагично коду выше
                if (root->right->left != nullptr) {
                    C = C + 1;
                    root->right = rightRotate(root->right);
                }
            }
            // Zag-Zag (Правый-правый)
            else if (root->right->key < key)
            {
                root->right->right = splay(root->right->right, key, C);
                C = C + 1;
                ;
                root = leftRotate(root);
            }
            if (root->right == nullptr) {
                return root;
            }
            else {
                C = C + 1;
                root = leftRotate(root);
                return root;
            }

        }
    }

    Node_of_btree* search_key_in_balance_tree(Node_of_btree* root, string key)
    {
        int c = 0;
        Root = splay(root, key, c);
        return Root;
    }
    int insert_key_in_balance_tree(Node_of_btree*& root, string key, int num, int& c)
    {
        if (root == nullptr) {
            root = new Node_of_btree(key, num);
            return 0;
        }
        // Иначе, сначала выполняем splay для корня
        root = splay(root, key, c);
        // Если ключ уже есть в дереве, возвращаем корень
        if (root->key == key) {
            return -2;
        }
        Node_of_btree* newNode = new Node_of_btree(key, num);
        // Если ключ меньше корневого, то делаем прошлый корень его левым поддеревом, и правым поддеревом то, что было о корня в правом поддереве. Новый элемент теперь корень
        if (key < root->key) {
            newNode->right = root;
            newNode->left = root->left;;
            root->left = nullptr;
        }
        // Если ключ больше корневого, то делаем прошлый корень его правым поддеревом, и левым поддеревом то, что было у корня. Новый элемент теперь корень
        else {
            newNode->left = root;
            newNode->right = root->right;;
            root->right = nullptr;
        }

        set_root(newNode);
        return 0;
    }
    int delete_key_from_balance_tree(Node_of_btree*& root, string key) {
        int c = 0;
        if (root == nullptr) {
            return -1; // Дерево пустое
        }

        // Перемещаем узел который хотим удалить в корень
        root = splay(root, key, c);

        if (root->key != key) {
            return -2; // не нашли узел
        }

        if (root->left == nullptr) {//если нет левого поддерева
            Node_of_btree* newRoot = root->right;
            delete root;
            root = newRoot;
        }
        else {//если существует левое поддерево
            Node_of_btree* newRoot = root->left;
            // Находим максимальный узел в левом поддереве
            while (newRoot->right != nullptr) {
                newRoot = newRoot->right;
            }
            // Перемещение максимального узла в качестве корня левого поддерева
            newRoot = splay(root->left, newRoot->key, c);
            // Правое поддерево текущего корня присоединяется к правой части нового корня, после чего текущий корень удаляется.
            newRoot->right = root->right;
            delete root;
            root = newRoot;
        }

        return 0;
    }
};
