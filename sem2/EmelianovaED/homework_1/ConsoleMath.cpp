#include <iostream>

#include "MiniLib.h"
void tastingVec3(Vec3& vec1, Vec3& vec2) {
  std::cout << "Тестирование библиотеки Vec3" << std::endl << std::endl;
  std::cout << "Вектор a: " << vec1 << std::endl;
  std::cout << "Вектор b: " << vec2 << std::endl << std::endl;

  Vec3 sum_vec = vec1 + vec2;
  std::cout << "a + b = " << sum_vec << std::endl;

  Vec3 diff_vec = vec1 - vec2;
  std::cout << "a - b = " << diff_vec << std::endl;

  Vec3 mul_right = vec1 * 2.5;
  Vec3 mul_left = 0.5 * vec1;
  std::cout << "a * 2.5 = " << mul_right << std::endl;
  std::cout << "0.5 * a = " << mul_left << std::endl;

  double dot_product = vec1.dotProduct(vec2);
  std::cout << "Скалярное произведение a·b = " << dot_product << std::endl;

  Vec3 vec_product = vec1.vectorProduct(vec2);
  std::cout << "Векторное произведение a x b = " << vec_product << std::endl;

  double len_vec = vec1.lengthVec();
  std::cout << "Длина вектора a: " << len_vec << std::endl;

  Vec3 norm_vec = vec1.normalized();
  std::cout << "Нормализованный a (копия): " << norm_vec << std::endl;
  std::cout << "Длина нормализованного: " << norm_vec.lengthVec() << std::endl;

  vec1.normalize();
  std::cout << "a после собственной нормализации: " << vec2 << std::endl;
}
int main() {
  setlocale(LC_ALL, "RUS");
  Vec3 vector_one(1.0, 2.0, 3.0);
  Vec3 vector_two(4.0, 5.0, 6.0);

  tastingVec3(vector_one, vector_two);

  return 0;
}
