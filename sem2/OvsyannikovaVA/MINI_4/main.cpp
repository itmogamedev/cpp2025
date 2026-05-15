#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

int main() {
  char* locale = setlocale(LC_ALL, "");
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(-50, 100);
  std::vector<int> numvec(20);

  std::generate(numvec.begin(), numvec.end(),
                [&dist, &gen]() { return dist(gen); });

  std::ofstream file("output.txt");

  int minnum = *std::min_element(numvec.begin(), numvec.end());
  int maxnum = *std::max_element(numvec.begin(), numvec.end());

  file << "Минимальный элемент в векторе: " << minnum;
  file << "\nМаксимальный элемент в векторе: " << maxnum;

  auto printvec = [](std::ofstream& file, std::vector<int>& v) {
    for (const auto& elem : v) {
      file << " " << elem;
    }
  };
  std::sort(numvec.begin(), numvec.end());
  file << "\n\nОтсортированный массив: [";
  printvec(file, numvec);
  file << " ]\n";

  int pos =
      std::count_if(numvec.begin(), numvec.end(), [](int x) { return x > 0; });
  int neg =
      std::count_if(numvec.begin(), numvec.end(), [](int x) { return x < 0; });
  int zero =
      std::count_if(numvec.begin(), numvec.end(), [](int x) { return x == 0; });
  file << "\nПоложительных элементов: " << pos << std::endl;
  file << "Отрицательных элементов: " << neg << std::endl;
  file << "Нулевых элементов: " << zero << std::endl;

  int sum = std::accumulate(numvec.begin(), numvec.end(), 0);
  double avg = std::accumulate(numvec.begin(), numvec.end(), 0.0,
                               [](double sum, int x) { return sum + x; }) /
               numvec.size();
  file << "\nСреднее арифметическое: " << avg << std::endl;

  std::vector<int> numvec2 = numvec;
  numvec2.erase(std::remove_if(numvec2.begin(), numvec2.end(),
                               [](int x) { return x % 2 == 0; }),
                numvec2.end());
  file << "\nВектор без чётных чисел: [";
  printvec(file, numvec2);
  file << " ]\n";

  std::vector<int> numvec3 = numvec2;
  std::sort(numvec3.begin(), numvec3.end());
  auto duble = std::unique(numvec3.begin(), numvec3.end());
  numvec3.erase(duble, numvec3.end());
  file << "\nВектор после удаления дубликатов: [";
  printvec(file, numvec3);
  file << " ]\n";
}
