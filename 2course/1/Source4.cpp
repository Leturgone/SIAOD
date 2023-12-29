#include <iostream>

const int ARRAY_SIZE = 320;
const int BITS_PER_ELEMENT = sizeof(unsigned int) * 8;

void printSetBits(unsigned int A[], int size) {
    for (int i = 0; i < size; i++) {
        unsigned int element = A[i];
        for (int bit = 0; bit < BITS_PER_ELEMENT; bit++) {
            if (element & (1u << bit)) {
                int bitNumber = i * BITS_PER_ELEMENT + bit;
                std::cout << bitNumber << " ";
            }
        }
    }
}

int main() {
    unsigned int A[ARRAY_SIZE / BITS_PER_ELEMENT] = {
        // «десь должны быть значени€ заполненного массива A
    };

    // ¬ывод номеров заполненных битов массива A
    std::cout << "Ќомера заполненных битов: ";
    printSetBits(A, ARRAY_SIZE / BITS_PER_ELEMENT);
    std::cout << std::endl;

    return 0;
}