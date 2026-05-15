#include <iostream>
#include <stdexcept>

#include "Vec3.h"

int main() {
  try {
    Vec3 first(1.0, 2.0, 3.0);
    Vec3 second(4.0, 5.0, 6.0);

    Vec3 sum = first + second;
    Vec3 difference = first - second;
    Vec3 scaled = first * 2.0;
    double dot = dotProduct(first, second);
    Vec3 cross = crossProduct(first, second);
    double first_length = first.length();
    Vec3 normalized = first.normalize();

    std::cout << "first = " << first << std::endl;
    std::cout << "second = " << second << std::endl;
    std::cout << "first + second = " << sum << std::endl;
    std::cout << "first - second = " << difference << std::endl;
    std::cout << "first * 2 = " << scaled << std::endl;
    std::cout << "dot product = " << dot << std::endl;
    std::cout << "cross product = " << cross << std::endl;
    std::cout << "first length = " << first_length << std::endl;
    std::cout << "normalized first = " << normalized << std::endl;
  } catch (const std::exception& error) {
    std::cout << "Error: " << error.what() << std::endl;
  }

  return 0;
}
