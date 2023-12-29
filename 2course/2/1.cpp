#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include<vector>
#include "functions.h"
int main() {
    setlocale(0, "");
    ofstream otf;
    string file_name;
    string file_name1 = "t2.txt";
    cout << "Введите название файла " << endl;
    cin >> file_name;
    cout << "---Меню работы с файлом---" << endl;
    cout <<"1. Создать новый файл" <<endl<< "2. Вывести содержимое текстового файла" << endl << "3. Добавить новую запись в конец файла;" << endl << "4. Прочитать значение числа, указав его порядковый номер в файле, и вернуть его значение" << endl << "5. Определить количество чисел в файле" << endl << "6. Создать два новых файла и упорядочить старый" << endl << "7. Выйти из программы" << endl;
    while (true) {
        int n;
        cout << "Выберите номер операции: ";
        if (cin >> n) {
            if (n == 1) {//создание файла
                if (create_file(file_name)==0) {
                    cout << "Файл успешно создан";
                }
                else {
                    cout << "Ошибка при создании файла";
                }
                cout << endl;
            }
            else if (n == 2) {//вывод файла
                print_file(file_name);
                cout << endl;
            }
            else if (n == 3) {
                int new_num;
                cout << "Введите число, которое хотите добавить в конец файла: ";
                if (cin >> new_num) {
                    if (add_to_file(file_name, new_num)==0) {
                        cout << "Число " << new_num << " успешно добавлено в файл" << endl;
                    }
                    else {
                        cout << "Не удалось открыть файл" << endl;
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
                int i;
                cout << "Введите порядковый номер числа, значения которого хотите получить: ";
                if (cin >> i) {
                    if (i > 0) {
                        int z = get_number(file_name, i);
                        if (z >= 0) {
                            cout << "Число под номером " << i << ": " << z << endl;
                        }
                        else if (z == -1) {
                            cout << "Не удалось открыть файл" << endl;
                        }
                        else {
                            cout << "Ошибка при чтении числа с индексом " << i << endl;
                        }
                    }
                    else {
                        cout << "Порядковый номер не может быть неположительным, повторите попытку" << endl;
                    }
                }
                else {
                    cin.clear();
                    while (cin.get() != '\n') {
                        cout << "Введено неверно, повторите попытку" << endl;

                    }
                }
            }
            else if (n == 5) {
                int c = count_num_in_file(file_name);
                if (c >= 0) {
                    cout << "Количество чисел в файле: " << c << endl;
                }
                else {
                    cout << "Не удалось открыть файл" << endl;
                }
            }
            else if (n == 6) {
                if (var_func(file_name) == 0) {
                    cout << "Операция произошла успешно" << endl;
                }
                else {
                    cout << "Не удалось открыть файл" << endl;
                }
            }
            else if (n == 7) {
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
}