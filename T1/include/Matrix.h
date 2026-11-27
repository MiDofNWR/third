#pragma once

#include "Generator.h"
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

namespace miit::algebra
{
    // Прямоугольная матрица целых чисел с хранением строк в векторах.
    class Matrix
    {
    private:
        std::vector<std::vector<int>> data;

    public:
        Matrix() = default;
        Matrix(const int rows, const int columns);
        explicit Matrix(std::vector<std::vector<int>> elements);

        bool operator==(const Matrix& other) const;
        bool operator!=(const Matrix& other) const;
        Matrix operator+(const Matrix& other) const;
        Matrix operator-(const Matrix& other) const;
        Matrix operator*(const Matrix& other) const;

        int* operator[](const int row);
        const int* operator[](const int row) const;
        int& minimum();
        const int& minimum() const;
        int& maximum();
        const int& maximum() const;
        size_t rowsCount() const;
        size_t columnsCount() const;
        void fill(const Generator& generator);
        void removeColumn(const size_t columnIndex);
        std::string toString() const;

        friend std::ostream& operator<<(std::ostream& output, const Matrix& matrix);
        friend std::istream& operator>>(std::istream& input, Matrix& matrix);
    };
}
