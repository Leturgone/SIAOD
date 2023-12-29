#include <iostream>
#include <vector>
#include "hashtabfuctions.h"
using namespace std;

int main() {
    setlocale(0, "");
    Hash_Table table(100);
    const int keyCount = 5;
    int num;
    char keys[keyCount][10] = {
        "ABC123",
        "DEF124",
        "ABC245",
        "BHT763",
        "ABC222"};
    cout << "1.Тест втсавки ключей в таблицу без коллизии и с коллизией: " << endl;
    // Вставка элементов в хеш-таблицу
    for (int i = 0; i < keyCount; i++) {
        num = i + 1;
        if ((table.insert_el(keys[i],num)) == 0){
            cout << "Ключ " << keys[i] << " успешно вставлен в таблицу" << endl;
        }
        else {
            cout << "Ошибка при вставке ключа " << keys[i] << endl;
        }
    }
    table.print();
    // Поиск элементов в хеш-таблице
    cout << "2.Тест поиска ключей в хэш таблице: " << endl;
    for (int i = 0; i < keyCount; i++) {
        int result = table.search_el(keys[i]);
        if (result != -1) {
            cout << "Элемент с ключом  " << keys[i] << " найден в хэш таблице под индексом " << result << endl;
        }
        else {
            cout << "Элемент с ключом " << keys[i] << " не найден" << endl;
        }
    }
    table.print();
    cout << "3.Тест рехешированния таблицы: " << endl;
    // Вывод содержимого хеш-таблицы
    cout << "---Таблица рехешированнна---" << endl;
    table.rehash();
    table.print();
    cout << "4.Удаления ключей в таблице: " << endl;
    // Удаление элементов из хеш-таблицы
    int result = table.delete_el(keys[0]);
    if (result == 0) {
        cout << "Элемент с ключом " << keys[0] << " успешно удален" << endl;
    }
    else {
        cout << "Ошибка при удалении ключа " << keys[0] << endl;
    }
    table.print();
    cout << "5.Специальный тест для метода с открытм адресом: " << endl;
    result = table.search_el(keys[4]);
    if (result != -1) {
        cout << "Элемент с ключом  " << keys[4] << " найден в хэш таблице" << endl;
    }
    else {
        cout << "Элемент с ключом " << keys[4] << " не найден" << endl;
    }
    return 0;

}