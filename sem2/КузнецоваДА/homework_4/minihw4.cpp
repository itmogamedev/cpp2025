#include<iostream>
#include<fstream>
#include<vector>
#include<random>
#include<numeric>

int main()
{
  std::ofstream out;
  out.open("output.txt");
  if (!out.is_open()) return 1;
  std::vector<int> randNum(20);
  std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution uni(-50, 100);
  std::generate(randNum.begin(), randNum.end(), [&]() { return uni(gen); });

  out << "Min: " << *(std::min_element(randNum.begin(), randNum.end()))
    << std::endl;
  out << "\nMax: " << *(std::max_element(randNum.begin(), randNum.end()))
    << std::endl;

  out << "\nSorted: ";
  std::sort(randNum.begin(), randNum.end());
  std::for_each(randNum.begin(), randNum.end(), [&out](int i) { out << i << " "; });
  out << std::endl;

  int positiveElementsNum = std::count_if(randNum.begin(), randNum.end(), [](int i) { return i > 0; });
  out << "\nNumber of positive numbers: " << positiveElementsNum << std::endl;
  int negativeElementsNum = std::count_if(randNum.begin(), randNum.end(), [](int i) { return i < 0; });
  out << "\nNumber of negative numbers: " << negativeElementsNum << std::endl;
  int zeroElementsNum = std::count_if(randNum.begin(), randNum.end(),[](int i) { return i == 0; });
  out << "\nNumber of zeroes: " << zeroElementsNum << std::endl;

  double sum = std::accumulate(randNum.begin(), randNum.end(), 0.0);
  double average = sum / randNum.size();
  out << "\nAverage: " << average << std::endl;

  std::vector<int> withoutSmall;
  out << "\nWithout numbers smaller than average: ";
  std::copy_if(randNum.begin(), randNum.end(), std::back_inserter(withoutSmall), [average](int i) { return i >= average; });
  std::for_each(withoutSmall.begin(), withoutSmall.end(), [&out](int i) { out << i << " "; });
  out << std::endl;

  std::sort(withoutSmall.begin(), withoutSmall.end());
  std::vector<int> withoutRepetitions;
  std::unique_copy(withoutSmall.begin(), withoutSmall.end(), std::back_inserter(withoutRepetitions));
  out << "Unique vector: ";
  std::for_each(withoutRepetitions.begin(), withoutRepetitions.end(), [&out](int i) { out << i << " "; });

  out << std::endl;
  out.close();
}
