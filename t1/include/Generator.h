#pragma once
namespace miit::algebra {
/**
 * @brief Базовый интерфейс генератора целых чисел.
 */
class Generator {
public:
    /** @brief Уничтожает генератор через базовый указатель. */
    virtual ~Generator();
    /** @brief Получает очередное значение. @return Сгенерированное целое число. */
    virtual int generate() = 0;
};
}
