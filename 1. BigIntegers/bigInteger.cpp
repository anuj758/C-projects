#include <iostream>
#include <stdexcept>
#include <algorithm>
using namespace std;

class bigInteger{
    string num;

    static string trimLeadingZeros(string str) {
        int i = 0;
        while (i < str.size() - 1 && str[i] == '0') i++;
        return str.substr(i);
    }

    static bool valid(string str){
        for(char c : str){
            if(c < '0' || c > '9') return false;
        }
        return true;
    }

    string addition(string a, string b){
        string answer;
        if(a.size() < b.size()) swap(a, b);
        while(b.size() < a.size()) b = '0' + b;
        int carry = 0;
        for(int i = a.size() - 1; i >= 0; i--){
            int digit1 = a[i] - '0';
            int digit2 = b[i] - '0';
            int sum = digit1 + digit2 + carry;
            answer.push_back(sum % 10 + '0');
            carry = sum / 10;
        }
        if(carry) answer.push_back('1');
        reverse(answer.begin(), answer.end());
        return answer;
    }

    string subtraction(string a, string b){ // calculate a - b
        string answer;
        char sign;
        if(a.size() == b.size())    sign = (a >= b) ? '+' : '-';
        else sign = (a.size() > b.size()) ? '+' : '-';

        if(sign == '-') swap(a, b);
        while(b.size() < a.size()) b = '0' + b;
        int borrow = 0;
        for(int i = a.size() - 1; i >= 0; i--){
            int digit1 = a[i] - '0' + borrow;
            int digit2 = b[i] - '0';
            if(digit1 >= digit2){
                borrow = 0;
            }
            else{
                digit1 = 10 + digit1;
                borrow = -1;
            }
            int diff = digit1 - digit2;
            answer.push_back(diff + '0');
        }
        reverse(answer.begin(), answer.end());
        answer = trimLeadingZeros(answer);
        if(sign == '-') answer = '-' + answer;
        return answer;
    }

    string multiplication(string a,string b){
        if(a.length()<b.length()) swap(a,b);        //b is always smaller

        reverse(a.begin(),a.end());
        reverse(b.begin(),b.end());

        string answer="";

        for(int i=0;i<b.length();i++){
            string multi;
            for(int k=0;k<i;k++) multi.push_back('0');
            int carry=0;
            int d2=b[i]-'0';
            for(char x:a){
                int d1=x-'0';
                int product=d1*d2+carry;
                char outputChar=product%10+'0';
                carry=product/10;
                multi.push_back(outputChar);   
            }
            if(carry) multi.push_back(carry+'0');
            reverse(multi.begin(),multi.end());
            answer=addition(answer,multi);    
        }
        answer = trimLeadingZeros(answer);
        return answer;
    }

    bigInteger divideByTwo(bigInteger n){
        string result;
        int carry = 0;

        for (char digit : n.num) {
            int current = carry * 10 + (digit - '0');
            result += (current / 2) + '0';
            carry = current % 2;
        }

        result = trimLeadingZeros(result);
        return bigInteger(result);
    }

    public:
        bigInteger(){     // constructor
            num = "0";
        }
        bigInteger(string str){   // parametrized contructor
            if(str.empty()){
                num = "0";
            }
            else{
                bool neg = (str[0] == '-');
                if(neg) str = str.substr(1);
                if(!valid(str)){
                    throw invalid_argument("! Invalid number.");
                }
                str = trimLeadingZeros(str);
                str = neg ? "-" + str : str;
                num = (str == "-0") ? "0" : str;
            }
        }

        bigInteger operator +(bigInteger& other){
            string a = num;
            string b = other.num;
            string answer;
            if(a[0] == '-' && b[0] == '-'){
                a = a.substr(1);
                b = b.substr(1);
                answer = "-" + addition(a, b);
            }
            else if(a[0] == '-'){
                a = a.substr(1);
                answer = subtraction(b, a);
            }
            else if(b[0] == '-'){
                b = b.substr(1);
                answer = subtraction(a, b);
            }
            else{
                answer = addition(a, b);
            }
            return (answer == "-0") ? bigInteger("0") : bigInteger(answer);
        }

        bigInteger operator -(bigInteger& other){
            string a = num;
            string b = other.num;
            string answer;
            if(a[0] == '-' && b[0] == '-'){
                a = a.substr(1);
                b = b.substr(1);
                answer = subtraction(b, a);
            }
            else if(a[0] == '-'){
                a = a.substr(1);
                answer = "-" + addition(a, b);
            }
            else if(b[0] == '-'){
                b = b.substr(1);
                answer = addition(a, b);
            }
            else{
                answer = subtraction(a, b);
            }
            return (answer == "-0") ? bigInteger("0") : bigInteger(answer);          
        }

        bigInteger operator *(bigInteger& other){
            string a = num;
            string b = other.num;
            string answer;
            if(a[0] == '-' && b[0] == '-'){
                a = a.substr(1);
                b = b.substr(1);
                answer = multiplication(a, b);
            }
            else if(a[0] == '-'){
                a = a.substr(1);
                answer = "-" + multiplication(a, b);
            }
            else if(b[0] == '-'){
                b = b.substr(1);
                answer = "-" + multiplication(a, b);
            }
            else{
                answer = multiplication(a, b);
            }
            return (answer == "-0") ? bigInteger("0") : bigInteger(answer);
        }

