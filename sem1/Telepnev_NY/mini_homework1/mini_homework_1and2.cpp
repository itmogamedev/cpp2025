#include <iostream>
#include <string>

double calculateSquareArea(int side) { return side * side; }

double calculateTrapeziaArea(int firstBasis, int secondBasis, int height) {
  return 0.5 * (firstBasis + secondBasis) * height;
}

int inputSquareData() {
  int side;
  std::cout << "Введите сторону квадрата = ";
  std::cin >> side;
  return side;
}

void inputTrapeziaData(int& firstBasis, int& secondBasis, int& height) {
  std::cout << "Введите значение первого основания = ";
  std::cin >> firstBasis;

  std::cout << "Введите значения второго основания = ";
  std::cin >> secondBasis;

  std::cout << "Введите значение высоты = ";
  std::cin >> height;
}

void printResult(const std::string& figureName, const std::string& parameters,
                 double area) {
  std::cout << "\n______Результат______" << std::endl;
  std::cout << "Фигура = " << figureName << std::endl;
  std::cout << parameters;
  std::cout << "Площадь = " << area << std::endl;
  std::cout << "_____________________" << std::endl;
}

int main() {
  setlocale(LC_ALL, "Russian");
  int choice;

  std::cout << "Выберите для какой фигуры ищем площадь." << std::endl
            << "Квадрат - 1 | Трапеция - 2" << std::endl;
  std::cin >> choice;

  switch (choice) {
    case 1: {
      int side = inputSquareData();
      if (side <= 0) {
        std::cout << "Ошибка. Значение должны быть положительны" << std::endl;
        break;
      }
      double area = calculateSquareArea(side);
      std::string parameters = "Сторона = " + std::to_string(side) + '\n';
      printResult("Квадрат", parameters, area);
      break;
    }
    case 2: {
      int firstBasis, secondBasis, height;
      inputTrapeziaData(firstBasis, secondBasis, height);

      if (firstBasis <= 0 || secondBasis <= 0 || height <= 0) {
        std::cout << "Ошибка. Все значения должны быть положительны"
                  << std::endl;
        break;
      }
      double area = calculateTrapeziaArea(firstBasis, secondBasis, height);
      std::string parameters = "Основания = " + std::to_string(firstBasis) +
                               " и " + std::to_string(secondBasis) +
                               " Высота = " + std::to_string(height) + '\n';

      printResult("Трапеция", parameters, area);
      break;
    }

    default:
      std::cout << "Ошибка. Выборка только из двух вариантов (1 или 2)"
                << std::endl;
      break;
  }
  return 0;
}
