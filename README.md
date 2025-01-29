# Identifier Generator

## Описание:
Этот проект представляет собой C++ библиотеку для генерации уникальных идентификаторов. Библиотека поддерживает простые идентификаторы (буквы и цифры) и составные идентификаторы, разделенные символом -. В проекте включены юнит-тесты, документация и демонстрация принципов CI/CD.

Класс `IdentifierGenerator` предназначен для генерации последовательных идентификаторов. Он поддерживает простые и составные идентификаторы, разделенные символом `-`.

## Использование

### Класс `IdentifierGenerator`
Класс `IdentifierGenerator` содержит следующие методы:
* `std::string GenerateNextIdentifier(const std::string &identifier) const;` - Генерирует следующий идентификатор.
* `std::string incrementPart(const std::string& part) const;` - Приватный метод для увеличения части идентификатора.

### Правила генерации идентификаторов
* Первый сгенерированный идентификатор - `A1`.
* Последовательность символов увеличивается по следующему принципу: `A1, A2, ... , A9, B1, B2, ..., B9, ..., Z1, Z2, ..., Z9`.
* После `Z9` генерируется `A1`, и если это была первая часть идентификатора, добавляется еще одна `A1`. Пример `Z9` -> `A1-A1`.
* Допустимые символы: `A-Z`, `1-9`, `-`.
* Запрещенные символы: `0, D, F, G, J, M, Q, V`.
* Не допускается `-` в начале или конце строки, а также два `-` подряд.
* Максимальное количество частей в идентификаторе: 10.

### Инструкции по компиляции и запуску

1. Убедитесь, что у Вас установлен компилятор g++.

2. Перейдите в каталог `src`.

3. Скомпилируйте проект:
    ```bash
    g++ -std=c++11 -I. ../test/test_identifier_generator.cpp IdentifierGenerator.cpp -o test
    ```

4. Запустите тесты:
    ```bash
    test.exe
    ```

### Примеры использования

```cpp
#include "IdentifierGenerator.h"
#include <iostream>

int main() {
    IdentifierGenerator generator;
    std::cout << generator.GenerateNextIdentifier("") << std::endl;   // Вывод: A1
    std::cout << generator.GenerateNextIdentifier("A1") << std::endl; // Вывод: A2
    std::cout << generator.GenerateNextIdentifier("Z9") << std::endl; // Вывод: A1-A1
    std::cout << generator.GenerateNextIdentifier("A1-Z9") << std::endl;// Вывод: A2-A1

    try {
        std::cout << generator.GenerateNextIdentifier("-") << std::endl; // Вывод: std::invalid_argument
    } catch(const std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
std::cout << generator.GenerateNextIdentifier("A1-A1-A1-A1-A1-A1-A1-A1-A1-A9") << std::endl; // Вывод: std::invalid_argument
