#include <iostream>
#include <string>
#include "TreeAndFile.h"
using namespace std;


int main() {
    setlocale(0, "");
    string tfile_name;
    string bfile_name = "bf.dat";
    cout << "Введите имя файла: " << endl;
    cin >> tfile_name;
    cout << "---Меню работы с бинарным файлом---" << endl;
    cout << "1. Создать двоичный файл и сформировать дерево поиска" << endl << "2.Вывод дерева" << endl << "3.Найти запись по ключу используя дерево поиска" << endl <<"4. Удалить запись по ключу используя дерево поиска" <<endl<< "5. Вывод всех записей двоичного файла" << endl << "6. Выйти из программы" << endl;
    Bin_Tree tree;
    while (true) {
        int n;
        cout << "Выберите номер операции: ";
        if (cin >> n) {
            if (n == 1) {//создание файла
                if (create_bin_file(tfile_name, bfile_name) == 0) {
                    cout << "Файл успешно создан"<< endl;
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
            else if (n == 2) {//Вывод дерева
                tree.printBinTree2("", tree.get_root(), false);
                
            }
            else if (n == 3) {
                string key;
                cout << "Введите ключ записи, доступ к которой хотите получить: ";
                if (cin >> key) {
                    int z = search_in_file_by_tree(bfile_name, key,tree);
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
            else if (n == 4) {
                string i;
                cout << "Введите значение ключа: ";
                cin >> i;
                int z = delete_in_file_by_tree(bfile_name, i,tree);
                if (z == 0) {
                    cout << "Запись успешно удалена" << endl;
                }
                else if (z == -1) {
                    cout << "Не удалось удалить запись с ключом " << i << " из файла повторите попытку" << endl;
                }
                else if (z == -2) {
                    cout << "Не удалось удалить запись с ключом " << i << " из дерева повторите попытку" << endl;
                }
            }
            else if (n == 5) {
                if (print_bin_file(bfile_name) == 1) {
                    cout << "Не удалось открыть файл";
                }
                cout << endl;
            }
            else if (n == 6) {
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
    return 0;
}
