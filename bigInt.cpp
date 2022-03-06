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

bool bigInt :: __abs_greater(const vector<long long int> &a, const vector<long long int> &b, bool true_if_equal = false){
    
    if(a.size() != b.size())  
        return a.size() > b.size();
    
    for(int i = 0; i < a.size(); i++)
        if(a[i] < b[i])
            return false;
        else if(b[i] < a[i])
            return true;

    return true_if_equal;        
}

vector<long long int> bigInt :: __sub(const vector<long long int> &a, const vector<long long int> &b){

    bool check = __abs_greater(a, b);    
    const vector<long long int> &greater = check? a : b,
                                &smaller = !check? a : b;

    vector<long long int> diff;
    short borrow = 0, i;

    for(i = 0; i < smaller.size(); i++){
        long long int block_diff = greater[i] - smaller[i] - borrow;

        if(block_diff < 0){
            block_diff += __exponent;
            borrow = 1;
        }
        else
            borrow = 0;
        
        diff.push_back(block_diff);
    }
    
    while(i < greater.size()){
        long long int block_diff = greater[i++] - borrow;

        if(block_diff < 0){
            block_diff += __exponent;
            borrow = 1;
        }
        else
            borrow = 0;
        
        diff.push_back(block_diff);
    }

    for(int i = diff.size()-1; i >= 0; i--)
        if(!diff[i])
            diff.pop_back();
        else
            break;

    return diff;
}


int main(){
    bigInt z, x("1000000000"), y("12345678910");
    z.number = z.__sub(x.number, y.number);
    z.print();
    return 0;
}