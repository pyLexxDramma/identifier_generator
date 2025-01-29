#include "IdentifierGenerator.h"
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept> // For std::invalid_argument

/**
 * @brief Генерирует следующий идентификатор на основе переданного.
 *
 * @param identifier Исходный идентификатор.
 * @return std::string Следующий идентификатор.
 * @throws std::invalid_argument Если идентификатор имеет недопустимый формат.
 */
std::string IdentifierGenerator::GenerateNextIdentifier(const std::string &identifier) const {
    if (identifier.empty()) {
        return "A1"; // Special case for empty identifier
    }

    // Проверка на валидность символов и формата ПЕРЕД разделением на части
    if (identifier == "-") {
        throw std::invalid_argument("Invalid identifier format: '-' is not allowed as a single character.");
    }
    for (size_t i = 0; i < identifier.length(); ++i) {
        char c = identifier[i];
        if (c == '0' || c == 'D' || c == 'F' || c == 'G' || c == 'J' || c == 'M' || c == 'Q' || c == 'V') {
            throw std::invalid_argument("Invalid identifier format: forbidden character '" + std::string(1, c) + "' found.");
        }
        if (!((c >= 'A' && c <= 'Z') || (c >= '1' && c <= '9') || (c == '-'))) {
            throw std::invalid_argument("Invalid identifier format: invalid character '" + std::string(1, c) + "' found.");
        }
        if (c == '-' && (i == 0 || i == identifier.length() - 1)) {
            throw std::invalid_argument("Invalid identifier format: '-' cannot be at the beginning or end.");
        }
        if (i > 0 && c == '-' && identifier[i - 1] == '-') {
            throw std::invalid_argument("Invalid identifier format: consecutive '-' characters.");
        }
    }

    std::vector<std::string> parts;
    std::string current_part;

    // Разделение идентификатора на части (A1, B2, A1-A1)
    for (char c : identifier) {
        if (c == '-') {
            if (current_part.empty()) {
                throw std::invalid_argument("Invalid identifier format: '-' cannot be consecutive or at the beginning.");
            }
            parts.push_back(current_part);
            current_part.clear();
        } else {
            current_part += c;
        }
    }
    parts.push_back(current_part);

    if (parts.size() > 10) {
        throw std::invalid_argument("Invalid identifier format: More than 10 parts.");
    }

    // Инкремент идентификатора
    bool overflow = false;
    for (int i = parts.size() - 1; i >= 0; --i) {
        std::string part = parts[i]; //create a copy of string

        std::string incremented_part = incrementPart(part);
        if (incremented_part == "A1" && !overflow) {
            overflow = true;
            parts[i] = incremented_part;

            if (i == 0) {
                // If this is first part after overflow, we need to add new part A1
                parts.insert(parts.begin(), "A1");
                if (parts.size() > 10) {
                    throw std::invalid_argument("Invalid identifier: Maximum length exceeded.");
                }
                break; // we added part, need to exit loop
            }
        } else {
            parts[i] = incremented_part;
            break;
        }
    }

    // Соединение частей в результирующий идентификатор
    std::string result;
    for (size_t i = 0; i < parts.size(); ++i) {
        result += parts[i];
        if (i < parts.size() - 1) {
            result += '-';
        }
    }
    return result;
}

/**
 * @brief Инкрементирует заданную часть идентификатора (A1, B2 и т.д.) и возвращает новую строку, если инкрементировано.
 *
 * @param part Часть идентификатора для инкрементации.
 * @return std::string Инкрементированная часть идентификатора.
 * @throws std::invalid_argument Если часть идентификатора имеет недопустимую длину.
 */
std::string IdentifierGenerator::incrementPart(const std::string& part) const {
    if (part.length() != 2) {
        throw std::invalid_argument("Invalid identifier part:" + part);
    }

    std::string temp_part = part;
    char& letter = temp_part[0];
    char& digit = temp_part[1];

    if (digit == '9') {
        digit = '1';
        if (letter == 'Z') {
            letter = 'A';
            return "A1";
        } else {
            letter++;
            // Skip forbidden characters
            while (letter == 'D' || letter == 'F' || letter == 'G' || letter == 'J' || letter == 'M' || letter == 'Q' || letter == 'V') {
                letter++;
            }
            return temp_part;
        }
    } else {
        digit++;
        return temp_part;
    }
}

