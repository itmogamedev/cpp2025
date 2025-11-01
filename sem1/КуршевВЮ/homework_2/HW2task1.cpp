#include <iostream>
#include <string>

void toEightAndSixteen(int num)
{
  const char alf[17] = { "0123456789ABCDEF" };
  std::string num_8{};
  int temp = num;

  while (num > 0)
  {
    num_8 = {alf[num % 8] + num_8};
    num /= 8;
  }
  std::cout << "8: " << num_8 << std::endl;

  num = temp;
  std::string num_16{};

  while (num > 0)
  {
    num_16 = {alf[num % 16] + num_16};
    num /= 16;
  }

  std::cout << "16: " << num_16;
}

int main()
{
  int num;
  std::cout << "Input number: ";
  std::cin >> num;
  toEightAndSixteen(num);
}