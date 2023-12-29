#include <iostream>
#include <string>
using namespace std;
struct Node_of_tree
{
    string key;
    int data;
    Node_of_tree* left;    //указатель на левого потомка
    Node_of_tree* right;   //указатель на правого потомка
    Node_of_tree(string key, int data)
    {
        this->key = key;
        this->data = data;
        this->left = nullptr;
        this->right = nullptr;
    }
    Node_of_tree(string key, int data, Node_of_tree* left, Node_of_tree* right)
    {
        this->key = key;
        this->data = data;
        this->left = left;
        this->right = right;
    }
};

class Bin_Tree {
private:
    Node_of_tree* Root;//корень дерева
public:
    Bin_Tree() {                      	//Конструктор
        Root = nullptr;
    }
    ~Bin_Tree() {
        delete Root;   	//Деструктор
    }
    Node_of_tree*& get_root() {
        return Root;
    }
    Node_of_tree* createNode(string key, int data) {
        Node_of_tree* newNode = new Node_of_tree(key, data);
        if (newNode == nullptr) {
            return nullptr;
        }
        return newNode;
    }

    Node_of_tree* search_key_in_tree(Node_of_tree* root, string key) {//поиск ключа в дереве,
        if (root == nullptr) {
            return nullptr;
        }
        else if (key < root->key) {
            root = search_key_in_tree(root->left, key);
            return root;
        }
        else if (key > root->key) {
            root = search_key_in_tree(root->right, key);
            return root;
        }
        else if (key == root->key) {
            return root;
        }
    }
    Node_of_tree* insert_node_in_tree(Node_of_tree*& root1, string key, int data) {//включение элемента в дерево
        if (root1 == nullptr) {
            root1 = createNode(key, data);
            return root1;
        }
        else {
            if (key < root1->key) {
                root1->left = insert_node_in_tree(root1->left, key, data);

            }
            else {
                if (key > root1->key) {
                    root1->right = insert_node_in_tree(root1->right, key, data);
                }
            }
        }
        return root1;
    }
    int delete_node(Node_of_tree*& node, string key) {
        Node_of_tree* temp = nullptr;
        if (node == nullptr) {
            return 1;
        }
        else {
            if (key < node->key) {
                delete_node(node->left, key);
            }
            else if (key > node->key) {
                delete_node(node->right, key);
            }
            else {//Нашли узел для удаления
                temp = node;
                if (temp->left == nullptr) {
                    node = temp->right;
                }
                else if (temp->right == nullptr) {
                    node = temp->left;
                }
                else {
                    //Если у узла есть и право и левое поддерево
                    replaceKey(temp->left, temp);
                }
            }
            delete temp;
            return 0;
        }
    }
    void replaceKey(Node_of_tree*& node, Node_of_tree*& temp) {
        if (node->right) {
            replaceKey(node->right, temp);
        }
        else {
            temp->key = node->key;
            temp = node;
            node = node->left;
        }
    }
    void printBinTree2(const string& prefix, const Node_of_tree* node, bool isLeft) {
        if (node != nullptr)
        {
            cout << prefix;

            cout << (isLeft ? "|--" : "|__");//если правое то выводится первое выражение, если нет то второе

            cout << node->key << std::endl;

            printBinTree2(prefix + (isLeft ? "|   " : "    "), node->left, true);
            printBinTree2(prefix + (isLeft ? "|   " : "    "), node->right, false);
        }
    }
};
