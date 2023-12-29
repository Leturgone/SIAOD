#include <iostream>
#include <bitset>

using namespace std;
void fun3() {
	unsigned int digit;
	cout << "Введите число: ";
	int n = 3;
	int p = 5;
	cin >> digit;
	unsigned int mask = (~0 << n) << (p + 1 - n);
	cout << "Число     : " << digit << "    " << bitset<32>(digit).to_string() << endl;
	cout << "Маска     : " << mask << "    " << bitset<32>(mask).to_string() << endl;
	digit = (digit & ~(~0 << n)) << (p + 1 - n);
	cout << "Результат : " << (digit) << "    " << bitset<32>(digit).to_string() << endl;

}
#define SHIFT 5
#define MASK 0x1F
const int N = 10000000;
int a[N / 32];
void set(int i) { a[i >> SHIFT] |= (1 << (i & MASK)); }
void clr(int i) { a[i >> SHIFT] &= ~(1 << (i & MASK)); }

int main() {
	setlocale(0, "");
	set(37);
	clr(37);
	cout << a;
	fun3();
	return 0;
}