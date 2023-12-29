#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
struct violation_record {//Структура записи о нарушении
    char car_num[10];//номер автомобиля, в данном случае это будет ключом, потому что номер машины уникален
    char name[20];//Фамилия владельца и инициалы
    char car_model[20];//модель машины
    char v_date[15];//дата анрушения
    char v_place[40];//место нарушения
    double stat_num;//номер статьи
    int fine;//сумма штрафа

};
int create_bin_file(string nametf, string namebf) {
    ifstream itf(nametf);
    if (itf) {//если файл существует
        //Если файл существует, функция открывает бинарный файл (namebf) для чтения и записи в двоичном режиме. 
        fstream obf(namebf, ios::out | ios::binary);
        violation_record r;
        int len = sizeof(violation_record);
        while (!itf.eof()) {
            itf.getline(r.car_num, 20, '\n');
            itf.getline(r.name, 20, '\n');
            itf.getline(r.car_model, 20, '\n');
            itf.getline(r.v_date, 15, '\n');
            itf.getline(r.v_place, 40, '\n');
            itf >> r.stat_num;
            itf >> r.fine;
            obf.write((char*)&r, sizeof(violation_record));
            itf.ignore(1, '\n');
        }
        obf.close();
        itf.close();
        return 0;
    }
    itf.close();
    return 1;
}


//сохранение данных двоичного файла в текстовом, так, чтобы используя их можно было восстановить двоичный файл;
int convert_bin_to_txt(string nametf, string namebf) {
    fstream ibf(namebf, ios::in | ios::binary);
    ofstream otf(nametf);
    if (ibf && otf) {
        violation_record r;
        while (ibf.read((char*)&r, sizeof(violation_record))) {
            otf << r.car_num << endl;
            otf << r.name << endl;
            otf << r.car_model << endl;
            otf << r.v_date << endl;
            otf << r.v_place << endl;
            otf << r.stat_num << endl;
            otf << r.fine << endl;
        }
        ibf.close();
        otf.close();
        return 0;
    }
    ibf.close();
    otf.close();
    return 1;
}

//вывод всех записей двоичного файла;
int print_bin_file(string namebf) {
    fstream ibf(namebf, ios::in | ios::binary);
    if (ibf.is_open()) {
        violation_record r;
        ibf.read((char*)&r, sizeof(r));
        while (!ibf.eof()) {
            cout << r.car_num << "  " << r.name << "  " << r.car_model << "  " << r.v_date << "  " << r.v_place << "  " << r.stat_num << "  " << r.fine << "\n";
            ibf.read((char*)&r, sizeof(violation_record));
        }
        ibf.close();
        return 0;
    }
    ibf.close();
    return 1;

}

////доступ к записи по ее порядковому номеру в файле, используя механизм прямого доступа к записи в двоичном файле;
int get_access_to_rec(string namebf, int numRecord) {
    fstream ibf(namebf, ios::binary | ios::in);
    int i, kod;
    if (ibf.is_open()) {
        ibf.seekg(0, ios::end);
        streamsize fileSize = ibf.tellg();
        int recordSize = fileSize / sizeof(violation_record);
        if (recordSize == 0) {
            ibf.close();
            return -3;
        }
        ibf.seekg(0, ios::beg);
        violation_record r;
        int offset = numRecord * sizeof(r);
        ibf.seekg(offset, ios::beg);
        if (!ibf.bad() and numRecord<recordSize) {								//такой номер записи есть в файле
            ibf.read((char*)&r, sizeof(violation_record));
            if (r.fine != 0) {
                cout << r.car_num << "  " << r.name << "  " << r.car_model << "  " << r.v_date << "  " << r.v_place << "  " << r.stat_num << "  " << r.fine << "\n";
                kod = 0;  //результат в r и возвращаем код завершения 0
            }
            else {
                kod = 1;
            }
           
        }
        else
            kod = 1;									    //нет записи с таким номером в файле
    }
    else
        kod = 2;										    //файл не открылся
    ibf.close();
    return kod;
}

