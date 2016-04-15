#include <iostream>
#include<string>

using namespace std;

int cases(string A) {
   
    if(A == "I")      return 1;
    if(A == "IV")     return 4;
    if(A == "V")      return 5;
    if(A == "IX")     return 9;
    if(A == "X")      return 10;
    if(A == "XL")     return 40;
    if(A == "L")      return 50;
    if(A == "XC")     return 90;
    if(A == "C")      return 100;
    if(A == "CD")     return 400;
    if(A == "D")      return 500;
    if(A == "CM")     return 900;
    if(A == "M")      return 1000;
    
    return 0;
}

int romanToInt(string A) {
    int sum = 0;
    
    for(int i = 0; i < A.length() ; i++) {
        string str;
        str.push_back(A[i]);
        if(i+1 < A.length()) {
            string s;
            s.push_back(A[i]);
            s.push_back(A[i+1]);
            if(cases(str) < cases(s)) {
                sum += cases(s);
                i++;
                continue;
            }
        }
        
        sum += cases(str);
    }
    
    return sum;
}

int main() {
   cout << romanToInt("XXIV");
   return 0;
}
