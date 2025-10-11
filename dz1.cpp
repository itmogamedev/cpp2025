#include<iostream>
using namespace std;

float S_sq(int a)
{
    return a*a;
}

float S_tr_abs(float a,float b,float s)
{
    return 0.5*(a + b)*s;

}

int main() 
{
    while (true)
    {
        char wibor;
        cout<<"wot do u need sqer or trapezoid? (s / t)"<<endl;
        cin>>wibor;

        if (wibor == 's')
        {
            int input;
            cout<<"tipe side lenght ";
            cin>>input;

            cout<<endl<<"S = "<<S_sq(input);
        }

        if (wibor == 't')
        {
            int input1,input2,input3;
            cout<<"Tipe sid's and hight length ";
            cin>>input1>>input2>>input3;

            cout<<endl<<"S = "<<S_tr_abs(input1,input2,input3);
        }


        if (wibor != 's' and wibor != 't')
        {
            cout<<"only s or t man...";
        }

        cout<<endl<<"*****************"<<endl<<endl;
    }
}