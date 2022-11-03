#include <cstddef>
#include <cstdlib>
#include <ios>
#include <iostream>
#include <string.h>
#include <string>
#include <cmath>

using std::cout;
using std::endl;

class BigNum {
public:
    BigNum() {
        copyFromStr("0");
    }

    BigNum(const BigNum& bigNum) {
        copyDigits(bigNum);
        copyStr(bigNum);
    }

    BigNum(const char* num) {
        copyFromStr(num);
    }

    BigNum(const char* digitArr, size_t arrLen, bool isNeg) {
        this->isNeg = isNeg;
        copyDigitsFromDigits(digitArr, arrLen);
        copyStrFromDigits(digitArr, arrLen);
    }

    BigNum(long long num) {
        if (num < 0) {
            isNeg = true;
            num = -num;
        }
        else
            isNeg = false;
        len = 1;
        long long numCopy = num;
        while (numCopy /= 10) ++len;
        digits = (char*)malloc(len * sizeof(char));
        for (size_t i = 0; i < len; ++i) {
            digits[i] = num % 10;
            num /= 10;
        }
        copyStrFromDigits(digits, len);
    }

    ~BigNum() {
        autoFree();
    }

    const char* getStrNum() const {
        return strNum;
    }

    void print() const {
        cout << strNum << endl;
    }

    void printDigits() const {
        if (isNeg)
            cout << '-';
        for (long long i = len - 1; i >= 0; --i)
            cout << digits[i] + 0;
        cout << endl;
    }

    void operator=(const BigNum& bigNum) {
        if (*this == bigNum) return;
        autoFree();
        copyDigits(bigNum);
        copyStr(bigNum);
    }

    void operator=(const char* num) {
        if (strLen == strlen(num) && memcmp(strNum, num, strLen))
            return;
        autoFree();
        copyFromStr(num);
    }

    BigNum operator-() const {
        if (strNum[0] == '0' )
            return *this;
        else if (isNeg) {
            BigNum ret(strNum + 1);
            ret.isNeg = false;
            return ret;
        }
        else {
            BigNum ret(true);
            ret.copyDigits(*this);
            ret.isNeg = true;
            ret.strLen = ret.len + 1;
            ret.strNum = (char*)malloc((ret.strLen + 1) * sizeof(char));
            ret.strNum[0] = '-';
            for (size_t i = 1; i < ret.strLen; ++i)
                ret.strNum[i] = strNum[i - 1];
            ret.strNum[ret.strLen] = 0;
            return ret;
        }
    }

    int compare(const BigNum& bigNum) const {
        if (this == &bigNum)
            return 0;
        else if (strNum[0] == '0') {
            if (bigNum.isNeg)
                return 1;
            else if (bigNum.strNum[0] == '0')
                return 0;
            else
                return -1;
        }
        else if (bigNum.strNum[0] == '0')
            return isNeg ? -1 : 1;
        else if (isNeg && !bigNum.isNeg)
            return -1;
        else if (!isNeg && bigNum.isNeg)
            return 1;
        else if (len > bigNum.len)
            return isNeg ? -1 : 1;
        else if (len < bigNum.len)
            return isNeg ? 1 : -1;
        else {
            for (long long i = len - 1; i >= 0; --i) {
                if (digits[i] > bigNum.digits[i])
                    return isNeg ? -1 : 1;
                else if (digits[i] < bigNum.digits[i])
                    return isNeg ? 1 : -1;
            }
            return 0;
        }
    }

    bool operator==(const BigNum& bigNum) {
        return compare(bigNum) == 0;
    }

    bool operator>(const BigNum& bigNum) {
        return compare(bigNum) > 0;
    }

    bool operator<(const BigNum& bigNum) {
        return compare(bigNum) < 0;
    }

    bool operator>=(const BigNum& bigNum) {
        return compare(bigNum) >= 0;
    }

    bool operator<=(const BigNum& bigNum) {
        return compare(bigNum) <= 0;
    }

