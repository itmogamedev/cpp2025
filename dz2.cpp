# include<iostream>
# include<string>
using namespace std;

// первое задание
void ex1()
{
    char w;
    long int n; // навсякий случай .....
    cout << "number, to hex or to oct (h/o)\n";
    cin >> n >> w;


    if (w == 'h')
    {
        cout << "ans: " << hex << n << dec << endl;
    }

    if (w == 'o')
    {
        cout << "ans: " << oct << n << dec << endl;
    }
    if (w != 'h' and w != 'o')
    {
        cout << "\33[91mincorrect letter\33[0m" << endl;
    }
}

// второе задание
void ex2()
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
        cout<<g<<"\n";
        
    } 

}

int main()
{
    while (true)
    {

    char wibor;
    cout << "(1/2)" << endl;
    try
    {
        cin >> wibor;
    }
    catch(...)
    {
        std::cerr << "INCORECT" << '\n';
    }
   

    if (wibor == '1')
    {
        ex1();
    }

    if (wibor == '2')
    {
        ex2();
    }

    if (wibor != '1' and wibor != '2')
    {
        cout << "\33[91mincorrect number\33[0m" << endl;
    }

    cout << endl << "********" << endl;
    }
    
}