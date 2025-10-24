#include <iostream>
#pragma once

bool syracuseTest(int c)
{
  bool result = false;
  while (c > 1)
  {
    if (c % 2 == 0)
    {
      c /= 2;
    }
    else if (c < 1)
    {
      break;
    }
    else
    {
      c = c * 3 + 1;
    }
  }
  if (c == 1)
  {
    result = true;
  }
  return result;
}

int main()
{
  int c;
  std::cin >> c;
  std::cout << syracuseTest(c);
}
