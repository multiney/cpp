#include "String.h"

#include <cstring>
#include <ios>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

void test_add() {
    String s1("123");
    String s2("456");
    cout << (s1 = s1 + s2 + "789") << endl;
}

// TODO: fix valgrind error
void test_char_swap() {
    String s("123");
    char *cs = (char*) "234";
    s.swap(cs);
    cout << s << "<==>" << cs << endl;
}

void test_String_swap() {
    String s1("123");
    String s2("456");
    s1.swap(s2);
    cout << "s1: " << s1 << ", s2: " << s2 << endl;
}

void test_assign() {
    String s1("hello");
    String s2, s3;
    s2 = s1;
    s3 = String("world");
    cout << s1 << ", " << s2 << ", " << s3 << endl;
}

void test_find() {
    String s1("hello world, my c plus plus!");
    int ret = s1.find("world", 7);
    cout << ret << endl;
}

void test_String_find() {
    String s("hello world, my c plus plus!");
    int ret = s.find(String("world"), 6);
    cout << ret << endl;
}

class Solution {
public:
    void getNext(int *next, const string& s) {
        int j = 0;
        next[0] = j;
        for (int i = 1; i < s.size(); ++i) {
            while (j > 0 && s[i] != s[j])
                j = next[j - 1];
            if (s[i] == s[j])
                ++j;
            next[i] = j;
        }
    }
    int strStr(string haystack, string needle) {
        if (needle.size() == 0)
            return 0;
        int j = 0;
        int next[needle.size()];
        getNext(next, needle);
        for (int i = 0; i < haystack.size(); ++i) {
            while (j > 0 && haystack[i] != needle[j])
                j = next[j - 1];
            if (haystack[i] == needle[j])
                ++j;
            if (j == needle.size())
                return i - needle.size() + 1;
        }
        return -1;
    }
};


int main (int argc, char *argv[])
{
    //test_add();
    //test_char_swap();
    //test_String_swap();
    //test_assign();
    //test_find();
    test_String_find();
}
