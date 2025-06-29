#include "bigInteger.cpp"

int main(){
    bigInteger a("1000000000000000000");
    bigInteger b("98765432123456789");

    bigInteger sum = a + b;
    bigInteger fact = !bigInteger("50");

    cout << "Sum: " << sum << endl;
    cout << "Factorial: " << fact << endl;
    return 0;
}
