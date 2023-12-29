#include <iostream>
using namespace std;

struct violation_record {
    char car_num[10];
    char name[20];
    char car_model[20];
    char v_date[15];
    char v_place[40];
    double stat_num;
    int fine;
};

int main() {
    setlocale(0, "");
    struct violation_record record;
    size_t size = sizeof(record);
    printf("Размер структуры: %zu байт\n", size);
    return 0;
}