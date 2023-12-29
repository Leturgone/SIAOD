#include <iostream>
using namespace std;
#include <chrono>
#include "hashfilefunr.h"

int main() {
    setlocale(0, "");
    Hash_Table table(100);
    string tfile_name;
    string bfile_name = "bf.dat";
    cout << "Введите имя файла: " << endl;
    cin >> tfile_name;
    cout << "---Меню работы с бинарным файлом ---" << endl;
    cout << "1. Создать двоичный файл" << endl  << "2. Вывод всех записей двоичного файла" << endl << endl<<"---Функции работы с файлом при помощи хэш таблицы---"<<endl<<"3. Прочитать записи из файла и вставить элементы в таблицу"<<endl << "4. Удалить запись из таблицы при заданном значении ключа и соответственно из файла" << endl << "5.  Найти запись в файле по значению ключа" << endl << "6. Вывести элементы хэш таблицы" <<endl << "7. Рехешировать таблицу" << endl << "8. Выйти из программы" << endl;
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
                int z = insert_rec_from_file(bfile_name,table);
                if (z == 0){
                    cout << "Хэш таблица сформирована" << endl;
                }
                else {
                    cout << "Ключи из файла уже записаны в хэш таблицу" << endl;
                }
            }
            else if (n == 4) {
                char num[10];
                cout << "Введите ключ записи ( номер автомобиля) , которую хотите удалить из хэш таблицы:" << endl;
                cin >> num;
                int z = delete_rec_from_file(num, bfile_name, table);
                if (z == 0) {
                    cout << "Ключ " << num << " успешно удален из файла и таблицы" << endl;
                }
                else if (z == -1) {
                    cout << "Запись с таким ключом не найдена" << endl;
                }
                else {
                    cout << "Ошибка при удалении ключа " << num << endl;
                }
            }
            else if (n == 5) {
                char num[10];
                cout << "Введите ключ записи ( номер автомобиля) , которую хотите найти в файле:" << endl;
                cin >> num;
                int z;
                auto start = std::chrono::steady_clock::now();
                z = find_rec_by_key_hash(num, bfile_name, table);
                auto end = std::chrono::steady_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                cout <<"Время доступа " << duration <<" мс"<< endl;
                // Вычисляем время доступа в миллисекундах

                if (z == -1) {
                    cout << "В хэш таблице нет записи с таким ключом" <<endl;
                }
                else if(z!=0) {
                    cout << "Ошибка при получении доступа" << endl;
                }
            }
            else if (n == 6) {
                table.print();
            }
            else if (n == 7) {
                table.rehash();
                cout << "Выполнено рехеширование, текущий размер таблицы - > "<<table.TABLE_SIZE << endl;
            }
            else if (n == 8) {
                cout << "Выполнен выход из программы" << endl;
                return 0;
            }
            else {
                cout << "Операции под таким номером нет в списке, повторите ввод" << endl;
            }

        }
        else{
            cin.clear();
            while (cin.get() != '\n') {
                cout << "Введено неверно, повторите попытку" << endl;

            }
        }
    }
	return 1;
}