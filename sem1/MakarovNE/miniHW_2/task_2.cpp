#include <iostream>

void thr(int x) {
  int step = 0;

  if (x < 1) {
    std::cout << "������� �� ����������� �����\n";
    return;
  }

  for (step; x != 1; step++) {
    bool evenness = (x % 2) == 0;

    if (evenness) {
      x = x / 2;
    }

    else {
      x = (3 * x + 1) / 2;
    }

    std::cout << x << std::endl;
  }
  std::cout << "��������� �� " << step << " �����" << std::endl;
}

int main() {
  system("chcp 1251 > nul");
  int number = 0;

  while (true) {
    std::cout << "������ ����� ��� �������� �������� �������: ";
    std::cin >> number;
    thr(number);
  }
}
