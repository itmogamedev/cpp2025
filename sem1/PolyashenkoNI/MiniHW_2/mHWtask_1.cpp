#include <iostream>
#include <string>
#include <algorithm>



void toOthersSystems(int a){
  std::string octopus = "";
  std::string hexik = "";
  int forHexik = a;
  
  if (a == 0){
    std::cout << "Enter something except null (-vibe)";
    return;
  }

  if (a > 0){
    while (a > 0){
      octopus += std::to_string(a % 8);
      a /= 8;
    }
  }

  std::reverse(octopus.begin(), octopus.end());
  std::cout << "Your octal number is: "<< octopus << std::endl;

  while (forHexik > 0){
    hexik += std::to_string(forHexik % 16);
    forHexik /= 16;
  }
  
  std::reverse(hexik.begin(), hexik.end());
  std::cout << "Your hexal number is: "<< hexik << std::endl;
}

int main(){
  int a = 0;
  std::cout << "Enter your num: ";

  if (!(std::cin >> a)){
    std::cout << "Greeetings! You have been banned! (+vibe)" << std::endl;
    return 1;
  }
  
  toOthersSystems(a);
  return 0;
}
