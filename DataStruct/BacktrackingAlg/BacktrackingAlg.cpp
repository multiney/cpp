#include "../include-file.h"

/**
 * 77. Combinations
 *
 * Constraints:
 * 1 <= n <= 20
 * 1 <= k <= n
 */
vector<vector<int>> retvvi;
vector<int> path;
void combineHelper(int n, int k, int startIndex) {
    if (path.size() == k) {
        retvvi.push_back(path);
        return;
    }
    for (int i = startIndex; i <= n - (k - path.size()) + 1; ++i) {
        path.push_back(i);
        combineHelper(n, k, i + 1);
        path.pop_back();
    }
}
vector<vector<int>> combine(int n, int k) {
    combineHelper(n, k, 1);
    return retvvi;
}

/**
 * 216. Combination Sum III
 *
 * Constraints:
 * 2 <= k <= 9
 * 1 <= n <= 60
 */
void combinationSum3Helper(int k, int n, int startIndex) {
    if (n < 0) return;
    if (path.size() == k) {
        if (n == 0) retvvi.push_back(path);
        return;
    }
    for (int i = startIndex; i <= 9 - (k - path.size()) + 1 && ((i + 9) * (9 - i + 1) >> 1) >= n ; ++i) {
        path.push_back(i);
        combinationSum3Helper(k, n - i, i + 1);
        path.pop_back();
    }
}
vector<vector<int>> combinationSum3(int k, int n) {
    combinationSum3Helper(k, n, 1);
    return retvvi;
}

/**
 * 17. Letter Combinations of a Phone Number
 *
 * Constraints:
 * 0 <= digits.length <= 4
 * digits[i] is a digit in the range ['2', '9'].
 */
vector<string> retvs;
const string dic[8]{"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
void letterCombinationsHelper(const string &digits, int index, const string &s) {
    if (index == digits.size()) {
        retvs.push_back(s);
        return;
    }
    for (int i = 0; i < dic[digits[index] - '2'].size(); ++i)
        letterCombinationsHelper(digits, index + 1, s + dic[digits[index] - '2'][i]);

}
vector<string> letterCombinations(string digits) {
    if (digits.size() == 0) return {};
    string s;
    letterCombinationsHelper(digits, 0, s);
    return retvs;
}

/**
 * 39. Combination Sum
 * 
 * Constraints:
 * 1 <= candidates.length <= 30
 * 2 <= candidates[i] <= 40
 * All elements of candidates are distinct.
 * 1 <= target <= 40
 */
void combinationSumHelper(vector<int> &candidates, int target, int startIndex) {
    if (target == 0) {
        retvvi.push_back(path);
        return;
    }
    for (int i = startIndex; i < candidates.size() && candidates[i] <= target; ++i) {
        path.push_back(candidates[i]);
        combinationSumHelper(candidates, target - candidates[i], i);
        path.pop_back();
    }
}
vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    std::sort(candidates.begin(), candidates.end());
    combinationSumHelper(candidates, target, 0);
    return retvvi;
}

/**
 * 40. Combination Sum II
 *
 * Constraints:
 * 1 <= candidates.length <= 100
 * 1 <= candidates[i] <= 50
 * 1 <= target <= 30
 */
void combinationSum2Helper(vector<int> &candidates, int target, int startIndex, vector<bool> &used) {
    if (target == 0) {
        retvvi.push_back(path);
        return;
    }
    for (int i = startIndex; i < candidates.size() && candidates[i] <= target; ++i) {
        if (i > 0 && candidates[i] == candidates[i - 1] && !used[i - 1]) continue;
        used[i] = true;
        path.push_back(candidates[i]);
        combinationSum2Helper(candidates, target - candidates[i], i + 1, used);
        path.pop_back();
        used[i] = false;
    }
}
vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
    vector<bool> used(candidates.size(), false);
    std::sort(candidates.begin(), candidates.end());
    combinationSum2Helper(candidates, target, 0, used);
    return retvvi;
}

/**
 * 131. Palindrome Partitioning
 *
 * Constraints:
 * 1 <= s.length <= 16
 * s contains only lowercase English letters.
 */
vector<vector<string>> retvvs;
vector<string> pathstr;
bool isPalindrome(const string &s, int i, int j) {
    for (; i < j; ++i, --j)
        if (s[i] != s[j])
            return false;
    return true;
}
void partitionHelper(const string &s, int startIndex) {
    if (startIndex >= s.size()) {
        retvvs.push_back(pathstr);
        return;
    }
    for (int i = startIndex; i < s.size(); ++i) {
        if (isPalindrome(s, startIndex, i))
            pathstr.push_back(s.substr(startIndex, i - startIndex + 1));
        else continue;
        partitionHelper(s, i + 1);
        pathstr.pop_back();
    }
}
vector<vector<string>> partition(string s) {
    partitionHelper(s, 0);
    return retvvs;
}

/**
 * 93. Restore IP Addresses
 *
 * Constraints:
 * 1 <= s.length <= 20
 * s consists of digits only.
 */
bool isValidIP(const string &s, int beg, int end) {
    if (end - beg < 0 || end - beg > 2) return false;
    if (s[beg] == '0' && beg != end) return false;
    int num = 0;
    while (beg <= end)
        num = num * 10 + (s[beg++] - '0');
    return num >= 0 && num <= 255;
}
void restoreIpAddressesHelper(string &s, int start, int pointNum) {
    if (pointNum == 3) {
        if (isValidIP(s, start, s.size() - 1))
            retvs.push_back(s);
        return;
    }
    for (int i = start; i < s.size(); ++i) {
        if (isValidIP(s, start, i)) {
            s.insert(s.begin() + i + 1, '.');
            restoreIpAddressesHelper(s, i + 2, pointNum + 1);
            s.erase(s.begin() + i + 1);
        } else break;
    }
}
vector<string> restoreIpAddresses(string s) {
    if (s.size() < 4 || s.size() > 12) return {};
    restoreIpAddressesHelper(s, 0, 0);
    return retvs;
}

/*
 * 78. Subsets
 *
 * Constraints:
 * 1 <= nums.length <= 10
 * -10 <= nums[i] <= 10
 * All the numbers of nums are unique.
 */
void subsetsHelper(vector<int> &nums, int start) {
    retvvi.push_back(path);
    for (int i = start; i < nums.size(); ++i) {
        path.push_back(nums[i]);
        subsetsHelper(nums, i + 1);
        path.pop_back();
    }
}
vector<vector<int>> subsets(vector<int>& nums) {
    subsetsHelper(nums, 0);
    return retvvi;
}
