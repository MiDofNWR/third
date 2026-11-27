#pragma once
#include "Generator.h"

namespace miit::algebra
{
    /**
     * @brief Генератор, возвращающий фиксированное значение.
     */
    class ConstantGenerator : public Generator
    {
    private:
        int value;

    public:
        /**
         * @brief Конструктор генератора константы.
         * @param value Константа для заполнения.
         */
        explicit ConstantGenerator(const int value);

        /**
         * @brief Возвращает заданную константу.
         * @return Константное число.
         */
        int generate() const override;
    };
}
