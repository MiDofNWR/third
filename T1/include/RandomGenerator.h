#pragma once
#include "Generator.h"
#include <random>

namespace miit::algebra
{
    /**
     * @brief Генератор случайных чисел в заданном диапазоне.
     */
    class RandomGenerator : public Generator
    {
    private:
        mutable std::uniform_int_distribution<int> distribution;
        mutable std::mt19937 generator;

    public:
        /**
         * @brief Конструктор генератора случайных чисел.
         * @param min Минимальная граница диапазона.
         * @param max Максимальная граница диапазона.
         */
        RandomGenerator(const int min, const int max);

        /**
         * @brief Сгенерировать случайное число из диапазона [min, max].
         * @return Случайное целое число.
         */
        int generate() const override;
    };
}
