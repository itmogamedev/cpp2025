#include <iostream>

class peremena {
 public:
  explicit peremena(int start_number) : current_number(start_number) {}

  void run() {
    while (current_number != 1) {
      std::cout << current_number << " -> ";
      if (isEven(current_number)) {
        current_number = current_number / 2;
      } else {
        current_number = (current_number * 3 + 1) / 2;
      }
    }
    std::cout << "1" << std::endl;
    std::cout << "Hypothesis is proven" << std::endl;
  }

 private:
  int current_number;

  bool isEven(int number) { return number % 2 == 0; }
};

int main() {
  int user_number;

  std::cout << "Insert natural number ";
  std::cin >> user_number;

  peremena sequence(user_number);
  sequence.run();

  return 0;
}
