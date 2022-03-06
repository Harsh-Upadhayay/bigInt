#include <iostream>
#include <vector>
#include <string>

#define toInt(x) (int)(x - '0')
#define toChar(x) (char)(x + '0')

class bigInt
{
    public:

    std :: vector<long long int> number;
    const static int __blockSize;
    const static int __exponent;
    bool isNegative;

    

    friend std :: ostream &operator<<(std :: ostream &op_stream, const bigInt &bi);
    friend std :: istream &operator>>(std :: istream &in_stream, bigInt &bi);

    bigInt();
    bigInt(std :: string num);
    bigInt(long long num);
    bigInt(bigInt &num);

    std :: vector<long long int> __add(const std :: vector<long long int> &a, const std :: vector<long long int> &b);
    std :: vector<long long int> __sub(const std :: vector<long long int> &a, const std :: vector<long long int> &b);
    bool __abs_greater(const std :: vector<long long int> &a, const std :: vector<long long int> &b, bool true_if_equal);
    void print();

    void operator=(bigInt const &num);
    void operator=(long long int num);
    void operator=(std :: string num);

    bool operator>(bigInt const &num);
    bool operator>(long long int num);
    bool operator>(std :: string const &num);

    bool operator>=(bigInt const &num);
    bool operator>=(long long int num);
    bool operator>=(std :: string const &num);

    bool operator<(bigInt const &num);
    bool operator<(long long int num);
    bool operator<(std :: string const &num);

    bool operator<=(bigInt const &num);
    bool operator<=(long long int num);
    bool operator<=(std :: string const &num);

    bool operator==(bigInt const &num);
    bool operator==(long long int num);
    bool operator==(std :: string const &num);

    bigInt operator++();
    bigInt operator++(int);

    bigInt operator--();
    bigInt operator--(int);

    bigInt operator-(bigInt const &num);
    bigInt operator-(long long int num);
    bigInt operator-(std :: string const &num);

    bigInt operator+(bigInt const &num);
    bigInt operator+(long long int num);
    bigInt operator+(std :: string const &num);

    bigInt operator*(bigInt const &num);
    bigInt operator*(long long int num);
    bigInt operator*(std :: string const &num);
};
