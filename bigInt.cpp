#include <iostream>
#include <math.h>
#include <vector>
#include "bigInt.h"
#include <iomanip>

using namespace std;

const int bigInt :: __blockSize = 3;
const int bigInt :: __exponent = pow(10, bigInt :: __blockSize);

bigInt :: bigInt(){
    number.push_back(0);
    isNegative = false;
}

bigInt :: bigInt(string num){
    int pow = 0;
    long long int block = 0, __exponent = 1;
    
    isNegative = (num[0] == '-');

    for(int i = num.size()-1; i >= 0; i--){
        
        if(isNegative && !i)
            break;

        if(pow == __blockSize){
            pow = 0;
            __exponent = 1;

            number.push_back(block);
            block = 0;
        }
        
        block += toInt(num[i])*__exponent;
        pow += 1;
        __exponent *= 10;
    
    }
    
    if(block)
        number.push_back(block);

}

bigInt :: bigInt(long long int num){
    isNegative = (num < 0);
    number.push_back(abs(num));
}


vector<long long int> bigInt :: __add(const vector<long long int> &a, const vector<long long int> &b){
    
    vector<long long int> sum;
    int carry = 0, i;
    
    for(i = 0; i < min(a.size(), b.size()); i++){
        auto block_sum = carry + a[i] + b[i];
        carry = block_sum/__exponent;
        sum.push_back(block_sum % __exponent);
    }
    const vector<long long int> &temp = (a.size() > b.size()) ? a : b;

    while(i < temp.size()){
        auto block_sum = temp[i++] + carry;
        carry = block_sum / __exponent;
        sum.push_back(block_sum % __exponent);
    }

    if(carry)
        sum.push_back(carry);
    
    return sum;
}

void bigInt :: print(){
    cout<<*(number.end()-1);
 
    for(int i = number.size()-2; i >= 0; i--)
        cout<<setw(__blockSize)<<setfill('0')<<number[i];
    
    cout<<endl;
}



int main(){
    bigInt z, x("1"), y("1");
    z.number = z.__add(x.number, y.number);
    z.print();
    return 0;
}