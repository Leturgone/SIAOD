#include <iostream>
#include <string>
#include "SearchTree.h"
#include "binfunctions.h"
using namespace std;

int create_tree_from_file(string namebf, Bin_Tree& tree) {
    fstream ibf(namebf, ios::in | ios::binary);
    if (ibf.is_open()) {
        violation_record r;
        int n = 0;
        while (!ibf.eof()) {
            ibf.read((char*)&r, sizeof(r));
            n++;
            tree.insert_node_in_tree(tree.get_root(), r.car_num, n);
        }
        ibf.close();
        return 0;
    }
    ibf.close();
    return 1;

}

//поиск записи в файле с использованием БДП

int search_in_file_by_tree(string namebf, string key, Bin_Tree& tree) {
    fstream ibf(namebf, ios::in | ios::binary);
    if (ibf.is_open()) {
        Node_of_tree* rec = tree.search_key_in_tree(tree.get_root(), key);
        if (rec != nullptr) {
            get_access_to_rec(namebf, rec->data - 1);
            ibf.close();
            return 0;
        }
        else {
            ibf.close();
            return 1;
        }
    }
    ibf.close();
    return 1;

}

int delete_in_file_by_tree(string namebf, string key, Bin_Tree& tree) {
    if (tree.delete_node(tree.get_root(), key) != 0) {
        return -2;
    }
    char charkey[10];
    key.copy(charkey, 10);
    charkey[6] = '\0';
    if (delete_rec_by_key(namebf, charkey) != 0) {
        return -1;
    }
    return 0;
}
