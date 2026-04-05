// #include <windows.h>
//
// #include <cstdlib>
// #include <fstream>
// #include <iostream>
// #include <map>
// #include <string>
// #include <vector>

#include "Adventurer.h"
#include "Guild.h"

//==============================[СЕТТЕРЫ]===============================

//==============================[ГЕТТЕРЫ]===============================

//====================== [ВЫВОД ИНФО В КОНСОЛЬ]

//=================== [РЕГИСТРАЦИЯ И ЗАПИСЬ В ФАЙЛ НОВОГО АВАНТЮРИСТА]

int main() {
  Guild pt("Data.txt");
  pt.menu();
  return 0;
}
