#pragma once
class SymbolGenerator {
 public:
  SymbolGenerator();
  char generate();

 private:
  bool seeded;
};
