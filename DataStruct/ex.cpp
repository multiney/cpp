#include <cstring>
#include <cmath>
#include <ios>
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

vector<vector<int>> fourSum(vector<int>& nums, int target) {
    if (nums.size() < 4) return {};
    vector<vector<int>> ret;
    std::sort(nums.begin(), nums.end());
    for (int i = 0; i < nums.size() - 3; ++i) {
        if (i > 0 && nums[i - 1] == nums[i]) continue;
        if (nums[i] + nums[i + 1] + nums[i + 2] + nums[i + 3] > target) break;
        if (nums[i] + nums[nums.size() - 3] + nums[nums.size() - 2] + nums[nums.size() - 1] < target) break;
        for (int j = i + 1; j < nums.size() - 2; ++j) {
            if (j > i + 2 && nums[j] == nums[j - 1]) continue;
            if (nums[i] + nums[j] + nums[j + 1] + nums[j + 2] > target) break;
            if (nums[i] + nums[j] + nums[nums.size() - 2] + nums[nums.size() - 1] < target) break;
            int left = j + 1;
            int right = nums.size() - 1;
            while (left < right) {
                long sum = nums[i] + nums[j] + nums[left] + nums[right];
                if (sum > target) --right;
                else if (sum < target) ++left;
                else {
                    while (left < right && nums[left] == nums[left + 1]) ++left;
                    while (left < right && nums[right] == nums[right - 1]) --right;
                    ret.push_back({nums[i], nums[j], nums[left], nums[right]});
                    ++left;
                    --right;
                }
            }
        }
    }
    return ret;
}
