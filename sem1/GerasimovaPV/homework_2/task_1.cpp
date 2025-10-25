
#include <iostream>
#include <string>
#include <format>
#pragma once

std::string convertToBase(int c)
{
  std::string result;
  result += "\nin octal: ";
  result += std::format("{:o}", c);
  result += "\nin hexadecimal ";
  result += std::format("{:x}", c);
  return result;
}

int main()
{
  int c;
  std::cin >> c;
  std::cout << convertToBase(c);
}
