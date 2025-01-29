#include <iostream>
#include "IdentifierGenerator.h"

int main() {
    IdentifierGenerator generator;
    std::cout << generator.GenerateNextIdentifier("") << std::endl;   // Вывод: A1
    std::cout << generator.GenerateNextIdentifier("A1") << std::endl; // Вывод: A2
    std::cout << generator.GenerateNextIdentifier("Z9") << std::endl; // Вывод: A1-A1
    return 0;
}
