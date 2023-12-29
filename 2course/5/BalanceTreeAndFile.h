#include "BalanceTree.h"
#include "binfunctions.h"
int create_balance_tree_from_file(string namebf, Bal_Bin_Tree& tree) {
    fstream ibf(namebf, ios::in | ios::binary);
    if (ibf.is_open()) {
        violation_record r;
        int n = 0;
        int c = 0;
        while (ibf.read((char*)&r, sizeof(r))) {
            n++;
            if (tree.insert_key_in_balance_tree(tree.get_root(), r.car_num, n, c) == -2) {
                return -2;
            }
        }
        cout << "Среднее число поворотов  при вставке ключа : " << double(c) / double(n) << endl;
        ibf.close();
        return 0;
    }
    ibf.close();
    return 1;

}

//поиск записи в файле с использованием БДП

int search_in_file_by_balance_tree(string namebf, string key, Bal_Bin_Tree& tree) {
    fstream ibf(namebf, ios::in | ios::binary);
    if (ibf.is_open()) {
        Node_of_btree* rec = tree.search_key_in_balance_tree(tree.get_root(), key);
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

int delete_in_file_by_balance_tree(string namebf, string key, Bal_Bin_Tree& tree) {
    if (tree.delete_key_from_balance_tree(tree.get_root(), key) != 0) {
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