#ifndef STRING_H_
#define STRING_H_

#include <iostream>

using std::istream;
using std::ostream;

class String
{
private:
    char * str;                 // pointer to string
    int len;                    // length of string
    static const int CINLIM = 80; // cin input limit
public:
// constructors and other methods
    String(const char * s = nullptr); // (default) constructor
    String(const String &); // copy constructor
    String(String &&st);
    ~String();
    int length () const { return len; }
    int size() const { return len; }
// overloaded operator methods
    String & operator=(const String & st);
    String & operator=(const char * s);
    String & operator=(String &&st);
    char & operator[](int i);
    const char & operator[](int i) const;
    String operator+(const String &st);
    String & operator+=(const String &st);
    String operator+(const char *s);
    String & operator+=(const char *s);

// overloaded operator friends
    friend bool operator<(const String &st1, const String &st2);
    friend bool operator>(const String &st1, const String &st2);
    friend bool operator==(const String &st1, const String &st2);
    friend bool operator!=(const String &st1, const String &st2);
    friend ostream & operator<<(ostream & os, const String & st);
    friend istream & operator>>(istream & is, String & st);
    friend void printAddr(const String &st);
public:
    // function
    void append(const String &st);
    void append(const char *s);

    void push_back(const char ch);
    void swap(char * &s);
    void swap(String &st);
    int find(const char *s, size_t index);
    int find(const String &st, size_t index);
private:
    String(bool isAlloc) {} // inner constructor
    
};
#endif // STRING_H_
