#include "ConstantGenerator.h"
#include "IStreamGenerator.h"
#include "RandomGenerator.h"
#include "Task1.h"
#include "Task2.h"
#include "ZeroGenerator.h"
#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>
using namespace miit::algebra;

/**
 * @brief Считывает значение указанного типа и повторяет запрос при неверном вводе.
 * @tparam T Тип считываемого значения.
 * @param prompt Текст приглашения для пользователя.
 * @return Корректно считанное значение.
 * @throw std::runtime_error Если входной поток завершился.
 */
template<typename T>
T readValue(const char* prompt) {
    for (;;) {
        std::cout << prompt;
        T value{};
        if (std::cin >> value) return value;
        if (std::cin.eof()) throw std::runtime_error("Ввод завершён");
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Некорректное значение. Попробуйте ещё раз.\n";
    }
}

/**
 * @brief Точка входа в консольную программу работы с матрицами.
 * @return Код завершения программы: 0 при успехе, 1 при ошибке.
 */
int main() {
    try {
        std::size_t rows = 0U;
        std::size_t columns = 0U;
        while (rows == 0U) rows = readValue<std::size_t>("Количество строк (> 0): ");
        while (columns == 0U) columns = readValue<std::size_t>("Количество столбцов (> 0): ");

        std::cout << "Заполнение: 1 — с клавиатуры, 2 — случайными числами, 3 — нулями, 4 — постоянным числом\n";
        const int fillChoice = readValue<int>("Выбор: ");
        std::unique_ptr<Generator> generator;
        switch (fillChoice) {
        case 1:
            std::cout << "Введите " << rows * columns << " целых чисел:\n";
            generator = std::make_unique<IStreamGenerator>(std::cin);
            break;
        case 2: {
            const int minimum = readValue<int>("Минимум: ");
            const int maximum = readValue<int>("Максимум: ");
            generator = std::make_unique<RandomGenerator>(minimum, maximum);
            break;
        }
        case 3:
            generator = std::make_unique<ZeroGenerator>();
            break;
        case 4:
            generator = std::make_unique<ConstantGenerator>(readValue<int>("Постоянное значение: "));
            break;
        default:
            std::cerr << "Неизвестный способ заполнения\n";
            return 1;
        }

        Matrix<int> original(rows, columns);
        original.fill(*generator);
        std::cout << "Исходная матрица:\n" << original.toString() << '\n';
        for (;;) {
            std::cout << "\n0 — выход, 1 — первое преобразование, 2 — второе преобразование, 3 — оба преобразования\n";
            const int action = readValue<int>("Действие: ");
            if (action == 0) break;
            if (action == 1 || action == 3) {
                Task1 task(original);
                task.solve();
                std::cout << "Результат задания 1:\n" << task.getMatrix().toString() << '\n';
            }
            if (action == 2 || action == 3) {
                Task2 task(original);
                task.solve();
                std::cout << "Результат задания 2:\n" << task.getMatrix().toString() << '\n';
            }
            if (action < 1 || action > 3) std::cout << "Неизвестное действие\n";
        }
    } catch (const std::exception& error) {
        std::cerr << "Ошибка: " << error.what() << '\n';
        return 1;
    }
    return 0;
}