////удаление записи с заданным значением ключа, выполнить путем замены на последнюю запись.
int delete_rec_by_key(string& namebf, char key[10]) {
    fstream bf(namebf, ios::in | ios::out | ios::binary);
    if (!bf.is_open()) return -1;				//не открылся

    violation_record r1;
    violation_record r;
    bf.seekg(0, ios::end);
    streamsize fileSize = bf.tellg();
    int recordSize = fileSize / sizeof(violation_record);
    if (recordSize == 0) {
        bf.close();
        return -3;
    }
    bool flag = false;
    bf.seekg(0, ios::beg);
    int numRecord = 0;//порядковый номер записи 
    bf.read((char*)&r, sizeof(r));//читаем и сохраняем в r
    while (!bf.eof()) {
        if (strcmp(r.car_num, key) == 0) {
            flag = true;
            break;
        }
        bf.read((char*)&r, sizeof(r));
        numRecord++;
    }
    if (numRecord > recordSize or flag==false) {
        bf.close();
        return -2;
    }
    else {
        violation_record lastRecord;
        violation_record emptyRecord{ "","","","","",0,0 };
        //Берем последнюю запись
        bf.seekg((recordSize - 1) * sizeof(r), std::ios::beg);
        bf.read(reinterpret_cast<char*>(&lastRecord), sizeof(r));

        //Переносимся в место записи котрую надо уддалть
        bf.seekp(numRecord * sizeof(r), std::ios::beg);
        bf.write(reinterpret_cast<const char*>(&emptyRecord), sizeof(violation_record));

    }
    bf.close();
    return 0;
}

////Доп.операция 
////1. Сформировать список нарушений по
////автомобилю заданного номера.Результат сохранить
////в новом двоичном файле с той же 
//// структурой записи,что и исходный файл.
int form_violation_list(string namebf, char key[]) {
    fstream bf(namebf, ios::in | ios::out | ios::binary);
    if (!bf.is_open()) return -1;
    ofstream out_bf("violation.dat", std::ios::binary);
    bf.seekg(0, ios::beg);
    violation_record r;
    int numRecord = 0;//порядковый номер записи
    bool flag = false;
    bf.read((char*)&r, sizeof(r));//читаем и сохраняем в r
    while (bf.read(reinterpret_cast<char*>(&r), sizeof(violation_record))) {
        if (strcmp(r.car_num, key) == 0) {
            flag = true;
            numRecord++;
            out_bf.write(reinterpret_cast<const char*>(&r.stat_num), sizeof(r.stat_num));
        }
    }

    if (flag == false) {
        return -2;
    }
    bf.close();
    out_bf.close();
    return 0;
}
//
////2. Увеличить сумму штрафа вдвое по всем авто за
////указанную дату и по заданной статье.
int double_fin_in_date(string& namebf, char date[], double stat) {
    fstream file(namebf, std::ios::in | std::ios::out | std::ios::binary);
    if (file) {
        // Создание временного файла
        const char* tempFileName = "temp_file.dat";
        std::fstream tempFile(tempFileName, std::ios::out | std::ios::binary);
        bool flag = false;
        violation_record record;
        while (file.read(reinterpret_cast<char*>(&record), sizeof(violation_record))) {
            if (strcmp(record.v_date, date) == 0 && record.stat_num == stat) {
                flag = true;
                record.fine *= 2;
            }
            // Запись во временный файл
            tempFile.write(reinterpret_cast<char*>(&record), sizeof(violation_record));
        }
        if (flag == false) {
            return -2;
        }
        // Закрытие файлов
        file.close();
        tempFile.close();

        // Замена исходного файла временным файлом
        remove(namebf.c_str());               // Удаление исходного файла
        rename(tempFileName, namebf.c_str()); // Переименование временного файла
        return 0;
    }
    return -1;
}

int  testBinF() {
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
                        int z = get_access_to_rec(bfile_name, i - 1);
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
                    int z = double_fin_in_date(bfile_name, date, stat);
                    if (z == 0) {
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
