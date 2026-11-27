#pragma once
#include "Generator.h"
#include <iostream>

namespace miit::algebra
{
    /**
     * @brief Генератор элементов из потока ввода.
     */
    class IStreamGenerator : public Generator
    {
    private:
        /**
         * @param in Поток ввода (std::cin).
         */
        std::istream& in;

    public:
        /**
         * @brief Конструктор генератора потока ввода.
         * @param in Поток ввода (std::cin).
         */
        explicit IStreamGenerator(std::istream& in = std::cin);

        /**
         * @brief Считывает и возвращает следующее число из потока.
         * @return Считанное число.
         */
        int generate() const override;
    };
}
