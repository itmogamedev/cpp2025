#include <iostream>
#include <string>

int s8(int a) {
  int oct = 1;
  int res = 0;
  int reminder;
  while (a > 0) {
    reminder = a % 8;
    res += reminder * oct;
    a = a / 8;
    oct = oct * 10;
  }
  return res;
}


int main() {
  setlocale(LC_ALL, "RU");
  int num;
  int num2;
  int SysSchislen;
  std::cout
      << "Выберите число которое хотите перевести в другую систему счисления"
      << std::endl;
  std::cout << "---------------------------------------------------------------"
               "----------------------------"
            << std::endl;
  std::cin >> num;
  std::cout << "---------------------------------------------------------------"
               "----------------------------"
            << std::endl;
  std::cout << "В какую систему счисления вы хотите перевести число из "
               "десятичной системы счисления?(8/16)"
            << std::endl;
  std::cout << "---------------------------------------------------------------"
               "----------------------------"
            << std::endl;
  std::cin >> SysSchislen;
  if (SysSchislen == 8) {
    num2 = s8(num);
    std::cout << "Число " << num << " было переведено в " << SysSchislen
              << " систему счисления, "
              << "в этой системе счисления оно равняется " << num2;
  }
  if (SysSchislen == 16) {
    std::cout << "Число " << num << " было переведено в " << SysSchislen
              << " систему счисления, "
              << "в этой системе счисления оно равняется " << std::hex << num;
  }

  return 0;
}