        bigInteger& operator=(const bigInteger& other) {
            if (this != &other) { 
                this->num = other.num;
            }
            return *this;
        }


        bool operator <(const bigInteger& other) const{     // a < b
            string a = num;
            string b = other.num;

            bool negA = (a[0] == '-');
            bool negB = (b[0] == '-');

            if (negA && !negB) return true;
            if (!negA && negB) return false;


            if (negA) {
                a = a.substr(1);
                b = b.substr(1);
            }


            if (a.length() != b.length())
                return negA ? a.length() > b.length() : a.length() < b.length();


            for (int i = 0; i < a.length(); ++i) {
                if (a[i] != b[i])
                    return negA ? a[i] > b[i] : a[i] < b[i];
            }

            return false;   
        }

        bool operator >(const bigInteger& other) const{
            return other < *this;
        }
        
        bool operator ==(const bigInteger& other) const{
            return num == other.num;
        }

        bool operator <=(const bigInteger& other) const{
            return (*this < other) || (*this == other);
        }

        bool operator >=(const bigInteger& other) const{
            return (*this > other) || (*this == other);
        }

        bool operator !=(const bigInteger& other) const{
            return !(*this == other);
        }

        bigInteger operator +=(bigInteger& other){
            *this = *this + other;
            return *this;
        }

        bigInteger operator -=(bigInteger& other){
            *this = *this - other;
            return *this;
        }

        bigInteger operator *=(bigInteger& other){
            *this = *this * other;
            return *this;
        }

        // Prefix ++a
        bigInteger& operator++() {
            bigInteger one("1");
            *this = *this + one;
            return *this;
        }

        // Postfix a++
        bigInteger operator++(int) {
            bigInteger temp = *this;
            ++(*this); // Reuse prefix
            return temp;
        }

        // Prefix --
        bigInteger& operator--() {
            bigInteger one("1");
            *this = *this - one;
            return *this;
        }

        // Postfix --
        bigInteger operator--(int) {
            bigInteger temp = *this;
            --(*this); // Reuse prefix
            return temp;
        }

        bigInteger operator -(){
            return (num[0] == '-') ? bigInteger(num.substr(1)) : "-" + num;
        }

        bigInteger operator!() {
            if (num[0] == '-') {
                throw invalid_argument("Factorial is undefined for negative numbers.");
            }

            bigInteger a = *this;
            bigInteger i("1");
            bigInteger ans("1");
            while(i <= a){
                ans = ans * i;
                i++;
            }
            return ans;
        }

        string division(string a, string b){
            if(b == "0") throw invalid_argument("!Division by zero.");
            bigInteger low("0"), high(a);
            bigInteger divisor(b), dividend(a);
            string answer;
            bigInteger one("1");
            while(low <= high){
                bigInteger mid = high + low;
                mid = divideByTwo(mid.num);
                bigInteger product = mid * divisor;
                if(product == dividend){
                    answer = mid.num;
                    break;
                }
                else if(product < dividend){
                    answer = mid.num;
                    low = mid + one;
                }
                else{
                    high = mid - one;
                }
            }
            return answer;
        }

        bigInteger operator /(bigInteger& other){
            string a = num;
            string b = other.num;
            string answer;
            if(a[0] == '-' && b[0] == '-'){
                a = a.substr(1);
                b = b.substr(1);
                answer = division(a, b);
            }
            else if(a[0] == '-'){
                a = a.substr(1);
                answer = division(a, b);
                answer = "-" + answer;
            }
            else if(b[0] == '-'){
                b = b.substr(1);
                answer = division(a, b);
                answer = "-" + answer;
            }
            else{
                answer = division(a, b);
            }
            return (answer == "-0") ? bigInteger("0") : bigInteger(answer);
        }

        bigInteger operator%(bigInteger& other) {
            bigInteger quotient = *this / other;
            bigInteger product = quotient * other;
            bigInteger remainder = *this - product;
            if (remainder < bigInteger("0"))
                remainder = remainder + other;

            return remainder;
        }

        bigInteger operator /=(bigInteger& other){
            *this = *this / other;
            return *this;
        }

        bigInteger operator %=(bigInteger& other){
            *this = *this % other;
            return *this;            
        }

        friend ostream& operator << (ostream& os, const bigInteger& output);
        friend istream& operator >> (istream& is, bigInteger& input);

};

ostream& operator << (ostream& os, const bigInteger& output){
    os << output.num;
    return os;
}

istream& operator >> (istream& is, bigInteger& input){
    string str;
    is >> str;
    bool neg = (str[0] == '-');
    if(neg) str = str.substr(1);
    if(!(bigInteger :: valid(str))){
        throw invalid_argument("! Invalid number.");
    }
    str = bigInteger :: trimLeadingZeros(str);
    str = neg ? "-" + str : str;
    input.num = (str == "-0") ? "0" : str;
    return is;
}
