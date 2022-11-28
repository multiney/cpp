#include <algorithm>
#include <string>
#include <vector>
#include <memory>
#include <cstring>
#include <climits>
#include <unordered_set>
#include <unordered_map>

using std::string;
using std::vector;

#include <iostream>
using std::cout;
using std::endl;

/*
 * 242============================================
 * -----------------------------------------------
 */
/*
 * 242. Valid Anagram 1
 *
 * Constraints:
 *
 * 1 <= s.length, t.length <= 5 * 104
 * s and t consist of lowercase English letters.
 */
bool isAnagram(string s, string t) {
    if (s.size() != t.size())
        return false;
    vector<int> count('z' + 1);
    for (int i = 0; i < s.size(); ++i) {
        ++count[s[i]];
        --count[t[i]];
    }
    for (auto i : count)
        if (i) return false;
    return true;
}
// TODO: 383 49 438
/*
 * -----------------------------------------------
 * 242============================================
 */

/*
 * 1002. Find Common Characters 2
 *
 * Constraints:
 *
 * 1 <= words.length <= 100
 * 1 <= words[i].length <= 100
 * words[i] consists of lowercase English letters.
 */
vector<string> commonChars(vector<string> &words) {
    int cnt[26];
    std::memset(cnt, words[0].size(), 26 * sizeof(int));
    vector<string> ret;
    for (auto &s : words) {
        int cnt1[26] = {0};
        for (auto c : s)
            ++cnt1[c - 'a'];
        for (int i = 0; i < 26; ++i)
            cnt[i] = std::min(cnt[i], cnt1[i]);
    }
    for (int i = 0; i < 26; ++i)
        while (cnt[i]--)
            ret.push_back(string(1, i + 'a'));
    return ret;
}

/*
 * 349. Intersection of Two Arrays 3
 * TODO: 350
 * Constraints:
 *
 * 1 <= nums1.length, nums2.length <= 1000
 * 0 <= nums1[i], nums2[i] <= 1000
 */
vector<int> intersection(vector<int> &nums1, vector<int> &nums2) {
    vector<int> ret;
    int hash[1001] = {0};
    for (int num : nums1)
        hash[num] = 1;
    for (int num : nums2)
        if (hash[num] == 1 && std::find(ret.cbegin(), ret.cend(), num) == ret.cend())
            ret.push_back(num);
    return ret;
}

vector<int> intersection2(vector<int> &nums1, vector<int> &nums2) {// __RECOMMENDED__
    std::unordered_set<int> nums_set(nums1.begin(), nums1.end());
    vector<int> ret;
    for (int num : nums2)
        if (nums_set.erase(num))
            ret.push_back(num);
    return ret;
}

/*
 * 202. Happy Number 4
 *
 * Constraints:
 * 1 <= n <= 231 - 1
 */
int getSum(int n) {
    int sum = 0;
    while (n) {
        sum += (n % 10) * (n % 10);
        n /= 10;
    }
    return sum;
}
bool isHappy(int n) {
    std::unordered_set<int> set;
    while (true) {
        int sum = getSum(n);
        if (sum == 1)
            return true;
        if (set.find(sum) != set.end())
            return false;
        set.insert(sum);
        n = sum;
    }
}

int digitSquareSum(int n) {
    int sum = 0, tmp;
    while (n) {
        tmp = n % 10;
        sum += tmp * tmp;
        n /= 10;
    }
    return sum;
}

bool isHappy2(int n) {// no need to grap
    int slow, fast;
    slow = fast = n;
    do {
        slow = digitSquareSum(slow);
        fast = digitSquareSum(fast);
        fast = digitSquareSum(fast);
    } while(slow != fast);
    if (slow == 1) return 1;
    else return 0;
}

/*
 * 1. Two Sum 5
 * Constraints:
 * 2 <= nums.length <= 104
 * -109 <= nums[i] <= 109
 * -109 <= target <= 109
 * Only one valid answer exists.
 */
vector<int> twoSum(vector<int> &nums, int target) {
    for (int i = 0; i < nums.size(); ++i) {
        auto it = std::find(nums.begin() + i + 1, nums.end(), target - nums[i]);
        if (it != nums.end())
            return std::initializer_list<int>{i, static_cast<int>(it - nums.begin())};
    }
    return {};
}

