#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <set>
#include <string>

int generateRandomNumber() {
    std::set<int> digits;
    while (digits.size() < 6) {
        int digit = rand() % 10;
        digits.insert(digit);
    }

    int number = 0;
    for (int digit : digits) {
        number = number * 10 + digit;
    }

    return number;
}

std::string convertToString(int number) {
    return std::to_string(number);
}

void writeToFile(const std::string& filePath, const std::string& content) {
    std::ofstream file(filePath, std::ios::app);
    if (file.is_open()) {
        file << content << "\n";
        file.close();
    }
}

int main() {
    // »нициализаци€ генератора случайных чисел
    srand(static_cast<unsigned int>(time(0)));

    for (int i = 0; i < 100; i++) {
        int randomNumber = generateRandomNumber();
        std::string randomString = convertToString(randomNumber);
        writeToFile("random_numbers.txt", randomString);
    }

    return 0;
}