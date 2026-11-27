#pragma once

namespace miit::algebra
{
    /**
     * @brief Абстрактный класс для генерации элементов матрицы.
     */
    class Generator
    {
    public:
        /**
         * @brief Виртуальный деструктор.
         */
        virtual ~Generator() = default;

        /**
         * @brief Генерирует следующее значение.
         * @return Сгенерированное значение.
         */
        virtual int generate() const = 0;
    };
}
