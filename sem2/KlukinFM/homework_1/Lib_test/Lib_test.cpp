#include <windows.h>

#include <iostream>

#include "vector3D.h"

void Run_test(Vector3D v1, Vector3D v2) {
  double scalar = rand() % 10;
  std::cout << "Первый вектор " << v1 << std::endl;
  std::cout << "Второй вектор " << v2 << std::endl;
  std::cout << "Скаляр = " << scalar << std::endl;
  std::cout << "Сумма векторов " << v1 + v2 << std::endl;
  std::cout << "Разность Векторов " << v1 - v2 << std::endl;
  std::cout << "Умножение первого вектора на скаляр " << scalar * v1
            << std::endl;
  std::cout << "Умножение второго вектора на скаляр " << v2 * scalar
            << std::endl;
  std::cout << "Скалярное произведение векторов " << v1.dotProd(v2)
            << std::endl;
  std::cout << "Векторное произведение векторов " << v1.vecProd(v2)
            << std::endl;
  std::cout << "Длина первого вектора " << v1.lenghtVec() << std::endl;
  std::cout << "Длина второго вектора " << v2.lenghtVec() << std::endl;
  std::cout << "Нормализация первого вектора " << v1.normVec() << std::endl;
  std::cout << "Нормализация второго вектора " << v2.normVec() << std::endl;
}

int main() {
  SetConsoleOutputCP(CP_UTF8);
  srand(time(NULL));
  Vector3D vec1(rand() % 101, rand() % 101, rand() % 101),
      vec2(rand() % 101, rand() % 101, rand() % 101);
  Run_test(vec1, vec2);
  return 0;
}
