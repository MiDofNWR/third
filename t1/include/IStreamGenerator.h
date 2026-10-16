#pragma once
#include "Generator.h"
#include <istream>
namespace miit::algebra {
/**
 * @brief Генератор, считывающий целые числа из входного потока.
 */
class IStreamGenerator final : public Generator {
private:
    /** @brief Поток, из которого считываются значения. */
    std::istream& input_;
public:
    /**
     * @brief Создаёт генератор, использующий заданный поток.
     * @param input Поток для чтения целых чисел.
     */
    explicit IStreamGenerator(std::istream& input);
    /**
     * @brief Считывает очередное значение из потока.
     * @return Считанное целое число.
     * @throw std::runtime_error Если число не удалось прочитать.
     */
    int generate() override;
};
}
