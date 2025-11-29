#include<iostream>

int main()
{
  int number;
  number = 1;
  while(number <= 1000)
  {
    int test_num;
    number++;
    test_num = number;

    while (test_num == 1)
    {
      if (test_num % 2 == 0)
        {
          test_num /= 2;
        }

        else
          {
            test_num = ((test_num*3)+1)/2;
          }
      }
  std::cout << number << "\n";  
  } 
}