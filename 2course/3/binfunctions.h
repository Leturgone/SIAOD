#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
struct violation_record {//��������� ������ � ���������
    char car_num[10];//����� ����������, � ������ ������ ��� ����� ������, ������ ��� ����� ������ ��������
    char name[20];//������� ��������� � ��������
    char car_model[20];//������ ������
    char v_date[15];//���� ���������
    char v_place[40];//����� ���������
    double stat_num;//����� ������
    int fine;//����� ������

};
int create_bin_file(string nametf, string namebf) {
    ifstream itf(nametf);
    if (itf) {//���� ���� ����������
        //���� ���� ����������, ������� ��������� �������� ���� (namebf) ��� ������ � ������ � �������� ������. 
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


//���������� ������ ��������� ����� � ���������, ���, ����� ��������� �� ����� ���� ������������ �������� ����;
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

//����� ���� ������� ��������� �����;
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

////������ � ������ �� �� ����������� ������ � �����, ��������� �������� ������� ������� � ������ � �������� �����;
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
        if (!ibf.bad() and numRecord<recordSize) {								//����� ����� ������ ���� � �����
            ibf.read((char*)&r, sizeof(violation_record));
            if (r.fine != 0) {
                cout << r.car_num << "  " << r.name << "  " << r.car_model << "  " << r.v_date << "  " << r.v_place << "  " << r.stat_num << "  " << r.fine << "\n";
                kod = 0;  //��������� � r � ���������� ��� ���������� 0
            }
            else {
                kod = 1;
            }
           
        }
        else
            kod = 1;									    //��� ������ � ����� ������� � �����
    }
    else
        kod = 2;										    //���� �� ��������
    ibf.close();
    return kod;
}

////�������� ������ � �������� ��������� �����, ��������� ����� ������ �� ��������� ������.
int delete_rec_by_key(string& namebf, char key[10]) {
    fstream bf(namebf, ios::in | ios::out | ios::binary);
    if (!bf.is_open()) return -1;				//�� ��������

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
    int numRecord = 0;//���������� ����� ������ 
    bf.read((char*)&r, sizeof(r));//������ � ��������� � r
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
        //����� ��������� ������
        bf.seekg((recordSize - 1) * sizeof(r), std::ios::beg);
        bf.read(reinterpret_cast<char*>(&lastRecord), sizeof(r));

        //����������� � ����� ������ ������ ���� �������
        bf.seekp(numRecord * sizeof(r), std::ios::beg);
        bf.write(reinterpret_cast<const char*>(&emptyRecord), sizeof(violation_record));

    }
    bf.close();
    return 0;
}

