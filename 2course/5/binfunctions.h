#include <iostream>
#include <fstream>

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
            itf.getline(r.car_num, 10, '\n');
            itf.getline(r.name, 20, '\n');
            itf.getline(r.car_model, 20, '\n');
            itf.getline(r.v_date, 15, '\n');
            itf.getline(r.v_place, 40, '\n');
            itf >> r.stat_num;
            itf >> r.fine;
            obf.write((char*)&r, sizeof(violation_record));
            //itf.get();
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
        if (strcmp(r.car_num,key)==0) {
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

        while (lastRecord.stat_num == 0 && recordSize > 1) {
            bf.seekg((recordSize - 2) * sizeof(violation_record));
            bf.read(reinterpret_cast<char*>(&lastRecord), sizeof(violation_record));
            recordSize--;
        }
        //����������� � ����� ������ ������ ���� �������
        bf.seekp(numRecord * sizeof(r), std::ios::beg);
        //���������� � ����� ������ ��������� ������
        bf.write(reinterpret_cast<char*>(&lastRecord), sizeof(r));

        bf.seekp((recordSize - 1) * sizeof(violation_record), ios::beg);
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
