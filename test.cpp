#include <iostream>

int main() {
    int num1 = 12;  // Binary: 1100
    int num2 = 9;   // Binary: 1001

    int result = num1 & num2;  // Binary result: 1000 (Decimal: 8)

    std::cout << "num1 & num2 = " << result << std::endl;

    return 0;
}