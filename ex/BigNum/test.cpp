#include <climits>
#include <cstring>
#include <ios>
#include <stdio.h>
#include <string>
#include <iostream>

#include "BigInt.hpp"
#include "./bignum.h"

using std::cout;
using std::endl;

static int main_ret = 0;
static int test_count = 0;
static int pass_count = 0;

#define EXPECT_EQ_BASE(equality, expect, actual, format)\
    do {\
        ++test_count;\
        if (equality)\
            ++pass_count;\
        else {\
            fprintf(stderr, "%s:%d: expect: " format " actual: " format "\n", __FUNCTION__, __LINE__, expect, actual);\
            main_ret = 1;\
        }\
    } while(0)

#define EXPECT_TRUE(actual) EXPECT_EQ_BASE(actual != 0, "true", "false", "%s")
#define EXPECT_FALSE(actual) EXPECT_EQ_BASE(actual == 0, "false", "true", "%s")
#define EXPECT_EQ_STRING(expect, actual) EXPECT_EQ_BASE(strlen(expect) == strlen(actual) && memcmp(expect, actual, strlen(expect)) == 0, expect, actual, "%s")
#define EXPECT_EQ_BIGNUM(expect, actual)\
    do {\
        int record_pass = pass_count;\
        EXPECT_EQ_STRING(BigNum::getStrNum(expect), BigNum::getStrNum(actual));\
        if (record_pass == pass_count)\
            break;\
        --test_count;\
        --pass_count;\
        EXPECT_EQ_BASE(expect == actual, "equal", "not equal", "%s");\
    } while(0)
/*
void EXPECT_EQ_BIGNUM(const char* expect, BigNum actual) {
    ++test_count;
    if (strlen(expect) == strlen(actual.getStrNum()) && memcmp(expect, actual.getStrNum(), strlen(expect)) == 0)
        ++pass_count;
    else {
        fprintf(stderr, "%s:%d: expect: %s actual: %s\n", __FUNCTION__, __LINE__, expect, actual.getStrNum());
        main_ret = 1;
    }
}
*/

BigNum a("0"), b("7878787878"), c("-7878787878"), d("-123456789"),
           e("123456789"), f("-123456788"), g("123456780"), h("9"), i("-2"), j("0"), k("7878787878"), l("1000000008"), m("-9"), n("10000000008")
           , o("999999999"), p("9111111");

BigInt A("0"), B("7878787878"), C("-7878787878"), D("-123456789"),
           E("123456789"), F("-123456788"), G("123456780"), H("9"), I("-2"), J("0"), K("7878787878"), L("1000000008"), M("-9"), N("10000000008");

static void test_constructor() {
    EXPECT_EQ_STRING("0", a.getStrNum());
    EXPECT_EQ_STRING("7878787878", b.getStrNum());
    EXPECT_EQ_STRING("-123456789", d.getStrNum());
    BigNum aCopy = a;
    EXPECT_EQ_BIGNUM(a, aCopy);
    BigNum bCopy = b;
    EXPECT_EQ_BIGNUM(b, bCopy);
    BigNum cCopy = c;
    EXPECT_EQ_BIGNUM(c, cCopy);
    // 0
    EXPECT_EQ_BIGNUM(a, BigNum(0ll));
    // pos
    EXPECT_EQ_BIGNUM(b, BigNum(7878787878ll));
    // neg
    EXPECT_EQ_BIGNUM(d, BigNum(-123456789ll));
}

static void test_is_equal() {
    EXPECT_TRUE(a == a);
    EXPECT_TRUE(b == b);
    EXPECT_TRUE(a == j);
    EXPECT_TRUE(b == k);
    EXPECT_FALSE(a == b);
}

static void test_assignment() {
    // test the same src
    a = a;
    EXPECT_EQ_STRING("0", a.getStrNum());
    // test diff src
    BigNum aCopy = a;
    aCopy = b;
    EXPECT_EQ_BIGNUM(b, aCopy);
    // not assign first, then assigned from pos, neg, and zero
    BigNum temp;
    EXPECT_EQ_BIGNUM(a, temp);
    BigNum temp2;
    temp2 = b;
    EXPECT_EQ_BIGNUM(b, temp2);
    BigNum temp3;
    temp3 = c;
    EXPECT_EQ_BIGNUM(c, temp3);
    // assigned from const char*
    temp3 = "1234";
    BigNum expect3("1234");
    EXPECT_EQ_BIGNUM(expect3, temp3);
}

static void test_is_greater_than() {
    // same > same
    EXPECT_FALSE(a > a);
    EXPECT_FALSE(b > b);
    EXPECT_FALSE(c > c);
    // pos > 0
    EXPECT_TRUE(b > a);
    EXPECT_TRUE(h > a);
    // pos > neg
    EXPECT_TRUE(b > c);
    // 0 > neg
    EXPECT_TRUE(a > c);
    EXPECT_TRUE(a > i);
    // pos > pos
    EXPECT_TRUE(b > e);
    EXPECT_TRUE(e > g);
    EXPECT_TRUE(g > a);
    // neg > neg
    EXPECT_TRUE(f > c);
    EXPECT_TRUE(f > d);
}