    BigNum operator+(const BigNum& bigNum) const {
        if (digits[len - 1] == '\0')
            return bigNum;
        else if (bigNum.digits[bigNum.len - 1] == '\0') 
            return *this;
        else if (isNeg && !bigNum.isNeg)
            return bigNum - -*this;
        else if (!isNeg && bigNum.isNeg)
            return *this - -bigNum;
        else {
            BigNum ret(true);
            char temp, carry = 0;
            size_t i;
            if (len == bigNum.len) {
                ret.digits = (char*)malloc((len + 1) * sizeof(char));
                for (i = 0; i < bigNum.len; ++i) {
                    temp = digits[i] + bigNum.digits[i] + carry;
                    ret.digits[i] = temp % 10;
                    carry = temp / 10;
                }
            }
            else if (len > bigNum.len) {
                ret.digits = (char*)malloc((len + 1) * sizeof(char));
                for (i = 0; i < bigNum.len; ++i) {
                    temp = digits[i] + bigNum.digits[i] + carry;
                    ret.digits[i] = temp % 10;
                    carry = temp / 10;
                }
                for (; i < len; ++i) {
                    temp = digits[i] + carry;
                    ret.digits[i] = temp % 10;
                    carry = temp / 10;
                }
            }
            else {
                ret.digits = (char*)malloc((bigNum.len + 1) * sizeof(char));
                for (i = 0; i < len; ++i) {
                    temp = digits[i] + bigNum.digits[i] + carry;
                    ret.digits[i] = temp % 10;
                    carry = temp / 10;
                }
                for (; i < bigNum.len; ++i) {
                    temp = bigNum.digits[i] + carry;
                    ret.digits[i] = temp % 10;
                    carry = temp / 10;
                }
            }
            if (carry != 0) {
                ret.digits[i] = carry;
                ret.len = i + 1;
            }
            else
                ret.len = i;
            ret.isNeg = isNeg;
            makeStrNum(ret);
            return ret;
        }
    }

    void operator+=(const BigNum& bigNum) {
        *this = *this + bigNum;
    }

    BigNum operator-(const BigNum& bigNum) const {
        if (strNum[0] == '0') // TODO: else / 0
            return -bigNum;
        else if (bigNum.strNum[0] == '0')
            return *this;
        else if (!isNeg && bigNum.isNeg)
            return *this + -bigNum;
        else if (isNeg && !bigNum.isNeg)
            return -(-*this + bigNum);
        else if (isNeg && bigNum.isNeg)
            return -bigNum - -*this;
        else {
            switch (compare(bigNum)) {
                case 0:
                    return BigNum("0");
                case -1:
                    return -(bigNum - *this);
                default:
                    char temp[len];
                    bool isCarry = false;
                    size_t i;
                    for (i = 0; i < bigNum.len; ++i) {
                        if (digits[i] < bigNum.digits[i]) {
                            temp[i] = digits[i] + 10 - bigNum.digits[i] - isCarry;
                            isCarry = true;
                        }
                        else if (digits[i] == bigNum.digits[i]) {
                            if (isCarry) {
                                temp[i] = '\11';
                                isCarry = true;
                            }
                            else {
                                temp[i] = '\0';
                                isCarry = false;
                            }
                        }
                        else {
                            temp[i] = digits[i] - bigNum.digits[i] - isCarry;
                            isCarry = false;
                        }
                    }
                    if (isCarry)
                        for (; i < len;) {
                            if (digits[i] == '\0')
                                temp[i] = '\11';
                            else {
                                temp[i] = digits[i] - '\x01';
                                ++i;
                                break;
                            }
                            ++i;
                        }
                    for (; i < len; ++i)
                        temp[i] = digits[i];
                    while (temp[--i] == 0);
                    return BigNum(temp, i + 1, false);
            }
        }
    }

    void operator-=(const BigNum& bigNum) {
        *this = *this - bigNum;
    }

    BigNum operator*(const BigNum& bigNum) {
        if (strNum[0] == '0' || bigNum.strNum[0] == '0')
            return BigNum();
        if (isNeg != bigNum.isNeg) {
            if (isNeg)
                return -(-*this * bigNum);
            return -(*this * -bigNum);
        }
        else {
            BigNum ret;
            if (len < bigNum.len) {
                for (size_t i = 0; i < len; ++i)
                    ret += multiplySingle(digits[i], bigNum, i);
                return ret;
            }
            else {
                for (size_t i = 0; i < bigNum.len; ++i)
                    ret += multiplySingle(bigNum.digits[i], *this, i);
                return ret;
            }
        }
    }

