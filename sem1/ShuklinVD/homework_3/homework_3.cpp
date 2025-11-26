#include <locale.h>

#include <iostream>

#include "functions.h"

int main() {
  system("chcp 1251 > nul");
  setlocale(LC_ALL, "");
  readFile("DataBase.txt");
  return 0;
}
