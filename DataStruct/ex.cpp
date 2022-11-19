#include <vector>
#include <string>
#include <climits>
#include <algorithm>
#include <unordered_map>
using namespace std;

int totalFruit(vector<int>& fruits) {
    unordered_map<int, int> count;
    int slow = 0;
    for (int i = 0; i < fruits.size(); ++i) {
        ++count[fruits[i]];
        while (count.size() > 2) {
            if (--count[fruits[slow]] == 0)
                count.erase(fruits[slow]);
            ++slow;
        }
    }
    return fruits.size() - slow;
}