    BigNum& operator*=(const BigNum& bigNum) {
        *this = *this * bigNum;
        return *this;
    }

    BigNum operator/(const BigNum& bigNum) {
        if (bigNum.strNum[0] == '0')
            return BigNum("NaN");
        if (strNum[0] == '0')
            return BigNum();
        if (isNeg != bigNum.isNeg) {
            if (isNeg)
                return -(-*this / bigNum);
            return -(*this / -bigNum);
        }
        switch (this->compare(bigNum)) {
            case 0:
                return BigNum("1");
            case -1:
                return BigNum();
        }
        
        long long lowerBound, upperBound, mid;
        size_t factorial = len - bigNum.len;
        if (digits[len - 1] > bigNum.digits[bigNum.len - 1]) {
            lowerBound = std::pow(10, factorial);
            upperBound = (digits[len - 1] / bigNum.digits[bigNum.len - 1] + 1) * lowerBound;
        }
        else {
            lowerBound = std::pow(10, factorial == 0 ? factorial : factorial - 1);
            upperBound = 20 * (lowerBound == 0 ? 1 : lowerBound);
        }
        while (lowerBound < upperBound) {
            mid = lowerBound + ((upperBound - lowerBound) >> 1);
            if (BigNum(mid) * bigNum > *this)
                upperBound = mid;
            else
                lowerBound = mid + 1;
        }
        return BigNum(lowerBound - 1);
    }

    static const char* getStrNum(const BigNum& bigNum) {
        return bigNum.strNum;
    }

private:
    void copyDigits(const BigNum& bigNum) {
        len = bigNum.len;
        digits = (char*)malloc(len * sizeof(char));
        memcpy(digits, bigNum.digits, len);
        isNeg = bigNum.isNeg;
    }

    void copyStr(const BigNum& bigNum) {
        strLen = bigNum.strLen;
        strNum = (char*)malloc((strLen + 1) * sizeof(char));
        memcpy(strNum, bigNum.strNum, strLen);
        strNum[strLen] = 0;
    }

    void copyFromStr(const char* num) {
        strLen = strlen(num);
        strNum = (char*)malloc((strLen + 1) * sizeof(char));
        memcpy(strNum, num, strLen);
        strNum[strLen] = 0;
        if (num[0] == '-') {
            len = strLen - 1;
            isNeg = true;
        } else {
            len = strLen;
            isNeg = false;
        }
        digits = (char*)malloc(len * sizeof(char));
        for (size_t i = 0; i < len; ++i)
            digits[i] = num[strLen - i - 1] - '0';
    }

    void copyDigitsFromDigits(const char* digitArr, size_t arrLen) {
        len = arrLen;
        digits = (char*)malloc(len * sizeof(char));
        for (size_t i = 0; i < len; ++i)
            digits[i] = digitArr[i];
    }

    void copyStrFromDigits(const char* digitArr, size_t arrLen) {
        if (isNeg) {
            strLen = arrLen + 1;
            strNum = (char*)malloc((strLen + 1) * sizeof(char));
            strNum[0] = '-';
            for (size_t i = 1; i < strLen; ++i)
                strNum[i] = digitArr[arrLen - i] + '0';
        }
        else {
            strLen = arrLen;
            strNum = (char*)malloc((strLen + 1) * sizeof(char));
            for (size_t i = 0; i < strLen; ++i)
                strNum[i] = digitArr[arrLen - i - 1] + '0';
        }
        strNum[strLen] = '\0';
    }

    static void makeStrNum(BigNum& bigNum) {
        if (bigNum.isNeg) {
            bigNum.strLen = bigNum.len + 1;
            bigNum.strNum = (char*)malloc((bigNum.strLen + 1) * sizeof(char));
            bigNum.strNum[0] = '-';
            for (size_t i = 1; i < bigNum.strLen; ++i)
                bigNum.strNum[i] = bigNum.digits[bigNum.len - i] + '0';
        }
        else {
            bigNum.strLen = bigNum.len;
            bigNum.strNum = (char*)malloc((bigNum.strLen + 1) * sizeof(char));
            for (size_t i = 0; i < bigNum.strLen; ++i)
                bigNum.strNum[i] = bigNum.digits[bigNum.len - i - 1] + '0';
        }
        bigNum.strNum[bigNum.strLen] = '0';
    }

