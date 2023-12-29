#include <iostream>
#include <vector>
using namespace std;
struct HashTableElement {
    char key_in_file[10];
    int recnum_in_file;
    bool deleted;
};

struct Hash_Table {
    int TABLE_SIZE;//размер таблицы
    int elem_count=0;
    vector<HashTableElement*> table;//массив, который содержит элементы хеш таблицы
    Hash_Table(int size) {
        TABLE_SIZE = size;
        table.resize(TABLE_SIZE, nullptr); // изменение размера вектора и инициализация nullptr
    }
    ~Hash_Table() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            delete table[i]; // освобождение памяти для каждого элемента
        }
    }
    int insert_el(char key[],int num) {
        HashTableElement element;
        strncpy_s(element.key_in_file, sizeof(element.key_in_file), key, 6);
        element.key_in_file[7] = '\0';
        element.key_in_file[8] = '\0';
        element.key_in_file[9] = '\0';
        element.recnum_in_file = num;
        element.deleted = false;
        int index = hash_f(element.key_in_file); // вычисление индекса (хеш-кода) элемента
        int originalIndex = index;
        // поиск свободной ячейки для вставки элемента

        while ((table[index] != nullptr) and (strcmp(table[index]->key_in_file, "") != 0)) {
            index = (index + 1) % TABLE_SIZE; // метод разрешения коллизии Открытый адрес (смещение на 1)
            if (index == originalIndex) {
                return -1;
            }
        }

        // вставка элемента в таблицу
        table[index] = new HashTableElement; // создание нового объекта
        *table[index] = element; // копирование данных
        elem_count = elem_count + 1;
        //double elemnum = elemcount();
        if (double(elem_count)/TABLE_SIZE>0.75) {
            rehash();
            cout << "Выполнено рехеширование, текущий размер таблицы - > " <<TABLE_SIZE << endl;
        }
        return 0;
    }

    int hash_f(char key_in_file[]) {
        int sum = 0;
        for (int i = 0; i < 6; i++) {
            sum += static_cast<int>(key_in_file[i]); // Суммируем ASCII-коды символов
        }
        return sum % TABLE_SIZE;
    }
    int search_el(char key[]) {
        int index = hash_f(key);
        int originalIndex = index;
        if (index >= 0) {
            while (table[index] != nullptr) {
                if (!table[index]->deleted && (strcmp(table[index]->key_in_file, key) == 0)) {
                    return table[index]->recnum_in_file;//нашли
                }
                index = (index + 1) % TABLE_SIZE;//если не нашли то идем дальше

                if (index == originalIndex) {
                    break;
                }
            }
            return -1; // Элемент не найден
        }
        else {
            return -1;
        }
    }
    int delete_el(char key[]) {
        int index = hash_f(key);
        int originalIndex = index;
        while (table[index] != nullptr) {
            if (!table[index]->deleted && (strcmp(table[index]->key_in_file, key) == 0)) {
                table[index]->deleted = true;
                return 0;
            }
            index = (index + 1) % TABLE_SIZE;

            if (index == originalIndex) {
                break;
            }
        }
        return -1;//не получилось удалить
    }
    void print() {
        bool flag = false;
        cout << "Хэш таблица: " << endl;
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (table[i] != nullptr and table[i]->deleted == false) {
                cout << i << " ----- " << table[i]->key_in_file << endl;
                flag = true;
            }
        }
        if (flag == false) {
            cout << "В хэш таблице нет элементов" << endl;;
        }
    }
    void rehash() {
        int TABLE_SIZE2 = TABLE_SIZE * 2;
        vector<HashTableElement*> temp_table(TABLE_SIZE2, nullptr);
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (table[i] != nullptr) {
                int sum = 0;
                for (int i1 = 0; i1 < 10; i1++) {
                    sum += static_cast<int>(table[i]->key_in_file[i1]); // Суммируем ASCII-коды символов
                }
                int index = sum % TABLE_SIZE2;
                while ((temp_table[index] != nullptr) and (strcmp(temp_table[index]->key_in_file, "") != 0)) {
                    index = (index + 1) % (TABLE_SIZE2); // метод разрешения коллизии Открытый адрес (смещение на 1)
                }
                temp_table[index] = new HashTableElement;
                *temp_table[index] = *table[i];

            }
        }
        // освобождение памяти, занятой старым массивом
        for (int i = 0; i < TABLE_SIZE; i++) {
            delete table[i];
        }

        // обновление указателей на новый массив и размер таблицы
        table = temp_table;
        TABLE_SIZE = TABLE_SIZE2;
    }

};


int testHeshT() {
    setlocale(0, "");
    Hash_Table table(100);
    const int keyCount = 5;
    int num;
    char keys[keyCount][10] = {
        "ABC123",
        "DEF124",
        "ABC245",
        "BHT763",
        "ABC222" };
    cout << "1.Тест втсавки ключей в таблицу без коллизии и с коллизией: " << endl;
    // Вставка элементов в хеш-таблицу
    for (int i = 0; i < keyCount; i++) {
        num = i + 1;
        if ((table.insert_el(keys[i], num)) == 0) {
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