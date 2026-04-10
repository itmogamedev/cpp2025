# include<iostream>

int main()
{
  char w;
  long int n; // навсякий случай .....
  std::cout << "number, to hex or to oct (h/o)\n";
  std::cin >> n >> w;


  if (w == 'h')
  {
    std::cout << "ans: " << std::hex << n << std::dec << "\n";
  }

  if (w == 'o')
    {
      std::cout << "ans: " << std::oct << n << std::dec << "\n";
    }
  if (w != 'h' and w != 'o')
    {
      std::cout << "\33[91mincorrect letter\33[0m" << "\n";
    }
}