    void autoFree() {
        if (len != 0)
            free((void*)digits);
        if (strLen != 0)
            free((void*)strNum);
    }

    BigNum(bool) {
        isNeg = false;
        len = strLen = 0;
        digits = 0;
        strNum = 0;
    }

    static BigNum multiplySingle(const char& digit, const BigNum& bigNum, size_t factorial) {
        char temp[bigNum.len + factorial + 1], carry = 0, product;
        memset(temp, 0, factorial);
        size_t i;
        for (i = factorial; i < bigNum.len + factorial; ++i) {
            product = digit * bigNum.digits[i - factorial];
            temp[i] = (product + carry) % 10;
            carry = (product + carry) / 10;
        }
        if (carry != 0)
            temp[i] = carry;
        else
            --i;
        return BigNum(temp, i + 1, false);
    }

private:
    bool isNeg;
    char* strNum;
    size_t len;
    char* digits;
    size_t strLen;
};


/*
    BigNum operator+(const BigNum& bigNum) const {
        if (digits[len - 1] == 0)
            return bigNum;
        else if(*this == -bigNum)
            return BigNum("0");
        else if (bigNum.digits[bigNum.len - 1] == 0)
            return *this;
        else if (digits[len - 1] > 0 && bigNum.digits[bigNum.len - 1] < 0)
            return *this - -bigNum;
        else if (digits[len - 1] < 0 && bigNum.digits[bigNum.len - 1] > 0)
            return bigNum - -*this;
        BigNum ret;
        int shorter, longer, i = 0;
        if (len > bigNum.len) {
            shorter = bigNum.len;
            longer = len;
        }
        else {
            shorter = len;
            longer = bigNum.len;
        }
        char temp, carry = 0;
        for (; i < shorter - 1; ++i) {
            temp = digits[i] + bigNum.digits[i] + carry;
            ret.digits[ret.len++] = temp % 10;
            carry = temp / 10;
        }
        if (digits[len - 1] < 0) {
            if (digits[shorter - 1] < 0 && bigNum.digits[shorter - 1] < 0) {
                temp = digits[shorter - 1] + bigNum.digits[shorter - 1] - carry;
            }
            else if (digits[shorter - 1] < 0) {
                temp = digits[shorter - 1] - bigNum.digits[shorter - 1] - carry;
            }
            else {
                temp = -digits[shorter - 1] + bigNum.digits[shorter - 1] - carry;
            }
            ret.digits[ret.len++] = -temp % 10;
            carry = temp / 10;
        }
        else {
            temp = digits[shorter - 1] + bigNum.digits[shorter - 1] + carry;
            ret.digits[ret.len++] = temp % 10;
            carry = temp / 10;
        }
        if (shorter != longer && carry < 0)
            carry = -carry;
        for (++i; i < longer - 1; ++i) {
            temp = digits[i] + bigNum.digits[i] + carry;
            ret.digits[ret.len++] = temp % 10;
            carry = temp / 10;
        }
        if (shorter != longer) {
            if (digits[len - 1] < 0) {
                if (digits[longer - 1] < 0 && bigNum.digits[longer - 1] < 0) {
                    temp = digits[longer - 1] + bigNum.digits[longer - 1] - carry;
                }
                else if (digits[longer - 1] < 0) {
                    temp = digits[longer - 1] - bigNum.digits[longer - 1] - carry;
                }
                else {
                    temp = -digits[longer - 1] + bigNum.digits[longer - 1] - carry;
                }
                ret.digits[ret.len++] = -temp % 10;
                carry = temp / 10;
            }
            else {
                temp = digits[longer - 1] + bigNum.digits[longer - 1] + carry;
                ret.digits[ret.len++] = temp % 10;
                carry = temp / 10;
            }
        }
        if (carry != 0) {
            ret.digits[ret.len++] = carry;
        }
        else if (digits[len - 1] < 0)
            ret.digits[ret.len - 1] *= -1;
        ret.makeStrNum();
        return ret;
    }
*/


