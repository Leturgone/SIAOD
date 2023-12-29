#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include<vector>

int create_file(string file_name) {
    ofstream otf(file_name);// открытие потока для записи
    if (!otf) {
        return 1;
    }
    otf << "123" << " " << "12" << " " << "55" << " " <<"27" << " " <<"89" << " " <<"43" << " " <<"11" << " "<<"90" << " "<<"56" << " " <<"43"<< "\n";
    otf << "17" << " " << "37" << " " <<"13" << " " <<"41" << " " <<"15" << " " <<"61" << " "<<"17"<< "\n";
    otf << "81" << " " << "19" << "\n";
    otf << "49";
    otf.close();
    return 0;
}
void print_file(string file_name) {
    ifstream itf(file_name);//открытие файла и связывание с потоком
    if (!itf) {
        cout << "Не удалось открыть файл";
    }
    else {
        while (!itf.eof()) {
            int x;
            itf >> x;
            cout << x << " ";
        }
    }
    itf.close();
}


int count_num_in_file(string file_name) {
    ifstream itf(file_name);//открытие файла и связывание с потоком
    if (!itf) {
        return -1;
    }
    else {
        int n = 0;
        while (!itf.eof()) {
            int x;
            itf >> x;
            n++;
        }
        return n;
    }
    itf.close();
}
int add_to_file(string file_name, int new_num) {
    ifstream itf(file_name, ios::app);//открытие файла и связывание с потоком
    if (!itf) {
        return 1;
    }
    ofstream otf(file_name, ios::app);// открытие потока для записи
    if (otf.good()) {
        otf << ' ' << new_num;
    }
    itf.close();
    otf.close();
    return 0;
}
int get_number(string file_name, int pos) {
    ifstream itf(file_name);//открытие файла и связывание с потоком
    if (!itf) {
        return -1;
    }
    else {
        int n;
        for (int i = 0; i < pos; i++) {
            if (!(itf >> n)) {
                return -2;
            }
        }
        return n;
    }
    itf.close();
}
int var_func(string& file_name) {
    //28 Создать два новых файла из значений исходного, переписав в один из них  первую половину чисел исходного, 
    //а в другой, оставшуюся часть.В исходный
    //файл слить данные их двух новых файлов упорядоченными по возрастанию
    //парами, т.е.прочитать первые числа двух файлов, сначала в исходный файл
    //записать меньшее из них, а за ним большее.
    ifstream inputFile(file_name);
    if (!inputFile) {
        return 1;
    }
    ofstream outputFile1("file1.txt");
    ofstream outputFile2("file2.txt");
    vector<int> numbers;
    int number;
    //Добавляем в вектор все числа из файла
    while (inputFile >> number) {
        numbers.push_back(number);
    }
    int halfSize = numbers.size() / 2;
    int ostSize = numbers.size() - halfSize;
    //Первую половину вектора в первый файл, вторую во второй
    for (int i = 0; i < ostSize; i++) {
        if (i == ostSize-1) {
            outputFile1 << numbers[i];
        }
        else {
            outputFile1 << numbers[i] << " ";
        }
    }
    for (int i = ostSize; i < numbers.size(); i++) {
        if (i == numbers.size()-1) {
            outputFile2 << numbers[i];
        }
        else {
            outputFile2 << numbers[i] << " ";
        }
    }
    //Закрываем потоки
    inputFile.close();
    outputFile1.close();
    outputFile2.close();
    //Открываем новые, чтобы прочитать из двух созданных и записать в старый
    ifstream input1("file1.txt");
    ifstream input2("file2.txt");
    if (!input1 or !input2) {
        return 1;
    }
    ofstream output(file_name);
    //Сортируем и записываем
    int num1, num2;
    while (!input1.eof() or !input2.eof()) {
        input1 >> num1;
        input2 >> num2;
        if (input1.eof() and !input2.eof()) {
            output << " " << num2;
            break;
        }
        else if (input2.eof() and !input1.eof()) {
            output << " " << num1;
            break;
        }
        else if (num1 < num2) {
            output << " " << num1 << " " << num2;
        }
        else {
            output << " " << num2 << " " << num1;
        }
    }

    input1.close();
    input2.close();
    output.close();
    return 0;
}


