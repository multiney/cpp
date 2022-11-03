#include <algorithm>
#include <cstring>   // string.h for some
#include "String.h"  // include <iostream>

using std::cout;
using std::endl;

// static method
void String::append(const String &st) {
    *this += st;
}

void String::append(const char *s) {
    *this += s;
}

void String::push_back(const char ch) {
    *this += &ch;
}

/*
void String::swap(char * &s) {
    cout << s << endl;
    if (*this == s)
        return;
    auto sLen = std::strlen(s);
    if (len < sLen) {
        len = sLen;
        char *temp = new char[len + 1];
        std::strcpy(temp, s);
        std::strcpy(s, str);
        delete [] str;
        str = temp;
    }
    else if (len == sLen) {
        char temp[sLen + 1];
        std::strcpy(temp, str);
        std::strcpy(str, s);
        s = temp;
    }
    else {
        char temp[len + 1];
        std::strcpy(temp, str);
        std::strcpy(str, s);
        s = temp;
        len = sLen;
    }
}
*/

// TODO: valgrind error ...
void String::swap(char * &s) {
    if (*this == s)
        return;
    char temp[len + 1];
    std::strcpy(temp, str);
    len = std::strlen(s);
    delete [] str;
    str = new char[len + 1];
    std::strcpy(str, s);
    s = temp;
}

void String::swap(String &st) {
    std::swap(len, st.len);
    std::swap(str, st.str);
}

/*
int String::find(const char *s, size_t index) {
    size_t sLen = strlen(s);
    if (sLen == 0 || index < 0 || index + sLen > len)
        return -1;
    for (int i = index; i <= (len - sLen); ++i) {
        if (std::memcmp(str + i, s, sLen) == 0)
            return i;
    }
    return -1;
}
*/

void getNext(int *next, const char *s) {
    size_t sLen = strlen(s);
    int j = -1;
    next[0] = j;
    for (int i = 1; i < sLen; ++i) {
        while (j >= 0 && s[i] != s[j + 1])
            j = next[j];
        if (s[i] == s[j + 1])
            ++j;
        next[i] = j;
    }
}

int String::find(const char *s, size_t index) {
    size_t nextLen = std::strlen(s);
    if (nextLen == 0)
        return 0;
    int j = -1;
    int next[nextLen];
    getNext(next, s);
    for (int i = index; i < len; ++i) {
        while (j >= 0 && str[i] != s[j + 1])
            j = next[j];
        if (str[i] == s[j + 1])
            ++j;
        if (j == nextLen - 1)
            return i - nextLen + 1;
    }
    return -1;
}

int String::find(const String &st, size_t index) {
    return find(st.str, index);
}

void printAddr(const String &st) {
    cout << (void*) st.str << endl;
}

// class method

String::String(const char * s) { // construct String from C string
    if (s == nullptr) {
        len = 0;
        str = new char[1];
        str[0] = '\0';
    }
    else {
        len = std::strlen(s);
        str = new char[len + 1];
        std::strcpy(str, s);
    }
}

String::String(const String & st) {
    len = st.len;
    str = new char[len + 1];
    std::strcpy(str, st.str);
}

String::String(String &&st) {
    len = st.len;
    str = st.str;
    st.str = nullptr;
}

String::~String() {
    if (str)
        delete [] str;
}

// overloaded operator methods

// assign a String to a String
String & String::operator=(const String & st) {
    if (*this == st)
        return *this;
    delete [] str;
    len = st.len;
    str = new char[len + 1];
    std::strcpy(str, st.str);
    return *this;
}

// assign a C string to a String
String & String::operator=(const char * s) {
    if (std::strcmp(str, s) == 0)
        return *this;
    len = std::strlen(s);
    delete [] str;
    str = new char[len + 1];
    std::strcpy(str, s);
    return *this;
}

// move assign
String & String::operator=(String &&st) {
    if (*this != st) {
        delete [] str;
        len = st.len;
        str = st.str;
        st.str = nullptr;
    }
    cout << "move assignment" << endl;
    return *this;
}

// read-write char access for non-const String
char & String::operator[](int i) {
    return str[i];
}

// read-only char access for const String
const char & String::operator[](int i) const {
    return str[i];
}

String String::operator+(const String & st) {
    String ret(false);
    ret.len = len + st.len;
    ret.str = new char[ret.len + 1];
    std::strcpy(ret.str, str);
    std::strcat(ret.str, st.str);
    return ret;
}

String & String::operator+=(const String &st) {
    len += st.len;
    char *temp = new char[len + 1];
    std::strcpy(temp, str);
    std::strcat(temp, st.str);
    delete [] str;
    str = temp;
    return *this;
}

String String::operator+(const char * s) {
    String ret(false);
    ret.len = len + strlen(s);
    ret.str = new char[ret.len + 1];
    std::strcpy(ret.str, str);
    std::strcat(ret.str, s);
    return ret;
}

String & String::operator+=(const char *s) {
    len += strlen(s);
    char *temp = new char[len + 1];
    std::strcpy(temp, str);
    std::strcat(temp, s);
    delete [] str;
    str = temp;
    return *this;
}

// overloaded operator friends

bool operator<(const String &st1, const String &st2) {
    return std::strcmp(st1.str, st2.str) < 0;
}

bool operator>(const String &st1, const String &st2) {
    return std::strcmp(st1.str, st2.str) > 0;
}

bool operator==(const String &st1, const String &st2) {
    if (&st1 == &st2)
        return true;
    return std::strcmp(st1.str, st2.str) == 0;
}

bool operator!=(const String &st1, const String &st2) {
    if (&st1 != &st2)
        return true;
    return std::strcmp(st1.str, st2.str) != 0;
}

// simple String output
ostream & operator<<(ostream & os, const String & st) {
    // TODO: 底层实现?
    os << st.str;
    return os;
}

// quick and dirty String input
istream & operator>>(istream &is, String &st) {
    char temp[String::CINLIM];
    is.get(temp, String::CINLIM);
    if (is)
        st = temp;
    while (is && is.get() != '\n')
        continue;
    return is;
}