/*
    BigNum operator-(const BigNum& bigNum) const {
        BigNum ret;
        bool isCarry = false;
        for (int i = 0; i < len || i < bigNum.len; ++i) {
            if (digits[i] > bigNum.digits[i]) {
                if (isCarry)
                    ret.digits[ret.len++] = bigNum.digits[i] + 9 - digits[i];
                else
                    ret.digits[ret.len++] = bigNum.digits[i] + 10 - digits[i];
                if (bigNum.digits[i + 1] > 0)
                    isCarry = true;
                else
                    isCarry = false;
            }
            else {
                if (isCarry)
                    ret.digits[ret.len++] = bigNum.digits[i] - 1 - digits[i];
                else
                    ret.digits[ret.len++] = bigNum.digits[i] - digits[i];
            }
        }
        ret.makeStrNum();
        return ret;
    }
    */

/*
bool operator>(const BigNum& bigNum) const {
        if (digits[len - 1] == '\0')
            return bigNum.isNeg;
        else if (bigNum.digits[bigNum.len - 1] == '\0')
            return !isNeg;
        else if (isNeg && !bigNum.isNeg)
            return false;
        else if (!isNeg && bigNum.isNeg)
            return true;
        else if (len > bigNum.len)
            return !isNeg;
        else if (len < bigNum.len)
            return isNeg;
        else {
            for (int i = len - 1; i >= 0; --i) {
                if (digits[i] > bigNum.digits[i])
                    return !isNeg;
                else if (digits[i] < bigNum.digits[i])
                    return isNeg;
            }
            return false;
        }
    }

    bool operator<(const BigNum& bigNum) const {
        if (bigNum.digits[bigNum.len - 1] == '\0')
            return isNeg;
        else if (digits[len - 1] == '\0')
            return !bigNum.isNeg;
        else if (isNeg && !bigNum.isNeg)
            return true;
        else if (!isNeg && bigNum.isNeg)
            return false;
        else if (len > bigNum.len)
            return isNeg;
        else if (len < bigNum.len)
            return !isNeg;
        else {
            for (int i = len - 1; i >= 0; --i) {
                if (digits[i] > bigNum.digits[i])
                    return isNeg;
                else if (digits[i] < bigNum.digits[i])
                    return !isNeg;
            }
            return false;
        }
    }

    bool operator==(const BigNum& bigNum) const {
        if (this == &bigNum)
            return true;
        if (isNeg != bigNum.isNeg)
            return false;
        if (len != bigNum.len)
            return false;
        if (strLen != bigNum.strLen)
            return false;
        for (int i = len - 1; i >= 0; --i)
            if (digits[i] != bigNum.digits[i])
                return false;
        for (int i = 0; i < strLen; ++i)
            if (strNum[i] != bigNum.strNum[i])
                return false;
        return true;
    }

    bool operator>=(const BigNum& bigNum) const {
        if (this == &bigNum)
            return true;
        if (bigNum.digits[bigNum.len - 1] == '\0')
            return !isNeg;
        else if (digits[len - 1] == '\0')
            return bigNum.isNeg;
        else if (isNeg && !bigNum.isNeg)
            return false;
        else if (!isNeg && bigNum.isNeg)
            return true;
        else if (len > bigNum.len)
            return !isNeg;
        else if (len < bigNum.len)
            return isNeg;
        else {
            for (int i = len - 1; i >= 0; --i) {
                if (digits[i] > bigNum.digits[i])
                    return !isNeg;
                else if (digits[i] < bigNum.digits[i])
                    return isNeg;
            }
            return true;
        }
    }

    bool operator<=(const BigNum& bigNum) const {
        if (this == &bigNum)
            return true;
        else if (digits[len - 1] == '\0')
            return !bigNum.isNeg;
        if (bigNum.digits[bigNum.len - 1] == '\0')
            return isNeg;
        else if (isNeg && !bigNum.isNeg)
            return true;
        else if (!isNeg && bigNum.isNeg)
            return false;
        else if (len > bigNum.len)
            return isNeg;
        else if (len < bigNum.len)
            return !isNeg;
        else {
            for (int i = len - 1; i >= 0; --i) {
                if (digits[i] > bigNum.digits[i])
                    return isNeg;
                else if (digits[i] < bigNum.digits[i])
                    return !isNeg;
            }
            return true;
        }
    }
*/
