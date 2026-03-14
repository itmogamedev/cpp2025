#include "vector_small.h"

void sborko() {
  Vec3 a(5, 2, 3);
  Vec3 b(6, 7, 6);

  std::cout << "Vector a: " << a << std::endl;
  std::cout << "Vector b: " << b << std::endl;

  std::cout << "\n~~~ SUMMA vectorov\n";
  Vec3 sum = a + b;
  std::cout << "a + b = " << sum << std::endl;

  std::cout << "\n~~~ RAZNOST vectorov\n";
  Vec3 diff = a - b;
  std::cout << "a - b = " << diff << std::endl;

  std::cout << "\n~~~ MULTIPLY const\n";
  Vec3 scaled = a * 3;
  std::cout << "a * 3 = " << scaled << std::endl;

  std::cout << "\n~~~ SCALAR multiply\n";
  float dot = a.scalarMulti(b);
  std::cout << "a • b = " << dot << std::endl;

  std::cout << "\n~~~ VECTOR multiply\n";
  Vec3 cross = a.vectorMulti(b);
  std::cout << "a x b = " << cross << std::endl;

  std::cout << "\n~~~ Vector LENGTH\n";
  std::cout << "|a| = " << a.vectorLength() << std::endl;
  std::cout << "|b| = " << b.vectorLength() << std::endl;

  std::cout << "\n~~~ Normalization\n";
  Vec3 norm = a.normal();
  Vec3 norm2 = b.normal();
  std::cout << "norm vector a = " << norm << std::endl;
  std::cout << "norm vector b = " << norm2 << std::endl;

  std::cout << "\n YAY !\n";
}
