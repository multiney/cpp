#include <cstring>
#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <algorithm>
#include <unordered_map>
#include <set>
#include <unordered_set>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
    int ret = 0;
    std::unordered_map<int, int> map;
    for (int i : nums1)
        for (int j : nums2)
            ++map[i + j];
    for (int i : nums3)
        for (int j : nums4)
            if (map.find(-(i + j)) != map.end())
                ret += map[-(i + j)];
    return ret;
}
