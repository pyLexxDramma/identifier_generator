#ifndef IDENTIFIER_GENERATOR_H
#define IDENTIFIER_GENERATOR_H

#include <string>

/**
 * @class IdentifierGenerator
 * @brief Класс для генерации идентификаторов.
 */
class IdentifierGenerator {
public:
    /**
     * @brief Генерирует следующий идентификатор на основе переданного.
     *
     * @param identifier Исходный идентификатор.
     * @return std::string Следующий идентификатор.
     * @throws std::invalid_argument Если идентификатор имеет недопустимый формат.
     */
    std::string GenerateNextIdentifier(const std::string &identifier) const;

private:
    /**
     * @brief Инкрементирует заданную часть идентификатора (A1, B2 и т.д.) и возвращает новую строку, если инкрементировано.
     *
     * @param part Часть идентификатора для инкрементации.
     * @return std::string Инкрементированная часть идентификатора.
     * @throws std::invalid_argument Если часть идентификатора имеет недопустимую длину.
     */
    std::string incrementPart(const std::string& part) const;
};

#endif // IDENTIFIER_GENERATOR_H
