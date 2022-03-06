#include <iostream>
#include <vector>
#include <string>

#define toInt(x) (int)(x - '0')
#define toChar(x) (char)(x + '0')

enum __sign {
    pp, pn, np, nn
};

class bigInt
{

    std :: vector<long long int> number;
    bool isNegative;

    const static int __blockSize;
    const static long long int __exponent;

    std :: vector<long long int> __add(const std :: vector<long long int> &a, const std :: vector<long long int> &b);
    std :: vector<long long int> __sub(const std :: vector<long long int> &a, const std :: vector<long long int> &b);
    
    bool __abs_greater(const std :: vector<long long int> &a, const std :: vector<long long int> &b, bool true_if_equal);
    bool __abs_smaller(const std :: vector<long long int> &a, const std :: vector<long long int> &b, bool true_if_equal);

    __sign get_case(bool a, bool b);

    public:

    friend std :: ostream &operator<<(std :: ostream &op_stream, const bigInt &bi);
    friend std :: istream &operator>>(std :: istream &in_stream, bigInt &bi);

    bigInt();
    bigInt(std :: string num);
    bigInt(long long num);
    bigInt(bigInt &num);

    void operator=(bigInt const &num);
    void operator=(long long int num);
    void operator=(std :: string num);

    bool operator>(bigInt const &num);
    bool operator>=(bigInt const &num);
    bool operator<(bigInt const &num);
    bool operator<=(bigInt const &num);

    bool operator==(bigInt const &num);
    bool operator==(long long int num);
    bool operator==(std :: string const &num);

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
