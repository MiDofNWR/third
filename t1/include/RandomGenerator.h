#pragma once
#include "Generator.h"
#include <random>
namespace miit::algebra {
/**
 * @brief Генератор случайных целых чисел в заданном диапазоне.
 */
class RandomGenerator final : public Generator {
private:
    /** @brief Движок генерации псевдослучайных чисел. */
    std::mt19937 engine_;
    /** @brief Равномерное распределение значений в выбранном диапазоне. */
    std::uniform_int_distribution<int> distribution_;
public:
    /**
     * @brief Создаёт генератор случайных чисел.
     * @param minimum Нижняя граница диапазона.
     * @param maximum Верхняя граница диапазона.
     * @throw std::invalid_argument Если minimum больше maximum.
     */
    RandomGenerator(int minimum, int maximum);
    /**
     * @brief Генерирует случайное число из заданного диапазона.
     * @return Случайное целое число.
     */
    int generate() override;
};
}
