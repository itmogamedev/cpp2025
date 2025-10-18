#include<iostream>

int main()
{
    int g;
    g = 1;
    while(g <= 1000)
    {
        int a;
        g++;
        a = g;
        while (a == 1)
        {
            if (a % 2 == 0)
            {
                a /= 2;
            }

            else
            {
                a= ((a*3)+1)/2;
            }
        }
        std::cout << g<< "\n";
        
    } 

}