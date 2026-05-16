#include <iostream>
#include "Start_project.h"
#include "Vec3.h"

void Project::strtProject() {
  Vec3 a(1, 2, 3), b(4, 5, 6);
  std::cout << "Вектор A: (" << a.x << "," << a.y << "," << a.z << ")\n";
  std::cout << "Вектор B: (" << b.x << "," << b.y << "," << b.z << ")\n";
  std::cout << "A+B = " << a + b << "\n";
  std::cout << "A-B = " << a - b << "\n";
  std::cout << "Умножение на скаляр: 3A= " << a * 3 << "\n";
  std::cout << "Скалярное произведение: A*B= " << a * b << "\n";
  std::cout << "Векторное произведение: AxB = " << cross(a, b) << "\n";
  std::cout << "Длина A = " << a.length() << "\n";
  std::cout << "Нормализация B = " << b.normalize() << "\n";
}
