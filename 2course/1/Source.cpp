#include <iostream>
#include <bitset>

using namespace std;

void fun1() {
	//5-ый, 11-ый, 3 - ий в значение 1 используя соответствующую маску и поразрядную операцию
	unsigned int digit = 0x1000;//4096 в десятичной, 1000000000000 в двоичной
	unsigned int mask = 0x0828;
	cout << "Число     : " << digit << "    " << bitset<16>(digit).to_string() << endl;
	cout << "Маска     : " << mask << "    " << bitset<16>(mask).to_string() << endl;
	digit = digit | mask;
	cout << "Результат : " << (digit) << "    " << bitset<16>(digit).to_string() << endl;
}

void fun2() {
	//Четыре старших бита в значение 0 используя соответствующую маску и поразрядную операцию
	unsigned int digit;
	cout << "Введите число: ";
	cin >> digit;
	unsigned int mask = (0xfffffff);//00001111111111111111111111111111 в двоичной
	cout << "Число     : " << digit << "    " << bitset<32>(digit).to_string() << endl;
	cout << "Маска     : " << mask << "    " << bitset<32>(mask).to_string() << endl;
	digit = digit & mask;
	cout << "Результат : " << (digit) << "    " << bitset<32>(digit).to_string() << endl;

}

void fun3() {
	//Разработать оператор присваивания и выражение которое умножает значение переменной на число 32 используя соответствующую поразрядную операцию
	unsigned int digit;
	cout << "Введите число: ";
	cin >> digit;
	//Нужно умножить введённое число на 32. Следовательно,нам нужно сдвинуть исходные байты влево на 2 в степени 5
	cout << "Число     : " << digit << "    " << bitset<16>(digit).to_string() << endl;
	cout << "Результат : " << (digit<<5) << "    " << bitset<16>((digit << 5)).to_string() << endl;
}

void fun4() {
	//Разработать оператор присваивания и выражение которое делит значение переменной на число 32 используя соответствующую поразрядную операцию
	unsigned int digit;
	cout << "Введите число: ";
	cin >> digit;
	//Тут аналогично третьему, но сдвигаем исходные байты направо на 5, тк надо деление
	cout << "Число     : " << digit << "    " << bitset<16>(digit).to_string() << endl;
	cout << "Результат : " << (digit >> 5) << "    " << bitset<16>((digit >> 5)).to_string() << endl;
}


void fun5() {
	//Разработать оператор присваивания и выражение, в котором используются 
	//только поразрядные операции.В выражении используется маска – переменная.
	//Обнулить n-ый бит, используя маску(вар 2). Маска инициализирована единицей в старшем разряде
	unsigned int digit;
	unsigned int mask;
	unsigned int nbite;
	cout << "Введите число: ";
	cin >> digit;
	cout << "Введите бит номер бита, который хотите обнулить: ";
	cin >> nbite;
	mask = 1 << 31;
	mask = mask>>(31-nbite);
	cout << "Число     : " << digit << "    " << bitset<32>(digit).to_string() << endl;
	cout << "Маска     : " << mask << "    " << bitset<32>(mask).to_string() << endl;
	cout << "Результат : " << (digit&(~mask)) << "    " << bitset<32>((digit & (~mask))).to_string() << endl;
}



int main() {
	setlocale(0, "");
	cout << "-----Задание 1---" << endl;
	cout << "Упражнение 1" << endl;
	fun1();
	cout << endl << "Упражнение 2" << endl;
	fun2();
	cout << endl << "Упражнение 3" << endl;
	fun3();
	cout << endl << "Упражнение 4" << endl;
	fun4();
	cout << endl << "Упражнение 5" << endl;
	fun5();
	return 0;
}