/*
 * 454. 4Sum II 6
 *
 * Constraints:
 * n == nums1.length
 * n == nums2.length
 * n == nums3.length
 * n == nums4.length
 * 1 <= n <= 200
 * -228 <= nums1[i], nums2[i], nums3[i], nums4[i] <= 228
 */
int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) { // __FIRST__
    std::unordered_map<int, int> sum_map;
    for (auto i : nums1)
        for (auto j : nums2)
            ++sum_map[i + j];
    int ret = 0;
    for (auto i : nums3)
        for (auto j : nums4) {
            auto iter = sum_map.find(-(i + j));
            if (iter != sum_map.end())
                ret += iter->second;
        }
    return ret;
}

/*
 * 383. Ransom Note 7
 *
 * Constraints:
 * 1 <= ransomNote.length, magazine.length <= 105
 * ransomNote and magazine consist of lowercase English letters.
 */
bool canConstruct(string ransomNote, string magazine) { // __FIRST__
    int hash[26] = {0};
    for (auto c : magazine)
        ++hash[c - 'a'];
    for (auto c : ransomNote) {
        if (hash[c - 'a'] > 0)
            --hash[c - 'a'];
        else
            return false;
    }
    return true;
}

/*
 * 15. 3Sum 8
 *
 * Constraints:
 * 3 <= nums.length <= 3000
 *-105 <= nums[i] <= 105
 */
vector<vector<int>> threeSum(vector<int>& nums) { // __FIRST__
    vector<vector<int>> ret;
    std::sort(nums.begin(), nums.end());
    for (int i = 0; i < nums.size(); ++i) {
        if (nums[i] > 0)
            break;
        if (i > 0 && nums[i] == nums[i - 1])
            continue;
        int left = i + 1;
        int right = nums.size() - 1;
        while (left < right) {
            if (nums[i] + nums[left] + nums[right] > 0) --right;
            else if (nums[i] + nums[left] + nums[right] < 0) ++left;
            else {
                ret.push_back({nums[i], nums[left], nums[right]});
                do { --right; } while (left < right && nums[right] == nums[right - 1]);
                do { ++left; } while (left < right && nums[left] == nums[left + 1]);
            }
        }
    }
    return ret;
}

/*
 * 18. 4Sum 9
 *
 * Constraints:
 * 1 <= nums.length <= 200
 * -109 <= nums[i] <= 109
 * -109 <= target <= 109
 */
vector<vector<int>> fourSum(vector<int>& nums, int target) { // __FIRST__
    vector<vector<int>> ret;
    if (nums.size() < 4) return ret;
    int n = nums.size();
    sort(nums.begin(), nums.end());
    for (int i = 0; i < n - 3; ++i) {
        if (i > 0 && nums[i] == nums[i - 1]) continue;
        if ((long)nums[i] + nums[i + 3] + nums[i + 2] + nums[i + 1] > target) break;
        if ((long)nums[i] + nums[n - 3] + nums[n - 2] + nums[n - 1] < target) continue;
        for (int j = i + 1; j < n - 2; ++j) {
            if (j > i + 1 && nums[j] == nums[j - 1]) continue;
            if ((long)nums[i] + nums[j] + nums[j + 2] + nums[j + 1] > target) break;
            if ((long)nums[i] + nums[j] + nums[n - 2] + nums[n - 1] < target) continue;
            int left = j + 1, right = n - 1;
            while (left < right) {
                long sum = nums[i] + nums[j] + nums[left] + nums[right];
                if (sum > target) --right;
                else if (sum < target) ++left;
                else {
                    ret.push_back({nums[i], nums[j], nums[left], nums[right]});
                    do {++left;} while (left < right && nums[left] == nums[left - 1]);
                    do {--right;} while (left < right && nums[right] == nums[right + 1]);
                }
            }
        }
    }
    return ret;
}








int main (int argc, char *argv[])
{
    vector<int> nums{1, -2, -5, -4, -3, 3, 3, 5};
    auto ret = fourSum(nums, -11);
    for (auto v : ret) {
        for (auto i : v)
            cout << i << " ";
        cout << endl;
    }
}
