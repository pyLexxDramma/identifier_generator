#include "IdentifierGenerator.h"
#include <iostream>
#include <cassert>
#include <stdexcept>

/**
 * @brief Тестирует генерацию идентификатора для пустого входного значения.
 */
void test_empty_identifier() {
    IdentifierGenerator generator;
    std::string nextId = generator.GenerateNextIdentifier("");
    assert(nextId == "A1");
    std::cout << "test_empty_identifier passed" << std::endl;
}

/**
 * @brief Тестирует инкремент идентификаторов.
 */
void test_simple_increment() {
    IdentifierGenerator generator;
    std::string id = "A1";
    std::string nextId = generator.GenerateNextIdentifier(id);
    assert(nextId == "A2");
    std::cout << "test_simple_increment passed" << std::endl;

    id = "A9";
    nextId = generator.GenerateNextIdentifier(id);
    assert(nextId == "B1");
    std::cout << "test_simple_increment passed" << std::endl;

    id = "Z9";
    nextId = generator.GenerateNextIdentifier(id);
    assert(nextId == "A1-A1");
    std::cout << "test_simple_increment passed" << std::endl;
}

/**
 * @brief Тестирует инкремент идентификаторов с несколькими частями.
 */
void test_multi_part_increment() {
    IdentifierGenerator generator;
    std::string id = "A1-Z9";
    std::string nextId = generator.GenerateNextIdentifier(id);
    assert(nextId == "A2-A1");
    std::cout << "test_multi_part_increment passed" << std::endl;

    id = "A1-A1-Z9";
    nextId = generator.GenerateNextIdentifier(id);
    assert(nextId == "A1-A2-A1");
    std::cout << "test_multi_part_increment passed" << std::endl;
}

/**
 * @brief Тестирует обработку недопустимых символов в идентификаторе.
 */
void test_invalid_chars() {
    IdentifierGenerator generator;
    std::string testCases[] = {"A0", "AD", "A-1", "A-"};
    for (const auto& testCase : testCases) {
        std::cout << "Testing invalid input: " << testCase << std::endl;
        try {
            generator.GenerateNextIdentifier(testCase);
            std::cout << "Test FAILED: Exception not thrown for '" << testCase << "'" << std::endl;
            assert(false);
        } catch (const std::invalid_argument& e) {
            std::cout << "Test PASSED: Exception thrown for '" << testCase << "'" << std::endl;
        } catch (...) {
            std::cout << "Test FAILED: Unexpected exception thrown for '" << testCase << "'" << std::endl;
            assert(false);
        }
    }
}

/**
 * @brief Тестирует максимальную длину идентификатора.
 */
void test_max_length() {
    IdentifierGenerator generator;
    std::string id = "A1-A1-A1-A1-A1-A1-A1-A1-A1-A9";
    try {
        generator.GenerateNextIdentifier(id);
        assert(false);
    } catch (const std::invalid_argument& e) {
        assert(true);
        std::cout << "test_max_length passed" << std::endl;
    }
}

/**
 * @brief Главная функция для запуска всех тестов.
 *
 * @return int Код возврата.
 */
int main() {
    test_empty_identifier();
    test_simple_increment();
    test_multi_part_increment();
    test_invalid_chars();
    test_max_length();

    return 0;
}
