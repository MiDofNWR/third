#include "../include/Matrix.h"
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <utility>

namespace miit::algebra
{
    Matrix::Matrix(int rows, int columns)
    {
        if (rows <= 0 || columns <= 0)
            throw std::runtime_error("Размеры матрицы должны быть положительными.");
        data.assign(static_cast<size_t>(rows), std::vector<int>(static_cast<size_t>(columns), 0));
    }

    Matrix::Matrix(std::vector<std::vector<int>> elements) : data(std::move(elements))
    {
        if (data.empty() || data.front().empty())
            throw std::runtime_error("Матрица должна содержать хотя бы одну строку и один столбец.");
        const size_t columns = data.front().size();
        for (const auto& row : data)
            if (row.size() != columns)
                throw std::runtime_error("Все строки матрицы должны иметь одинаковую длину.");
    }

    bool Matrix::operator==(const Matrix& other) const { return data == other.data; }
    bool Matrix::operator!=(const Matrix& other) const { return !(*this == other); }

    Matrix Matrix::operator+(const Matrix& other) const
    {
        if (rowsCount() != other.rowsCount() || columnsCount() != other.columnsCount())
            throw std::runtime_error("Нельзя складывать матрицы разных размеров.");
        if (data.empty()) return Matrix();
        Matrix result(static_cast<int>(rowsCount()), static_cast<int>(columnsCount()));
        for (size_t i = 0; i < rowsCount(); ++i)
            for (size_t j = 0; j < columnsCount(); ++j)
                result.data[i][j] = data[i][j] + other.data[i][j];
        return result;
    }

    Matrix Matrix::operator-(const Matrix& other) const
    {
        if (rowsCount() != other.rowsCount() || columnsCount() != other.columnsCount())
            throw std::runtime_error("Нельзя вычитать матрицы разных размеров.");
        if (data.empty()) return Matrix();
        Matrix result(static_cast<int>(rowsCount()), static_cast<int>(columnsCount()));
        for (size_t i = 0; i < rowsCount(); ++i)
            for (size_t j = 0; j < columnsCount(); ++j)
                result.data[i][j] = data[i][j] - other.data[i][j];
        return result;
    }

    Matrix Matrix::operator*(const Matrix& other) const
    {
        if (columnsCount() != other.rowsCount())
            throw std::runtime_error("Число столбцов первой матрицы должно быть равно числу строк второй.");
        if (data.empty() || other.data.empty()) return Matrix();
        Matrix result(static_cast<int>(rowsCount()), static_cast<int>(other.columnsCount()));
        for (size_t i = 0; i < rowsCount(); ++i)
            for (size_t j = 0; j < other.columnsCount(); ++j)
                for (size_t k = 0; k < columnsCount(); ++k)
                    result.data[i][j] += data[i][k] * other.data[k][j];
        return result;
    }

    int* Matrix::operator[](int row)
    {
        if (row < 0 || static_cast<size_t>(row) >= data.size())
            throw std::runtime_error("Индекс выходит за пределы матрицы.");
        return data[static_cast<size_t>(row)].data();
    }
    const int* Matrix::operator[](int row) const
    {
        if (row < 0 || static_cast<size_t>(row) >= data.size())
            throw std::runtime_error("Индекс выходит за пределы матрицы.");
        return data[static_cast<size_t>(row)].data();
    }

    const int& Matrix::minimum() const
    {
        if (data.empty()) throw std::runtime_error("Матрица пуста.");
        const int* value = &data[0][0];
        for (const auto& row : data)
            for (const int& element : row)
                if (element < *value) value = &element;
        return *value;
    }
    int& Matrix::minimum() { return const_cast<int&>(static_cast<const Matrix&>(*this).minimum()); }
    const int& Matrix::maximum() const
    {
        if (data.empty()) throw std::runtime_error("Матрица пуста.");
        const int* value = &data[0][0];
        for (const auto& row : data)
            for (const int& element : row)
                if (element > *value) value = &element;
        return *value;
    }
    int& Matrix::maximum() { return const_cast<int&>(static_cast<const Matrix&>(*this).maximum()); }
    size_t Matrix::rowsCount() const { return data.size(); }
    size_t Matrix::columnsCount() const { return data.empty() ? 0 : data.front().size(); }
    void Matrix::fill(const Generator& generator)
    {
        for (auto& row : data)
            for (int& element : row) element = generator.generate();
    }
    void Matrix::removeColumn(size_t columnIndex)
    {
        if (columnIndex >= columnsCount() || columnsCount() <= 1)
            throw std::runtime_error("Некорректный индекс для удаления столбца.");
        for (auto& row : data) row.erase(row.begin() + static_cast<std::ptrdiff_t>(columnIndex));
    }
    std::string Matrix::toString() const
    {
        std::ostringstream output;
        for (const auto& row : data)
        {
            output << "[ ";
            for (int element : row) output << std::setw(4) << element << " ";
            output << "]\n";
        }
        return output.str();
    }
    std::ostream& operator<<(std::ostream& output, const Matrix& matrix)
    {
        return output << matrix.toString();
    }
    std::istream& operator>>(std::istream& input, Matrix& matrix)
    {
        for (auto& row : matrix.data)
            for (int& element : row)
                if (!(input >> element)) throw std::runtime_error("Ошибка ввода элементов матрицы из потока.");
        return input;
    }
}
