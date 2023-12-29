//28 Кузнечик прыгает вперед по столбикам, 
//расположенным на одной линии на равных
//расстояниях друг от друга.Столбики имеют
//порядковые номера от 1 до N.Вначале
//Кузнечик сидит на столбике с номером 1. Он
//может прыгнуть вперед на расстояние от 1 до
//K столбиков, считая от текущего.На каждом
//столбике Кузнечик имеет определенный шанс
//встретиться с лягушкой.Определите, как
//нужно прыгать Кузнечику, чтобы встретить
//как можно меньше лягушек.

//Динамическое программирование
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;
void dinamic_method(int N, int K,vector<int>frogs) {
    vector<int> dp(N + 1, 10000);//Вектор для хранения стоимости достижения столбика
    vector<int> jumps(N + 1, 0); //Вектор для хранения прыжков
    dp[1] = 0;
    int P=0;
    //Перебор позиций и прыжкой
    for (int i = 2; i <= N; i++) {
        int frog = frogs[i];
        for (int j = 1; j <= K; j++) {
            if (j < i) {
                //находим куда прыгать
                if (dp[i] > dp[i - j] + frog) {//если стоимость меньще текущего значения, то обновляем
                    dp[i] = dp[i - j] + frog;
                    jumps[i] = j; // Сохраняем номер прыжка
                }
            }
            P = P + 1;
        }
    }
    cout << "Маршрут прыжков (метод динамического програмирования): ";
    int cur = N;
    while (cur > 1) {
        cout << jumps[cur] << " ";
        cur -= jumps[cur];
    }
    cout << endl;
    cout << "Количество переборов (метод динамического програмирования): "<<P << std::endl;
}

int brute_force_method(int N, int K, vector<int>& frogs, vector<int>& jumps,int& P) {
    if (N <= 1) {
        return 0;
    }

    int min_frogs = 10000;//количество встреченных лягушек

    for (int i = 1; i <= K; i++) {
        P = P + 1;
        if (i < N) {

            //Эта стоимость рекурсивно вычисляется для позиции N - i и суммируется с количеством лягушек.
            //Если эта стоимость меньше текущего значения min_frogs, то она обновляется, а номер прыжка i сохраняется в векторе jumps для позиции N.
            int curr_frogs = brute_force_method(N - i, K, frogs, jumps,P) + frogs[N];
            if (curr_frogs < min_frogs) {
                min_frogs = curr_frogs;
                jumps[N] = i;
            }
        }
    }

    return min_frogs;
}

void brute_force_method(int N, int K, vector<int>& frogs) {
    vector<int> jumps(N + 1, 0); // Вектор для хранения прыжков
    int P = 0;
    brute_force_method(N, K, frogs, jumps,P);

    cout << "Маршрут прыжков (метод грубой силы): ";
    int cur = N;
    while (cur > 1) {
        cout << jumps[cur] << " ";
        cur -= jumps[cur];
    }
    cout << endl;
    cout << "Количество переборов (метод грубой силы): " << P << endl;
}

int main() {
    setlocale(0, "");
    int N, K;
    while (true) {
        cout << "Введите количество столбиков (N) и максимальную длину прыжка (K): ";
        if (cin >> N >> K) {
            srand(time(0)); // Инициализация генератора случайных чисел
            vector<int>frogs(N + 1, 0);
            for (int i = 2; i <=N; i++) {
                frogs[i] = rand() % 2;
            }
            cout << "Расположение лягушек: " << endl;
            cout << "Столбики ";
            for (int i = 1; i <=N; i++) {
                cout << i << " ";
            }
            cout << endl;
            cout << "Лягушки  ";
            for (int i = 1; i <=N ; i++) {
                cout<<frogs[i]<<" ";
            }
            cout << endl;
            dinamic_method(N, K,frogs);
            brute_force_method(N, K, frogs);
            return 0;
        }
        else {
            cin.clear();
            while (cin.get() != '\n') {
                cout << "Введено неверно, повторите попытку" << endl;

            }
        }
    }
}
