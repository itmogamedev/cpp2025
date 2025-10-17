 #include <iostream>
using namespace std;

int main(){
    int n;
    cout << "Input your number:";
    cin >> n;
    if (n==0){
        cout << "You need input n>0!";
        return 1;
    }

    while (n!=1){
        if (n%2 == 0)
        {
            n /=2;
        }
        else 
        {
            n = (n*3 + 1 ) / 2;
        }
        cout << "====>" << n;
    }
    cout << "All good, the theorem work!";
    return 0;
}