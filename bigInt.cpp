#include <iostream>
#include "bigInt.h"

using namespace std;

const int bigInt :: blockSize = 3;

bigInt :: bigInt(){
    number.push_back(0);
}

bigInt :: bigInt(string num){
    int pow = 0;
    long long int block = 0, exponent = 1;
    
    isNegative = (num[0] == '-');

    for(int i = num.size()-1; i >= 0; i--){
        
        if(isNegative && !i)
            break;

        if(pow == blockSize){
            pow = 0;
            exponent = 1;

            number.push_back(block);
            block = 0;
        }
        
        block += toInt(num[i])*exponent;
        pow += 1;
        exponent *= 10;
    
    }
    
    if(block)
        number.push_back(block);

    for(auto x : number)
        cout<<x<<" ";

}

int main(){
    bigInt x("123456789");

    return 0;
}