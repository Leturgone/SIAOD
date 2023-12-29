#include <iostream>
using namespace std;
#include <chrono>
#include "hashtabfuctions.h"
#include "binfunctions.h"
//1) Прочитать запись из файла и вставить элемент в таблицу(элемент
//включает : ключ и номер записи с этим ключом в файле, и для метода с
//открытой адресацией возможны дополнительные поля).
//2) Удалить запись из таблицы при заданном значении ключа и соответственно из файла.
//3) Найти запись в файле по значению ключа(найти ключ в хеш - таблице,
//получить номер записи с этим ключом в файле, выполнить прямой доступ
//к записи по ее номеру).
//

int insert_rec_from_file(string& namebf, Hash_Table& table) {
    int numRecord=0;
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