static void test_is_less_than() {
    // same < same
    EXPECT_FALSE(a < a);
    EXPECT_FALSE(b < b);
    EXPECT_FALSE(c < c);
    // pos < 0
    EXPECT_FALSE(b < a);
    EXPECT_FALSE(h < a);
    // pos < neg
    EXPECT_FALSE(b < c);
    // 0 < neg
    EXPECT_FALSE(a < c);
    EXPECT_FALSE(a < i);
    // pos < pos
    EXPECT_FALSE(b < e);
    EXPECT_FALSE(e < g);
    // neg < neg
    EXPECT_FALSE(f < c);
    EXPECT_FALSE(f < d);
}

static void test_is_greater_than_or_equal() {
    // same >= same
    EXPECT_TRUE(a >= a);
    EXPECT_TRUE(b >= b);
    EXPECT_TRUE(c >= c);
    // pos >= 0
    EXPECT_TRUE(b >= a);
    EXPECT_TRUE(h >= a);
    // pos >= neg
    EXPECT_TRUE(b >= c);
    // 0 >= neg
    EXPECT_TRUE(a >= c);
    EXPECT_TRUE(a >= i);
    // pos >= pos
    EXPECT_TRUE(b >= e);
    EXPECT_TRUE(e >= g);
    // neg >= neg
    EXPECT_TRUE(f >= c);
    EXPECT_TRUE(f >= d);
}

static void test_is_less_than_or_equal() {
    // same <= same
    EXPECT_TRUE(a <= a);
    EXPECT_TRUE(b <= b);
    EXPECT_TRUE(c <= c);
    // pos <= 0
    EXPECT_FALSE(b <= a);
    EXPECT_FALSE(h <= a);
    // pos <= neg
    EXPECT_FALSE(b <= c);
    // 0 <= neg
    EXPECT_FALSE(a <= c);
    EXPECT_FALSE(a <= i);
    // pos <= pos
    EXPECT_FALSE(b <= e);
    EXPECT_FALSE(e <= g);
    // neg <= neg
    EXPECT_FALSE(f <= c);
    EXPECT_FALSE(f <= d);
}

static void test_unary_neg() {
    // -0
    EXPECT_EQ_BIGNUM(BigNum("0"), -a);
    // -pos
    EXPECT_EQ_BIGNUM(BigNum("-7878787878"), -b);
    // -neg
    EXPECT_EQ_BIGNUM(BigNum("123456789"), -d);
}

static void test_add() {
    // 0 + 0
    EXPECT_EQ_BIGNUM(a, a + a);
    // 0 + pos
    EXPECT_EQ_BIGNUM(BigNum("7878787878"), a + b);
    // pos + 0
    EXPECT_EQ_BIGNUM(BigNum("7878787878"), b + a);
    // 0 + neg
    EXPECT_EQ_BIGNUM(BigNum("-123456789"), a + d);
    // neg + 0
    EXPECT_EQ_BIGNUM(BigNum("-7878787878"), c + a);
    // pos + pos
    EXPECT_EQ_BIGNUM(BigNum("15757575756"), b + b);
    EXPECT_EQ_BIGNUM(BigNum("8002244667"), b + e);
    // neg + neg
    EXPECT_EQ_BIGNUM(BigNum("-15757575756"), c + c);
    EXPECT_EQ_BIGNUM(BigNum("-8002244667"), c + d);

    // pos + neg
    EXPECT_EQ_BIGNUM(BigNum("0"), b + c);
    EXPECT_EQ_BIGNUM(BigNum("7755331089"), b + d);
    EXPECT_EQ_BIGNUM(BigNum("-7755331089"), e + c);
    EXPECT_EQ_BIGNUM(BigNum("7"), h + i);
    EXPECT_EQ_BIGNUM(BigNum("-123456780"), h + d);
    EXPECT_EQ_BIGNUM(BigNum("999999999"), l + m);
    // neg + pos
    EXPECT_EQ_BIGNUM(BigNum("0"), c + b);
    EXPECT_EQ_BIGNUM(BigNum("7755331089"), d + b);
    EXPECT_EQ_BIGNUM(BigNum("-7755331089"), c + e);
    EXPECT_EQ_BIGNUM(BigNum("7"), i + h);
    EXPECT_EQ_BIGNUM(BigNum("-123456780"), d + h);
    EXPECT_EQ_BIGNUM(BigNum("999999999"), m + l);
}

