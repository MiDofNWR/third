#include <cstdlib>
#include <clocale>
#include <iostream>
#include <memory>

#include "../include/ConstantGenerator.h"
#include "../include/IStreamGenerator.h"
#include "../include/Matrix.h"
#include "../include/RandomGenerator.h"
#include "../include/Task1.h"
#include "../include/Task2.h"
#include "../include/ZeroGenerator.h"

/**
 * @brief Варианты выбора способа заполнения матрицы.
 */
enum fill
{
	one = 1, two, three, four
};

/**
 * @brief Варианты выбора действия.
 */
enum choice
{
  first = 1, second
};

/**
 * @brief Функция проверки ввода.
 * @return Введённое целое число.
 * @throw std::runtime_error Если ввод некорректен.
 */
int getValue();

/**
 * @brief Точка входа в программу.
 */
int main()
{
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    try
    {
        std::cout << "Введите количество строк матрицы:\n";
        int rows = getValue();
        std::cout << "Введите количество столбцов матрицы:\n";
        int cols = getValue();
        if (rows <= 0 || cols <= 0)
        {
            std::cerr << "Размеры матрицы должны быть положительными.\n";
            return EXIT_FAILURE;
        }

        std::cout << "Выберите способ заполнения:\n"
                  << one << " - Вручную с клавиатуры \n"
                  << two << " - Случайными числами \n"
                  << three << " - Нулями \n"
                  << four << " - Константным значением \n";

        int fill_choice = getValue();
		
		miit::algebra::Matrix matrix(rows, cols);

        switch (fill_choice)
        {
        case one:
          {
            std::cout << "Введите элементы матрицы построчно:\n";
			miit::algebra::IStreamGenerator generator(std::cin);
            matrix.fill(generator);
            break;
          }
        case two:
        {
            std::cout << "Введите минимальную и максимальную границы:\n";
            int min_val = getValue();
			int max_val = getValue();
			miit::algebra::RandomGenerator generator(min_val, max_val);
            matrix.fill(generator);
            break;
        }
        case three:
        {
			miit::algebra::ZeroGenerator generator;
			matrix.fill(generator);
            break;
        }
        case four:
        {
            std::cout << "Введите константу для заполнения:\n";
            int const_val = getValue();
			miit::algebra::ConstantGenerator generator(const_val);
			matrix.fill(generator);
            break;
        }
        default:
            std::cerr << "Неверный выбор способа заполнения.\n";
            return EXIT_FAILURE;
        }
		
        std::cout << "\nИсходная матрица:\n" << matrix;

        std::cout << "\nВыберите действие:\n"
                  << first << " - Заменить нулевые элементы максимальным по модулю элементом матрицы\n"
                  << second << " - Вставить нулевой столбец после каждого столбца с максимальным по модулю элементом \n";

        int op_choice = getValue();

        switch (op_choice)
        {
          case first:
          {
            miit::algebra::Task1 task(matrix);
            std::cout << "\nРезультат:\n" << task.Solve();
            break;
          }
          case second:
          {
            miit::algebra::Task2 task(matrix);
            std::cout << "\nРезультат:\n" << task.Solve();
            break;
          }
          default:
            std::cerr << "Неверный выбор операции.\n";
            return EXIT_FAILURE;
        }
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Ошибка: " << ex.what() << '\n';
        return EXIT_FAILURE;
    }

    return 0;
}

int getValue()
{
    int value = 0;

    if (std::cin >> value)
    {
        return value;
    }

    throw std::runtime_error("Ошибка ввода.");
}
