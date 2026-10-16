#pragma once

#include "Generator.h"

#include <algorithm>
#include <cstddef>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace miit::algebra {

template<typename T>
/**
 * @brief Шаблонный класс прямоугольной матрицы.
 * @tparam T Тип элементов матрицы.
 */
class Matrix {
private:
    /** @brief Двумерный контейнер со строками матрицы. */
    std::vector<std::vector<T>> data_;

    /**
     * @brief Проверяет, что все строки имеют одинаковую длину.
     * @throw std::invalid_argument Если матрица не является прямоугольной.
     */
    void validateRectangular() const {
        if (data_.empty()) return;
        const std::size_t width = data_.front().size();
        for (const auto& row : data_) {
            if (row.size() != width) throw std::invalid_argument("Matrix rows must have equal length");
        }
    }

public:
    /** @brief Создаёт пустую матрицу. */
    Matrix() = default;
    /**
     * @brief Создаёт матрицу заданного размера.
     * @param rows Количество строк.
     * @param columns Количество столбцов.
     * @param value Начальное значение элементов.
     */
    Matrix(std::size_t rows, std::size_t columns, const T& value = T{})
        : data_(rows, std::vector<T>(columns, value)) {}
    /**
     * @brief Создаёт матрицу из готовых строк.
     * @param values Значения строк матрицы.
     * @throw std::invalid_argument Если строки имеют разную длину.
     */
    explicit Matrix(const std::vector<std::vector<T>>& values) : data_(values) { validateRectangular(); }
    /** @brief Создаёт копию другой матрицы. */
    Matrix(const Matrix&) = default;
    /** @brief Перемещает данные другой матрицы в новый объект. */
    Matrix(Matrix&&) noexcept = default;
    /** @brief Уничтожает матрицу. */
    ~Matrix() = default;
    /** @brief Копирует данные другой матрицы. */
    Matrix& operator=(const Matrix&) = default;
    /** @brief Перемещает данные другой матрицы. */
    Matrix& operator=(Matrix&&) noexcept = default;

    /**
     * @brief Возвращает строку матрицы по индексу.
     * @param row Индекс строки.
     * @return Ссылка на выбранную строку.
     */
    std::vector<T>& operator[](std::size_t row) {
        return data_[row];
    }

    /**
     * @brief Возвращает строку неизменяемой матрицы по индексу.
     * @param row Индекс строки.
     * @return Константная ссылка на выбранную строку.
     */
    const std::vector<T>& operator[](std::size_t row) const {
        return data_[row];
    }

    /**
     * @brief Создаёт матрицу со сдвигом строк влево.
     * @param positions Количество позиций для сдвига.
     * @return Новая матрица со сдвинутыми строками.
     */
    Matrix operator<<(std::size_t positions) const {
        Matrix result(*this);
        for (auto& row : result.data_) {
            if (!row.empty()) {
                const std::size_t shift = positions % row.size();
                std::rotate(row.begin(), row.begin() + static_cast<std::ptrdiff_t>(shift), row.end());
            }
        }
        return result;
    }

    /**
     * @brief Создаёт матрицу со сдвигом строк вправо.
     * @param positions Количество позиций для сдвига.
     * @return Новая матрица со сдвинутыми строками.
     */
    Matrix operator>>(std::size_t positions) const {
        Matrix result(*this);
        for (auto& row : result.data_) {
            if (!row.empty()) {
                const std::size_t shift = positions % row.size();
                std::rotate(row.rbegin(), row.rbegin() + static_cast<std::ptrdiff_t>(shift), row.rend());
            }
        }
        return result;
    }

    /** @brief Возвращает количество строк. @return Число строк матрицы. */
    std::size_t rows() const noexcept { return data_.size(); }
    /** @brief Возвращает количество столбцов. @return Число столбцов матрицы. */
    std::size_t columns() const noexcept { return data_.empty() ? 0U : data_.front().size(); }
    /** @brief Проверяет отсутствие строк или столбцов. @return true для пустой матрицы. */
    bool empty() const noexcept { return rows() == 0U || columns() == 0U; }

    /**
     * @brief Заполняет все элементы матрицы значениями генератора.
     * @param generator Генератор очередных значений.
     */
    void fill(Generator& generator) {
        for (auto& row : data_) for (auto& value : row) value = static_cast<T>(generator.generate());
    }

    /**
     * @brief Вставляет строку перед указанной позицией.
     * @param index Индекс вставки.
     * @param row Значения новой строки.
     * @throw std::out_of_range Если индекс недопустим.
     * @throw std::invalid_argument Если длина строки не совпадает с числом столбцов.
     */
    void insertRow(std::size_t index, const std::vector<T>& row) {
        if (index > rows()) throw std::out_of_range("Row insertion index is out of range");
        if (!data_.empty() && row.size() != columns()) throw std::invalid_argument("Inserted row has wrong size");
        data_.insert(data_.begin() + static_cast<std::ptrdiff_t>(index), row);
    }

    /**
     * @brief Удаляет строку по индексу.
     * @param index Индекс удаляемой строки.
     * @throw std::out_of_range Если индекс недопустим.
     */
    void removeRow(std::size_t index) {
        if (index >= rows()) throw std::out_of_range("Row removal index is out of range");
        data_.erase(data_.begin() + static_cast<std::ptrdiff_t>(index));
    }

    /**
     * @brief Вставляет столбец перед указанной позицией.
     * @param index Индекс вставки.
     * @param column Значения нового столбца.
     * @throw std::logic_error Если матрица пуста.
     * @throw std::out_of_range Если индекс недопустим.
     * @throw std::invalid_argument Если высота столбца не совпадает с числом строк.
     */
    void insertColumn(std::size_t index, const std::vector<T>& column) {
        if (empty()) throw std::logic_error("Cannot insert a column into an empty matrix");
        if (index > columns()) throw std::out_of_range("Column insertion index is out of range");
        if (column.size() != rows()) throw std::invalid_argument("Inserted column has wrong size");
        for (std::size_t row = 0; row < rows(); ++row) {
            data_[row].insert(data_[row].begin() + static_cast<std::ptrdiff_t>(index), column[row]);
        }
    }

    /**
     * @brief Удаляет столбец по индексу.
     * @param index Индекс удаляемого столбца.
     * @throw std::out_of_range Если индекс недопустим.
     */
    void removeColumn(std::size_t index) {
        if (index >= columns()) throw std::out_of_range("Column removal index is out of range");
        for (auto& row : data_) row.erase(row.begin() + static_cast<std::ptrdiff_t>(index));
    }

    /**
     * @brief Преобразует матрицу в текст с пробелами между элементами.
     * @return Строковое представление матрицы.
     */
    std::string toString() const {
        std::ostringstream out;
        for (std::size_t row = 0; row < rows(); ++row) {
            for (std::size_t column = 0; column < columns(); ++column) {
                if (column != 0U) out << ' ';
                out << data_[row][column];
            }
            if (row + 1U != rows()) out << '\n';
        }
        return out.str();
    }
};

} // namespace miit::algebra
