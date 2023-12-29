#include <iostream>
using namespace std;
void f(unsigned int x) {
	int offset = sizeof(x)*8;
	int maska = 0x80000000;;
	for (int i = 0; i<offset; i++) {
		cout << x & (1 << (offset - 1)) >> i);
		cout << ((x & maska) >> n - 1-i);
		maska = maska >> 1;
	}

}
int main() {
}