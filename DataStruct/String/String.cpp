#include <vector>
#include <string>
#include <algorithm>

using std::vector;
using std::string;

/*
 * 344. Reverse String
 *
 * Constraints:
 * 1 <= s.length <= 105
 * s[i] is a printable ascii character.
 */
void reverseString(vector<char> &s) {
    for (int left = 0, right = s.size() - 1; left < right;)
        std::swap(s[left++], s[right--]);
}

/*
 * 541. Reverse String II
 *
 * Constraints:
 * 1 <= s.length <= 104
 * s consists of only lowercase English letters.
 * 1 <= k <= 104
 */
string reverseStr(string s, int k) {
    for (int i = 0; i < s.size(); i = i + 2 * k)
        for (int left = i, right = i + k - 1 < s.size() - 1 ? i + k - 1 : s.size() - 1; left < right; ++left, --right)
            std::swap(s[left], s[right]);
    return s;
}

/*
 * 剑指 Offer 05. 替换空格
 *
 * Constraints:
 * 0 <= s 的长度 <= 10000
 */
string replaceSpace(string s) {
    int count = 0;
    int oldSize = s.size();
    for (auto c : s)
        if (c == ' ')
            ++count;
    s.resize(oldSize + 2 * count);
    int newSize = s.size();
    for (int i = oldSize - 1, j = newSize - 1; i < j; --i, --j) {
        if (s[i] != ' ')
            s[j] = s[i];
        else {
            s[j] = '0';
            s[--j] = '2';
            s[--j] = '%';
        }
    }
    return s;
}

/*
 * 151. Reverse Words in a String
 *
 * Constraints:
 * 1 <= s.length <= 104
 * s contains English letters (upper-case and lower-case), digits, and spaces ' '.
 * There is at least one word in s.
 */
void reverse(string &s, int left, int right) {
    for (;left < right; ++left, --right)
        std::swap(s[left], s[right]);
}

void removeExtraSpaces(string &s) {
    int slow = 0;
    for (int fast = 0; fast < s.size(); ++fast) {
        if (s[fast] != ' ') {
            if (slow) s[slow++] = ' ';
            while (fast < s.size() && s[fast] != ' ')
                s[slow++] = s[fast++];
        }
    }
    s.resize(slow);
}

string reverseWords(string s) {
    removeExtraSpaces(s);
    reverse(s, 0, s.size() - 1);
    int start = 0;
    for (int i = 0; i <= s.size(); ++i) {
        if (s[i] == ' ' || i == s.size()) {
            reverse(s, start, i - 1);
            start = i + 1;
        }
    }
    return s;
}

/*
 * 剑指 Offer 58 - II. 左旋转字符串
 *
 * Constraints:
 * 1 <= k < s.length <= 10000
 */
string reverseLeftWords(string s, int n) {
    std::reverse(s.begin(), s.begin() + n);
    std::reverse(s.begin() + n, s.end());
    std::reverse(s.begin(), s.end());
    return s;
}
string reverseLeftWords2(string s, int n) {
    return (s + s).substr(n, s.size());
}

/*
 * 28. Find the Index of the First Occurrence in a String
 *
 * Constraints:
 * 1 <= haystack.length, needle.length <= 104
 * haystack and needle consist of only lowercase English characters.
 */
void getNext(int *next, const string &s) {
    int j = -1;
    next[0] = -1;
    for (int i = 1; i < s.size(); ++i) {
        while (j >= 0 && s[i] != s[j + 1])
            j = next[j];
        if (s[i] == s[j + 1])
            ++j;
        next[i] = j;
    }
}
int strStr(string haystack, string needle) {
    int next[needle.size()];
    getNext(next, needle);
    for (int i = 0, j = -1; i < haystack.size(); ++i) {
        while (j >= 0 && haystack[i] != needle[j + 1])
            j = next[j];
        if (haystack[i] == needle[j + 1])
            ++j;
        if (j == needle.size() - 1)
            return i - j;
    }
    return -1;
}

/*
 * 459. Repeated Substring Pattern
 *
 * Constraints:
 * 1 <= s.length <= 104
 * s consists of lowercase English letters.
 */
bool repeatedSubstringPattern(string s) {
    string tmp = s + s;
    tmp.erase(tmp.begin());
    tmp.erase(tmp.end() - 1);
    return (tmp.find(s) != string::npos);
}

bool repeatedSubstringPattern2(string s) {
    if (s.size() < 2) return false;
    int next[s.size()];
    getNext(next, s);
    if (next[s.size() - 1] != -1 && s.size() % (s.size() - next[s.size() - 1] - 1) == 0)
        return true;
    return false;
}
