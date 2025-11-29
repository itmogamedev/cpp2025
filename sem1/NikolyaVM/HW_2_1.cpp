#include<iostream>

void sixteen (int number10) {
  std::cout << std::hex << number10 << std::dec << "\n";
};

void eight (int number10) {
  std::cout << std::oct << number10 << std::dec << "\n";
};

int main(){
  int number, num_sys;
  std::cout << "Please, input your number\n";
  std::cin >> number;
  std::cout << "Please, input desired number system (8 or 16)\n";
  std::cin >> num_sys;

  if (num_sys == 16)
    {
      sixteen (number);
    }

  if (num_sys ==8)
    {
      eight (number);
    }
  if (num_sys != 16 and num_sys != 8)
    {
      std::cout << "Invalid input, try again\n";
    }
}