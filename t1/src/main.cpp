#include "ConstantGenerator.h"
#include "IStreamGenerator.h"
#include "RandomGenerator.h"
#include "Task1.h"
#include "Task2.h"
#include "ZeroGenerator.h"
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
using namespace miit::algebra;

enum class FillChoice { Keyboard = 1, Random, Zero, Constant };
enum class Action { First = 1, Second, Both };

/**
 * @brief Считывает значение указанного типа.
 * @tparam T Тип считываемого значения.
 * @param prompt Текст приглашения для пользователя.
 * @return Корректно считанное значение.
 * @throw std::runtime_error Если значение не удалось считать.
 */
template<typename T>
T readValue(const std::string& prompt) {
    std::cout << prompt;
    T value{};
    if (!(std::cin >> value)) throw std::runtime_error("Некорректный ввод");
    return value;
}

/**
 * @brief Точка входа в консольную программу работы с матрицами.
 * @return Код завершения программы: 0 при успехе, 1 при ошибке.
 */
int main() {
    try {
        const auto rowCount = readValue<long long>("Количество строк (> 0): ");
        const auto columnCount = readValue<long long>("Количество столбцов (> 0): ");
        if (rowCount <= 0 || columnCount <= 0)
            throw std::invalid_argument("Размеры матрицы должны быть положительными");
        const auto rows = static_cast<std::size_t>(rowCount);
        const auto columns = static_cast<std::size_t>(columnCount);

        std::cout << "Заполнение: 1 — с клавиатуры, 2 — случайными числами, 3 — нулями, 4 — постоянным числом\n";
        const auto fillChoice = static_cast<FillChoice>(readValue<int>("Выбор: "));
        std::unique_ptr<Generator> generator;
        switch (fillChoice) {
        case FillChoice::Keyboard:
            std::cout << "Введите " << rows * columns << " целых чисел:\n";
            generator = std::make_unique<IStreamGenerator>(std::cin);
            break;
        case FillChoice::Random: {
            const int minimum = readValue<int>("Минимум: ");
            const int maximum = readValue<int>("Максимум: ");
            generator = std::make_unique<RandomGenerator>(minimum, maximum);
            break;
        }
        case FillChoice::Zero:
            generator = std::make_unique<ZeroGenerator>();
            break;
        case FillChoice::Constant:
            generator = std::make_unique<ConstantGenerator>(readValue<int>("Постоянное значение: "));
            break;
        default:
            std::cerr << "Неизвестный способ заполнения\n";
            return 1;
        }

        Matrix<int> original(rows, columns);
        original.fill(*generator);
        std::cout << "Исходная матрица:\n" << original.toString() << '\n';
        std::cout << "\n1 — первое преобразование, 2 — второе преобразование, 3 — оба преобразования\n";
        const auto action = static_cast<Action>(readValue<int>("Действие: "));
        const auto runFirst = [&original]() {
            Task1 task(original);
            task.solve();
            std::cout << "Результат задания 1:\n" << task.getMatrix().toString() << '\n';
        };
        const auto runSecond = [&original]() {
            Task2 task(original);
            task.solve();
            std::cout << "Результат задания 2:\n" << task.getMatrix().toString() << '\n';
        };
        switch (action) {
        case Action::First:
            runFirst();
            break;
        case Action::Second:
            runSecond();
            break;
        case Action::Both:
            runFirst();
            runSecond();
            break;
        default:
            throw std::invalid_argument("Неизвестное действие");
        }
    } catch (const std::exception& error) {
        std::cerr << "Ошибка: " << error.what() << '\n';
        return 1;
    }
    return 0;
}