static void test_sub() {
    // 0 - 0
    EXPECT_EQ_BIGNUM(a, a - a);
    // 0 - pos
    EXPECT_EQ_BIGNUM(BigNum("-7878787878"), a - b);
    // pos - 0
    EXPECT_EQ_BIGNUM(BigNum("7878787878"), b - a);
    // 0 - neg
    EXPECT_EQ_BIGNUM(BigNum("123456789"), a - d);
    // neg - 0
    EXPECT_EQ_BIGNUM(BigNum("-123456789"), d - a);
    // pos - pos: big - small
    EXPECT_EQ_BIGNUM(BigNum("7755331089"), b - e);
    EXPECT_EQ_BIGNUM(BigNum("7755331098"), b - g);
    EXPECT_EQ_BIGNUM(BigNum("9"), e - g);
    EXPECT_EQ_BIGNUM(BigNum("2121212130"), n - b);
    EXPECT_EQ_BIGNUM(BigNum("6878787870"), b - l);
    // pos - pos: same - same
    EXPECT_EQ_BIGNUM(BigNum("0"), b - b);
    // pos - pos: small - big
    EXPECT_EQ_BIGNUM(BigNum("-7755331089"), e - b);
    EXPECT_EQ_BIGNUM(BigNum("-7755331098"), g - b);
    EXPECT_EQ_BIGNUM(BigNum("-9"), g - e);
    EXPECT_EQ_BIGNUM(BigNum("-2121212130"), b - n);
    EXPECT_EQ_BIGNUM(BigNum("-6878787870"), l - b);
    // neg - neg: big - small
    EXPECT_EQ_BIGNUM(BigNum("7755331089"), d - c);
    EXPECT_EQ_BIGNUM(BigNum("123456779"), m - f);
    // neg - neg: same - same
    EXPECT_EQ_BIGNUM(BigNum("0"), f - f);
    // neg - neg: small - big
    EXPECT_EQ_BIGNUM(BigNum("-7755331090"), c - f);
}

static void test_multiply() {
    // 0 * 0
    EXPECT_EQ_BIGNUM(BigNum("0"), a * a);
    // 0 * else
    EXPECT_EQ_BIGNUM(BigNum("0"), a * b); // 0 * pos
    EXPECT_EQ_BIGNUM(BigNum("0"), a * c); // 0 * neg
    // else * 0
    EXPECT_EQ_BIGNUM(BigNum("0"), h * a); // pos * 0
    EXPECT_EQ_BIGNUM(BigNum("0"), g * a); // neg * 0
    // pos * pos
    EXPECT_EQ_BIGNUM(BigNum("9000000072"), l * h);
    EXPECT_EQ_BIGNUM(BigNum("9000000072"), h * l);
    EXPECT_EQ_BIGNUM(BigNum("972689852630003742"), b * e);
    EXPECT_EQ_BIGNUM(BigNum("62075298426519742884"), b * b);
    // neg * neg
    EXPECT_EQ_BIGNUM(BigNum("15241578503276944"), f * f);
    // pos * neg
    EXPECT_EQ_BIGNUM(BigNum("-972689852630003742"), b * d);
}

static void test_divide() {
    // 0 / pos
    EXPECT_EQ_BIGNUM(BigNum("0"), a / b);
    // 0 / neg
    EXPECT_EQ_BIGNUM(BigNum("0"), a / d);
    // TODO:else / 0
    //EXPECT_EQ_BIGNUM(BigNum("NaN"), a / a);
    // pos / pos
    EXPECT_EQ_BIGNUM(BigNum("875420875"), b / h);
    EXPECT_EQ_BIGNUM(BigNum("1"), b / b);
    EXPECT_EQ_BIGNUM(BigNum("0"), b / n);
    EXPECT_EQ_BIGNUM(BigNum("1"), e / g);
    EXPECT_EQ_BIGNUM(BigNum("0"), g / e);
    EXPECT_EQ_BIGNUM(BigNum("63"), b / g);
    EXPECT_EQ_BIGNUM(BigNum("109"), o / p);
    // pos / neg
    EXPECT_EQ_BIGNUM(BigNum("-63"), b / -g);
}

int main (int argc, char *argv[])
{
    /*
    test_constructor();
    test_is_equal();
    test_assignment();
    test_is_greater_than();
    test_is_less_than();
    test_is_greater_than_or_equal();
    test_is_less_than_or_equal();
    test_unary_neg();
    test_add();
    test_sub();
    test_multiply();
    test_divide();

    printf("%d/%d (%3.2f%%) passed\n", pass_count, test_count, pass_count * 100.0 / test_count);
    */
    BigNum base("2");
    BigNum ret("1");
    for (int i = 0; i < 1000; ++i)
        ret = ret * base;
    ret.print();
    cout << std::strlen(ret.getStrNum()) << endl;
    /*
    BigInt base("2");
    BigInt ret("1");
    for (int i = 0; i < 1000; ++i)
        ret *= base;
        */
    return main_ret;
}
