#include <iostream>
#include <math.h>
#include <vector>
#include "bigInt.h"
#include <iomanip>

using namespace std;

const int bigInt :: __blockSize = 18;
const long long int bigInt :: __exponent = pow(10, bigInt :: __blockSize);

bigInt :: bigInt(){

    isNegative = false;
}

bigInt :: bigInt(string num){

    *this = num;
}

bigInt :: bigInt(long long int num){
    
    isNegative = (num < 0);
    while(num){
        number.push_back(num%__exponent);
        num /= __exponent;
    }
}

bigInt :: bigInt(bigInt &num){
    for(auto x : num.number)
        number.push_back(x);
    isNegative = num.isNegative;
}

vector<long long int> bigInt :: __add(const vector<long long int> &a, const vector<long long int> &b){
    
    vector<long long int> sum;
    int carry = 0, i;
    
    for(i = 0; i < min(a.size(), b.size()); i++){
        long long int block_sum = carry + a[i] + b[i];
        carry = block_sum/__exponent;
        sum.push_back(block_sum % __exponent);
    }
    const vector<long long int> &temp = (a.size() > b.size()) ? a : b;

    while(i < temp.size()){
        long long int block_sum = temp[i++] + carry;
        carry = block_sum / __exponent;
        sum.push_back(block_sum % __exponent);
    }

    if(carry)
        sum.push_back(carry);
    
    return sum;
}

vector<long long int> bigInt :: __sub(const vector<long long int> &a, const vector<long long int> &b){

    bool check = __abs_greater(a, b, false);    
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

    for(int i = diff.size()-1; i > 0; i--)
        if(!diff[i])
            diff.pop_back();
        else
            break;

    return diff;
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

bool bigInt :: __abs_smaller(const vector<long long int> &a, const vector<long long int> &b, bool true_if_equal = false){
    
    if(a.size() != b.size())  
        return a.size() < b.size();
    
    for(int i = 0; i < a.size(); i++)
        if(a[i] > b[i])
            return false;
        else if(b[i] > a[i])
            return true;

    return true_if_equal;        
}

__sign bigInt :: get_case(bool a, bool b){
    if(!a && !b) 
        return pp;
    if(!a && b)
        return pn;
    if(a && !b)
        return np;
    return nn;
}


bigInt bigInt :: operator+(bigInt const &num){
    
    const vector<long long int> &a = this->number, &b = num.number;
    bigInt sum;
    __sign sign = get_case(this->isNegative, num.isNegative);

    switch (sign)
    {
    case pp:
        sum.number = __add(a, b); 
        sum.isNegative = false;
        break;    
    case pn:
        sum.number = __sub(a, b);
        sum.isNegative = !__abs_greater(a, b); 
        break;  
    case np:
        sum.number = __sub(a, b); 
        sum.isNegative = __abs_greater(a, b);
        break;  
    case nn:
        sum.number = __add(a, b);
        sum.isNegative = true; 
        break;
    }

    return sum;
}

bigInt bigInt :: operator+(long long int num){
    bigInt temp(num);
    temp = *this + temp;
    return temp;
}

bigInt bigInt :: operator+(string const &num){
    bigInt temp(num);
    temp = *this + temp;
    return temp;
}

bigInt bigInt :: operator-(bigInt const &num){
    
    const vector<long long int> &a = this->number, &b = num.number;
    bigInt diff;
    __sign sign = get_case(this->isNegative, num.isNegative);

    switch (sign)
    {
    case pp:
        diff.number = __sub(a, b); 
        diff.isNegative = !__abs_greater(a, b);
        break;    
    case pn:
        diff.number = __add(a, b);
        diff.isNegative = false; 
        break;  
    case np:
        diff.number = __add(a, b); 
        diff.isNegative = true;
        break;  
    case nn:
        diff.number = __sub(a, b);
        diff.isNegative = __abs_greater(a, b); 
        break;
    }

    return diff;
}

bigInt bigInt :: operator-(long long int num){
    bigInt temp(num);
    temp = *this - temp;
    return temp;
}

bigInt bigInt :: operator-(string const &num){
    bigInt temp(num);
    temp = *this - temp;
    return temp;
}

void bigInt :: operator=(bigInt const &num){
    
    this->number.clear();

    for(auto x : num.number)
        this->number.push_back(x);
    
    this->isNegative = num.isNegative;
}

void bigInt :: operator=(long long int num){
    
    number.clear();
    isNegative = (num < 0);
    while(num){
        number.push_back(num%__exponent);
        num /= __exponent;
    }
}

void bigInt :: operator=(string num){
    
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

bool bigInt :: operator>(bigInt const &num){    
    
    const vector<long long int> &a = this->number, &b = num.number;
    __sign sign = get_case(this->isNegative, num.isNegative);
    bool isGreater;

    switch (sign)
    {
    case pp:
        isGreater = __abs_greater(a, b);
        break;
    case pn:
        isGreater = true;
        break;
    case np:
        isGreater = false;
        break;
    case nn:
        isGreater = __abs_smaller(a, b);
        break;
    }

    return isGreater;
}

bool bigInt :: operator>=(bigInt const &num){    
    
    const vector<long long int> &a = this->number, &b = num.number;
    __sign sign = get_case(this->isNegative, num.isNegative);
    bool isGreater;

    switch (sign)
    {
    case pp:
        isGreater = __abs_greater(a, b, true);
        break;
    case pn:
        isGreater = true;
        break;
    case np:
        isGreater = false;
        break;
    case nn:
        isGreater = __abs_smaller(a, b, true);
        break;
    }

    return isGreater;
}

bool bigInt :: operator<(bigInt const &num){    
    
    return !(*this >= num);
}

bool bigInt :: operator<=(bigInt const &num){    
    
    return !(*this > num);
}

bool bigInt :: operator==(bigInt const &num){
    if(number.size() != num.number.size())
        return false;

    for(int i = 0; i < number.size(); i++)
        if(number[i] != num.number[i])
            return false;
    
    return (this->isNegative == num.isNegative);
}

bool bigInt :: operator==(long long int num){
    bigInt temp(num);
    return *this == temp;
}

bool bigInt :: operator==(std :: string const &num){
    bigInt temp(num);
    return *this == temp;
}

ostream &operator<<(ostream &op_stream, const bigInt &bi) {

    if(!bi.number.size())
        return op_stream << "0";

    if(bi.isNegative)
        op_stream << "-";
    
    op_stream << *(bi.number.end()-1);
 
    for(int i = bi.number.size()-2; i >= 0; i--)
        op_stream << setw(bi.__blockSize) << setfill('0') << bi.number[i];
    
    return op_stream;
}

istream &operator>>(istream &in_stream, bigInt &bi) {
    
    string input;
    in_stream >> input;
    // bi = input;

    return in_stream;
}

