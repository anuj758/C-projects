#include <iostream>
using namespace std;


int main(){
    long long int num1, num2;
    cout << "Enter two integers : ";
    cin >> num1 >> num2;
    char operation;
    cout << "--------------------------------------------------------------------------------" << "\n";
    cout << "1. Enter '+' for addition" << "\n";
    cout << "2. Enter '-' for subtraction" << "\n";
    cout << "3. Enter '*' for multiplication" << "\n";
    cout << "4. Enter '/' for division" << "\n";
    cout << "5. Enter '%' for remainder" << "\n";
    cout << "--------------------------------------------------------------------------------" << "\n";
    cin >> operation;

    long long int ans;
    switch (operation)
    {
    case '+':
        ans = num1 + num2;
        cout << ans << "\n";
        break;
    
    case '-':
        ans = num1 - num2;
        cout << ans << "\n";
        break;

    case '*':
        ans = num1 * num2;
        cout << ans << "\n";
        break;
    
    case '/':
        ans = num1 / num2;
        break;

    case '%':
        ans = num1 % num2;
        cout << ans << "\n";
        break;

    default:
        cout << "operation not valid" << "\n";
        break;
    }
    return 0;
}
