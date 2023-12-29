#include <iostream>
#include <string>
#include <chrono>
#include "hashtabfuctions.h"
#include "SearchTree.h"
#include "BalanceTree.h"
#include "binfunctions.h"
using namespace std;

//1) Прочитать запись из файла и вставить элемент в таблицу(элемент
//включает : ключ и номер записи с этим ключом в файле, и для метода с
//открытой адресацией возможны дополнительные поля).
//2) Удалить запись из таблицы при заданном значении ключа и соответственно из файла.
//3) Найти запись в файле по значению ключа(найти ключ в хеш - таблице,
//получить номер записи с этим ключом в файле, выполнить прямой доступ
//к записи по ее номеру).
//

int insert_rec_from_file(string& namebf, Hash_Table& table) {
    int numRecord = 0;
    fstream ibf(namebf, ios::in | ios::out | ios::binary);
    if (!ibf) {
        return -1;
    }
    violation_record r;
    while ((ibf.read(reinterpret_cast<char*>(&r), sizeof(violation_record)))) {
        if (table.search_el(r.car_num) == -1) {
            table.insert_el(r.car_num, numRecord);
            numRecord++;
        }
        else {
            return -1;
        }
    }
    ibf.close();
    return 0;
}
int delete_rec_from_file(char key[], string namebf, Hash_Table& table) {
    if (table.search_el(key) != -1) {
        int z = delete_rec_by_key(namebf, key);
        return table.delete_el(key);
    }
    else {
        return -1;
    }
}

int find_rec_by_key_hash(char key[], string namebf, Hash_Table& table) {
    int key_num = table.search_el(key);//получаем номер записи
    if (key_num != -1) {
        return get_access_to_rec(namebf, key_num);//получаем доступ к записи по его номеру

    }
    else {
        return -1;
    }
}
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

