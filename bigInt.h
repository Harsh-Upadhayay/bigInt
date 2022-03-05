#include <bits/stdc++.h>

using namespace std;

#define toInt(x) (int)(x - '0')
#define toChar(x) (char)(x + '0')

class bigInt
{

    string number;

    public:

    friend ostream &operator<<(ostream &op_stream, const bigInt &bi);
    friend istream &operator>>(istream &in_stream, bigInt &bi);

    bigInt();
    bigInt(string num);
    bigInt(long long num);
    bigInt(bigInt &num);

    /**
     * @brief fun desc.
     * 
     * @param num 
     */
    void operator=(bigInt const &num);
    /**
     * @brief asda
     * 
     * @param num 
     */
    void operator=(long long int num);
    void operator=(string num);

    bool operator>(bigInt const &num);
    bool operator>(long long int num);
    bool operator>(string const &num);

    bool operator>=(bigInt const &num);
    bool operator>=(long long int num);
    bool operator>=(string const &num);

    bool operator<(bigInt const &num);
    bool operator<(long long int num);
    bool operator<(string const &num);

    bool operator<=(bigInt const &num);
    bool operator<=(long long int num);
    bool operator<=(string const &num);

    bool operator==(bigInt const &num);
    bool operator==(long long int num);
    bool operator==(string const &num);

    /**
     * @brief Pre increment operator
     * 
     * @return incremented bigInt 
     */
    bigInt operator++();

    /**
     * @brief Post increment operator
     * 
     * @return unincremented bigInt 
     */
    bigInt operator++(int);

    bigInt operator--();
    bigInt operator--(int);

    bigInt operator-(bigInt const &num);
    bigInt operator-(long long int num);
    bigInt operator-(string const &num);

    bigInt operator+(bigInt const &num);
    bigInt operator+(long long int num);
    bigInt operator+(string const &num);

    bigInt operator*(bigInt const &num);
    bigInt operator*(long long int num);
    /**
     * @brief overloaded operator to multiply string with bigInt obj
     * 
     * @param num string constan
     * @return Product bigInt 
     */
    bigInt operator*(string const &num);
};
