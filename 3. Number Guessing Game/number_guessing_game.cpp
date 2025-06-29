#include <iostream>
#include <ctime>
using namespace std;

int main(){
    srand(time(0));
    int n = rand();
    while(true){
        int x;
        cout << "Enter the number: ";
        cin >> x;

        if(x == n){
            cout << "Correct Answer" << "\n";
            break;
        }
        else if(x < n){
            cout << "Guessed number is too low" << "\n";
        }
        else{
            cout << "Guessed number is too high" << "\n";
        }
    }

    return 0;
}
