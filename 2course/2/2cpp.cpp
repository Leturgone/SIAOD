#include <iostream>
#include <fstream>
#include "binfunctions.h"


int main() {
	setlocale(0, "");
	string tfile_name;
    string bfile_name = "bf.dat";
	cout << "Введите имя файла: " << endl;
	cin >> tfile_name;
	cout << "---Меню работы с бинарным файлом---" << endl;
    cout << "1. Создать двоичный файл" << endl << "2. Сохранить данные двоичного в текстовый файл" << endl << "3. Вывод всех записей двоичного файла" << endl << "4. Получить доступ к записи по порядковуму номеру" << endl << "5. Удалить запись с заданным значением ключа" << endl << "6. Сформировать список нарушений по автомобилю заданного номера." << endl << "7. Увеличить сумму штрафа вдвое по всем авто за указанную дату и по заданной статье." << endl << "8. Выйти из программы" << endl;
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
            else if (n == 2) {//сохранить данные двоичного в текстовый
                if (convert_bin_to_txt("bft.txt", bfile_name) == 0) {
                    cout << "Файл успешно создан";
                }
                else {
                    cout << "Ошибка при создании файла";
                }
                cout << endl;
            }
            else if (n == 3) {
                if (print_bin_file(bfile_name) == 1) {
                    cout << "Не удалось открыть файл";
                }
                cout << endl;
            }
            else if (n == 4) {
                int i;
                cout << "Введите порядковый номер записи, доступ к которой хотите получить: ";
                if (cin >> i) {
                    if (i > 0) {
                        int z = get_access_to_rec(bfile_name,i-1);
                        if (z == 1) {
                            cout << "Ошибка при чтении числа с индексом " << i << endl;
                        }
                        else if (z == 2) {
                            cout << "Не удалось открыть файл" << endl;
                        }
                        else if (z == -3) {
                            cout << "Файл пустой" << endl;
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
                char i[10];
                cout << "Введите значение ключа: ";
                cin >> i;
                int z = delete_rec_by_key(bfile_name, i);
                if (z == 0) {
                    cout << "Запись успешно удалена" << endl;
                }
                else if (z == -1) {
                    cout << "Не удалось открыть файл" << endl;
                }
                else if (z == -2) {
                    cout << "Не удалось найти запись с ключом " << i << " повторите попытку" << endl;
                }
                else if (z == -3) {
                    cout << "Файл пуст" << endl;
                }
            }
            else if (n == 6) {
                char num[10];
                string nbfile_name = "bf.dat";
                cout << "Введит номер автомобиля: " << endl;
                cin >> num;
                int z = form_violation_list(nbfile_name, num);
                if (z == 0) {
                    cout << "Операция произошла успешно" << endl;

                }
                else if (z == -2) {
                    cout << "Нет машины под таким номером" << endl;
                }
                else if (z == -3) {
                    cout << "Файл пуст" << endl;
                }
                else {
                    cout << "Не удалось открыть файл" << endl;
                }
            }
            else if (n == 7) {
                double stat;
                char date[10];
                cout << "Введите номер статьи: ";
                if (cin >> stat) {
                    cout << "Введите дату: ";
                    cin >> date;
                    int z= double_fin_in_date(bfile_name, date,stat);
                    if (z== 0) {
                        cout << "Операция произошла успешно" << endl;
                    }
                    else if (z == -1) {
                        cout << "Не удалось открыть файл" << endl;
                    }
                    else if (z == -2) {
                        cout << "Записи с подходящими данными не найдены" << endl;
                    }
                    else {
                        cout << "Не удалось открыть файл" << endl;
                    }
                }
                else {
                    cin.clear();
                    while (cin.get() != '\n') {
                        cout << "Номер статьи ввелен неверно, повторите ввод" << endl;
                    }
                }
            }
            else if (n == 7) {

            }
            else if (n == 8) {
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

