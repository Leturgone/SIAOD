#include <iostream>
#include <string>
using namespace std;
struct Node_of_btree
{
    string key;
    int data;
    Node_of_btree* left;    //��������� �� ������ �������
    Node_of_btree* right;   //��������� �� ������� �������
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
    Node_of_btree* Root;//������ ������
public:
    Bal_Bin_Tree() {                      	//�����������
        Root = nullptr;
    }
    ~Bal_Bin_Tree() {
        delete Root;   	//����������
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

            cout << (isLeft ? "|--" : "|__");//���� ������ �� ��������� ������ ���������, ���� ��� �� ������

            cout << node->key << std::endl;

            printBinTree2(prefix + (isLeft ? "|   " : "    "), node->left, true);
            printBinTree2(prefix + (isLeft ? "|   " : "    "), node->right, false);
        }
    }
    // ��������� ������� ��� ��������� ��������� � ������ y ������.
    Node_of_btree* rightRotate(Node_of_btree*& x)
    {
        //x - ������������ ������� 
        Node_of_btree* y = x->left;
        x->left = y->right;
        y->right = x;
        return y;
    }
    // ��������� ������� ��� ��������� ��������� � ������ x ����� 
    Node_of_btree* leftRotate(Node_of_btree*& x)
    {
        //x - ������������ �������
        Node_of_btree* y = x->right;
        x->right = y->left;
        y->left = x;
        return y;
    }
    Node_of_btree* splay(Node_of_btree*& root, string key, int& C) {
        if (root == nullptr || root->key == key)
            return root;
        if (key < root->key)// ���� ����� � ����� ���������
        {
            if (root->left == nullptr) {// ����� ��� � ������, �� ���������
                return root;
            }
            // Zig-Zig (�����-�����) 
            if (root->left->key > key) {
                root->left->left = splay(root->left->left, key, C);//���������� ���� �� ����� ������� ����� �����
                C = C + 1;
                root = rightRotate(root);//������ �������� ��� root->left, �����  ��� ����� ������� ������� � ������� ����� else

            }
            // Zig-Zag (�����-������) 
            else if (root->left->key < key) {
                root->left->right = splay(root->left->right, key, C);//������� ���������� ��������� ���� ��� ������ left-right

                if (root->left->right != nullptr) {
                    C = C + 1;
                    root->left = leftRotate(root->left); // ��������� ������ �������� ��� root->left
                }
            }
            if (root->left == nullptr) {
                return root;
            }
            else {
                C = C + 1;
                root = rightRotate(root);
                return root;
            }// ��������� ������ �������� ��� �����, ��� ���� �� ������ �� ���������� ��������, �.� � ������ ����� ������������ ���� �����
        }
        else {
            if (root->right == nullptr) return root;

            // Zag-Zig (������-�����)
            if (root->right->key > key) {
                root->right->left = splay(root->right->left, key, C); //���� �� ������� �������� ���������� ���� ����
                if (root->right->left != nullptr) {
                    C = C + 1;
                    root->right = rightRotate(root->right);
                }
            }
            // Zag-Zag (������-������)
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
        // �����, ������� ��������� splay ��� �����
        root = splay(root, key, c);
        // ���� ���� ��� ���� � ������, ���������� ������
        if (root->key == key) {
            return -2;
        }
        Node_of_btree* newNode = new Node_of_btree(key, num);
        // ���� ���� ������ ���������, �� ������ ������� ������ ��� ����� ����������, � ������ ���������� ��, ��� ���� � ����� � ������ ���������. ����� ������� ������ ������
        if (key < root->key) {
            newNode->right = root;
            newNode->left = root->left;;
            root->left = nullptr;
        }
        // ���� ���� ������ ���������, �� ������ ������� ������ ��� ������ ����������, � ����� ���������� ��, ��� ���� � �����. ����� ������� ������ ������
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
            return -1; // ������ ������
        }

        // ���������� ���� ������� ����� ������� � ������
        root = splay(root, key, c);

        if (root->key != key) {
            return -2; // �� ����� ����
        }

        if (root->left == nullptr) {//���� ��� ������ ���������
            Node_of_btree* newRoot = root->right;
            delete root;
            root = newRoot;
        }
        else {//���� ���������� ����� ���������
            Node_of_btree* newRoot = root->left;
            // ������� ������������ ���� � ����� ���������
            while (newRoot->right != nullptr) {
                newRoot = newRoot->right;
            }
            // ����������� ������������� ���� � �������� ����� ������ ���������
            newRoot = splay(root->left, newRoot->key, c);
            // ������ ��������� �������� ����� �������������� � ������ ����� ������ �����, ����� ���� ������� ������ ���������.
            newRoot->right = root->right;
            delete root;
            root = newRoot;
        }

        return 0;
    }
};
