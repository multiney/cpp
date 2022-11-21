#include <vector>
#include <string>
#include <climits>
#include <algorithm>
#include <unordered_map>
using namespace std;

string minWindow(string s, string t) {
    vector<int> map('z' + 1);
    for (char c : t)
        ++map[c];
    int counter = t.size();
    int minLen = INT_MAX;
    int start = 0;
    for (int i = 0, j = 0; j < s.size();) {
        if (map[s[j++]]-- > 0)
            --counter;
        while (counter == 0) {
            minLen = std::min(minLen, j - (start = i));
            if (map[s[i++]]++ >= 0)
                ++counter;
        }
    }
    return minLen == INT_MAX ? "" : s.substr(start, minLen);
}
