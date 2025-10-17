#include <cmath>
#include <iostream>
// OKAK
void malenkayaBukvaVNachaleDTS(long long int n1, int b) {
  long long int k, l, c = 0;
  if (n1 < 0) {
    n1 = -n1;
    std::cout << "-";
  }
  k = n1;
  l = n1;
  while (l >= b) {
    l /= b;
    k = l;
    c++;
  }
  for (int i = c; i != 0; i--) {
    long long int div = pow(b, i);
    long long int per = n1 / div;

    if (per < 10) {
      std::cout << n1 / div;
    } else {
      switch (per) {
        case 10:
          std::cout << "A";
          break;

        case 11:
          std::cout << "B";
          break;

        case 12:
          std::cout << "C";
          break;

        case 13:
          std::cout << "D";
          break;

        case 14:
          std::cout << "E";
          break;

        case 15:
          std::cout << "F";
          break;
      }
    }
    n1 %= div;
    k = n1;
  }

  if (k < 10) {
    std::cout << k;
  } else {
    switch (k) {
      case 10:
        std::cout << "A";
        break;

      case 11:
        std::cout << "B";
        break;

      case 12:
        std::cout << "C";
        break;

      case 13:
        std::cout << "D";
        break;

      case 14:
        std::cout << "E";
        break;

      case 15:
        std::cout << "F";
        break;
    }
  }
}

int main() {
  long long int n, b;
  std::cin >> n >> b;
  if (b == 8) {
    std::cout << "oct: ";
    malenkayaBukvaVNachaleDTS(n, 8);
  }
  else if (b == 16) {
    std::cout << "hex: ";
    malenkayaBukvaVNachaleDTS(n, 16);
  } else {
    std::cout << "error!";
  }
  
}