////���.�������� 
////1. ������������ ������ ��������� ��
////���������� ��������� ������.��������� ���������
////� ����� �������� ����� � ��� �� 
//// ���������� ������,��� � �������� ����.
int form_violation_list(string namebf, char key[]) {
    fstream bf(namebf, ios::in | ios::out | ios::binary);
    if (!bf.is_open()) return -1;
    ofstream out_bf("violation.dat", std::ios::binary);
    bf.seekg(0, ios::beg);
    violation_record r;
    int numRecord = 0;//���������� ����� ������
    bool flag = false;
    bf.read((char*)&r, sizeof(r));//������ � ��������� � r
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
////2. ��������� ����� ������ ����� �� ���� ���� ��
////��������� ���� � �� �������� ������.
int double_fin_in_date(string& namebf, char date[], double stat) {
    fstream file(namebf, std::ios::in | std::ios::out | std::ios::binary);
    if (file) {
        // �������� ���������� �����
        const char* tempFileName = "temp_file.dat";
        std::fstream tempFile(tempFileName, std::ios::out | std::ios::binary);
        bool flag = false;
        violation_record record;
        while (file.read(reinterpret_cast<char*>(&record), sizeof(violation_record))) {
            if (strcmp(record.v_date, date) == 0 && record.stat_num == stat) {
                flag = true;
                record.fine *= 2;
            }
            // ������ �� ��������� ����
            tempFile.write(reinterpret_cast<char*>(&record), sizeof(violation_record));
        }
        if (flag == false) {
            return -2;
        }
        // �������� ������
        file.close();
        tempFile.close();

        // ������ ��������� ����� ��������� ������
        remove(namebf.c_str());               // �������� ��������� �����
        rename(tempFileName, namebf.c_str()); // �������������� ���������� �����
        return 0;
    }
    return -1;
}

int  testBinF() {
    setlocale(0, "");
    string tfile_name;
    string bfile_name = "bf.dat";
    cout << "������� ��� �����: " << endl;
    cin >> tfile_name;
    cout << "---���� ������ � �������� ������---" << endl;
    cout << "1. ������� �������� ����" << endl << "2. ��������� ������ ��������� � ��������� ����" << endl << "3. ����� ���� ������� ��������� �����" << endl << "4. �������� ������ � ������ �� ����������� ������" << endl << "5. ������� ������ � �������� ��������� �����" << endl << "6. ������������ ������ ��������� �� ���������� ��������� ������." << endl << "7. ��������� ����� ������ ����� �� ���� ���� �� ��������� ���� � �� �������� ������." << endl << "8. ����� �� ���������" << endl;
    while (true) {
        int n;
        cout << "�������� ����� ��������: ";
        if (cin >> n) {
            if (n == 1) {//�������� �����
                if (create_bin_file(tfile_name, bfile_name) == 0) {
                    cout << "���� ������� ������";
                }
                else {
                    cout << "������ ��� �������� �����";
                }
                cout << endl;
            }
            else if (n == 2) {//��������� ������ ��������� � ���������
                if (convert_bin_to_txt("bft.txt", bfile_name) == 0) {
                    cout << "���� ������� ������";
                }
                else {
                    cout << "������ ��� �������� �����";
                }
                cout << endl;
            }
            else if (n == 3) {
                if (print_bin_file(bfile_name) == 1) {
                    cout << "�� ������� ������� ����";
                }
                cout << endl;
            }
            else if (n == 4) {
                int i;
                cout << "������� ���������� ����� ������, ������ � ������� ������ ��������: ";
                if (cin >> i) {
                    if (i > 0) {
                        int z = get_access_to_rec(bfile_name, i - 1);
                        if (z == 1) {
                            cout << "������ ��� ������ ����� � �������� " << i << endl;
                        }
                        else if (z == 2) {
                            cout << "�� ������� ������� ����" << endl;
                        }
                        else if (z == -3) {
                            cout << "���� ������" << endl;
                        }
                    }
                    else {
                        cout << "���������� ����� �� ����� ���� ���������������, ��������� �������" << endl;
                    }
                }
                else {
                    cin.clear();
                    while (cin.get() != '\n') {
                        cout << "������� �������, ��������� �������" << endl;

                    }
                }
            }
            else if (n == 5) {
                char i[10];
                cout << "������� �������� �����: ";
                cin >> i;
                int z = delete_rec_by_key(bfile_name, i);
                if (z == 0) {
                    cout << "������ ������� �������" << endl;
                }
                else if (z == -1) {
                    cout << "�� ������� ������� ����" << endl;
                }
                else if (z == -2) {
                    cout << "�� ������� ����� ������ � ������ " << i << " ��������� �������" << endl;
                }
                else if (z == -3) {
                    cout << "���� ����" << endl;
                }
            }
            else if (n == 6) {
                char num[10];
                string nbfile_name = "bf.dat";
                cout << "������ ����� ����������: " << endl;
                cin >> num;
                int z = form_violation_list(nbfile_name, num);
                if (z == 0) {
                    cout << "�������� ��������� �������" << endl;

                }
                else if (z == -2) {
                    cout << "��� ������ ��� ����� �������" << endl;
                }
                else if (z == -3) {
                    cout << "���� ����" << endl;
                }
                else {
                    cout << "�� ������� ������� ����" << endl;
                }
            }
            else if (n == 7) {
                double stat;
                char date[10];
                cout << "������� ����� ������: ";
                if (cin >> stat) {
                    cout << "������� ����: ";
                    cin >> date;
                    int z = double_fin_in_date(bfile_name, date, stat);
                    if (z == 0) {
                        cout << "�������� ��������� �������" << endl;
                    }
                    else if (z == -1) {
                        cout << "�� ������� ������� ����" << endl;
                    }
                    else if (z == -2) {
                        cout << "������ � ����������� ������� �� �������" << endl;
                    }
                    else {
                        cout << "�� ������� ������� ����" << endl;
                    }
                }
                else {
                    cin.clear();
                    while (cin.get() != '\n') {
                        cout << "����� ������ ������ �������, ��������� ����" << endl;
                    }
                }
            }
            else if (n == 7) {

            }
            else if (n == 8) {
                cout << "�������� ����� �� ���������" << endl;
                return 0;
            }
            else {
                cout << "�������� ��� ����� ������� ��� � ������, ��������� ����" << endl;
            }
        }
        else {
            cin.clear();
            while (cin.get() != '\n') {
                cout << "������� �������, ��������� �������" << endl;

            }
        }
    }
    return 0;
}