int main() {
    setlocale(0, "");
    Hash_Table table(150);
    string tfile_name;
    string bfile_name = "bf.dat";
    cout << "Введите имя файла: " << endl;
    cin >> tfile_name;
    cout << "---Меню работы с бинарным файлом ---" << endl;
    cout << "1. Создать двоичный файл" << endl << "2. Вывод всех записей двоичного файла" << endl << "---Функции работы с файлом при помощи хэш таблицы---" << endl << "3. Прочитать записи из файла и вставить элементы в таблицу" << endl <<  "4.  Найти запись в файле по значению ключа" << endl << "6. Вывести элементы хэш таблицы" << endl << "---Функции работы с файлом при помощи дерева поиска---" << endl<< "7. Создать двоичный файл и сформировать дерево поиска" << endl << "8.Вывод дерева" << endl << "9.Найти запись по ключу используя дерево поиска" << endl<<"---Функции работы с файлом при помощи косого дерева поиска---" << endl << "10. Создать двоичный файл и сформировать дерево поиска" << endl << "11. Вывод дерева" << endl << "12. Найти запись по ключу используя дерево поиска" << endl << "13. Выйти из программы" << endl;
    Bin_Tree tree;
    Bal_Bin_Tree tree1;
    while (true) {
        int n;
        cout << "Выберите номер операции: ";
        if (cin >> n) {
            if (n == 1) {//создание файла
                if (create_bin_file(tfile_name, bfile_name) == 0) {
                    cout << "Файл успешно создан";
                }
                else {
                    cout << "Ошибка при создании файла";
                }
                cout << endl;
            }
            else if (n == 2) {
                if (print_bin_file(bfile_name) == 1) {
                    cout << "Не удалось открыть файл";
                }
                cout << endl;
            }
            else if (n == 3) {
                int z = insert_rec_from_file(bfile_name, table);
                if (z == 0) {
                    cout << "Хэш таблица сформирована" << endl;
                }
                else {
                    cout << "Ключи из файла уже записаны в хэш таблицу" << endl;
                }
            }
            else if (n == 4) {
                char num[10];
                cout << "Введите ключ записи ( номер автомобиля) , которую хотите найти в файле:" << endl;
                cin >> num;
                int z;
                auto start = std::chrono::steady_clock::now();
                z = find_rec_by_key_hash(num, bfile_name, table);
                auto end = std::chrono::steady_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                cout << "Время доступа " << duration << " мс" << endl;
                // Вычисляем время доступа в миллисекундах

                if (z == -1) {
                    cout << "В хэш таблице нет записи с таким ключом" << endl;
                }
                else if (z != 0) {
                    cout << "Ошибка при получении доступа" << endl;
                }
            }
            else if (n == 6) {
                table.print();
            }
            else if (n == 7) {//создание файла
                if (create_bin_file(tfile_name, bfile_name) == 0) {
                    cout << "Файл успешно создан" << endl;
                    if (create_tree_from_file(bfile_name, tree) == 0) {
                        cout << "Дерево поиска успешно создано";
                    }
                    else {
                        cout << "Ошибка при создании дерева поиска";
                    }
                }
                else {
                    cout << "Ошибка при создании файла";
                }
                cout << endl;
            }
            else if (n == 8) {//Вывод дерева
                tree.printBinTree2("", tree.get_root(), false);

            }
            else if (n == 9) {
                string key;
                cout << "Введите ключ записи, доступ к которой хотите получить: ";
                if (cin >> key) {
                    auto start = std::chrono::steady_clock::now();
                    int z = search_in_file_by_tree(bfile_name, key, tree);
                    auto end = std::chrono::steady_clock::now();
                    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                    cout << "Время доступа " << duration << " мс" << endl;
                    // Вычисляем время доступа в миллисекундах
                    if (z == 1) {
                        cout << "Ошибка при чтении записи с ключом " << key << endl;
                    }
                    else if (z == 2) {
                        cout << "Не удалось открыть файл" << endl;
                    }
                    else if (z == -3) {
                        cout << "Файл пустой" << endl;
                    }
                }
                else {
                    cin.clear();
                    while (cin.get() != '\n') {
                        cout << "Введено неверно, повторите попытку" << endl;

                    }
                }
            }
            else if (n == 10) {//создание файла
                if (create_bin_file(tfile_name, bfile_name) == 0) {
                    cout << "Файл успешно создан" << endl;
                    if (create_balance_tree_from_file(bfile_name, tree1) == 0) {
                        cout << "Дерево поиска успешно создано";
                    }
                    else {
                        cout << "Ошибка при создании дерева поиска";
                    }
                }
                else {
                    cout << "Ошибка при создании файла";
                }
                cout << endl;
            }
            else if (n == 11) {//Вывод дерева
                tree1.printBinTree2("", tree1.get_root(), false);

            }
            else if (n == 12) {
                string key;
                cout << "Введите ключ записи, доступ к которой хотите получить: ";
                if (cin >> key) {
                    auto start = std::chrono::steady_clock::now();
                    int z = search_in_file_by_balance_tree(bfile_name, key, tree1);
                    auto end = std::chrono::steady_clock::now();
                    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                    cout << "Время доступа " << duration << " мс" << endl;
                    // Вычисляем время доступа в миллисекундах
                    if (z == 1) {
                        cout << "Ошибка при чтении записи с ключом " << key << endl;
                    }
                    else if (z == 2) {
                        cout << "Не удалось открыть файл" << endl;
                    }
                    else if (z == -3) {
                        cout << "Файл пустой" << endl;
                    }
                }
                else {
                    cin.clear();
                    while (cin.get() != '\n') {
                        cout << "Введено неверно, повторите попытку" << endl;

                    }
                }
            }

            else if (n ==13 ) {
                cout << "Выполнен выход из программы" << endl;
                return 0;
            }
            else {
                cout << "Операции под таким номером нет в списке, повторите ввод" << endl;
            }

        }
        else {
            cin.clear();
            while (cin.get() != '\n') {
                cout << "Введено неверно, повторите попытку" << endl;

            }
        }
    }
    return 1;
}