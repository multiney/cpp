#include <climits>
#include <malloc.h>

#include <unordered_map>
#include <vector>
#include <string>

using std::vector;
using std::string;

/*
 * 704==================================================================
 * ---------------------------------------------------------------------
 */
/*
 * 704. Binary Search 1
 */
int search(vector<int>& nums, int target) {
    int left = 0, right = nums.size(), mid;
    while (left < right) {
        mid = left + ((right - left) >> 1);
        if (nums[mid] < target)
            left = mid + 1;
        else
            right = mid;
    }
    return (left < nums.size() && nums[left] == target) ? left : -1;
}
// c Version
int search(int *nums, int numsSize, int target) {
    int left = 0, right = numsSize, mid;
    while (left < right) {
        mid = left + ((right - left) >> 1);
        if (nums[mid] < target)
            left = mid + 1;
        else
            right = mid;
    }
    return left < numsSize && nums[left] == target ? left : -1;
}

/*
 * 35. Search Insert Position 2
 *
 * Constraints: nums contains distinct values sorted in ascending order.
 */
int searchInsert(int *nums, int numsSize, int target) {
    int left = 0, right = numsSize, mid;
    while (left < right) {
        mid = left + ((right - left) >> 1);
        if (nums[mid] < target)
            left = mid + 1;
        else
            right = mid;
    }
    return left;
}

/*
 * 34. Find First and Last Position of Element in Sorted Array 3
 *
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* searchRange(int *nums, int numsSize, int target, int *returnSize) {
    int *ret = (int*)malloc(sizeof(int) * (*returnSize = 2));
    int left = 0, right = numsSize, mid;
    while (left < right) {
        mid = left + ((right - left) >> 1);
        if (nums[mid] < target)
            left = mid + 1;
        else
            right = mid;
    }
    if (left == numsSize || nums[left] != target) {
        ret[0] = ret[1] = -1;
        return ret;
    }
    ret[0] = left, right = numsSize - 1;
    while (left < right) {
        mid = left +((right - left) >> 1) + 1;
        if (nums[mid] > target)
            right = mid - 1;
        else
            left = mid;
    }
    ret[1] = right;
    return ret;
}

/*
 * 69. Sqrt(x) 4
 */
int mySqrt(int x) {
    int s = 1, l = x, mid;
    while (s <= l) {
        mid = s + ((l - s) >> 1);
        if (mid > x / mid)
            l = mid - 1;
        else
            s = mid + 1;
    }
    return s - 1;
}
int sqrtNewton(int x) { // TODO: how?
    long r = x;
    while (r * r > x)
        r = (r + x / r) / 2;
    return r;
}

/*
 * 367. Valid Perfect Square 5
 *
 * Constraints: 1 <= num <= 2^31 - 1
 */
bool isPerfectSquare(int num) {
    int s = 1, l = num, mid;
    while (s <= l) {
        mid = s + ((l - s) >> 1);
        if (mid > num / mid)
            l = mid - 1;
        else
            s = mid + 1;
    }
    return (s - 1) * (s - 1) == num;
}

bool isPerfectSquare2(int num) {
    int i = 1;
    while (num > 0) {
        num -= i;
        i += 2;
    }
    return num == 0;
}

/*
 * 704------------------------------------------------------------------------------
 * =================================================================================
 */

/*
 * 27=========================================
 * -------------------------------------------
 */
/*
 * 27. Remove Element 6
 */
int removeElement(vector<int> &nums, int val) {
    int slow = 0;
    for (int fast = 0; fast < nums.size(); ++fast)
        if (nums[fast] != val)
            nums[slow++] = nums[fast];
    return slow;
}
int removeElement2(vector<int> &nums, int val) {
    int left = 0, right = nums.size() - 1;
    while (left <= right) {
        while (left <= right && nums[left] != val)
            ++left;
        while (left <= right && nums[right] == val)
            --right;
        if (left < right)
            nums[left++] = nums[right--];
    }
    return left;
}

/*
 * 26. Remove Duplicates from Sorted array 7
 *
 * Constraints: 1 <= nums.length <= 3 * 10^4
 */
int removeDuplicates(vector<int> &nums) {
    int slow = 0;
    for (int fast = 1; fast < nums.size(); ++fast)
        if (nums[slow] != nums[fast])
            nums[++slow] = nums[fast];
    return slow + 1;
}
int removeDuplicates2(vector<int> &nums) {
    int slow = 1;
    for (int fast = slow; fast < nums.size(); ++fast)
        if (nums[fast] != nums[fast - 1])
            nums[slow++] = nums[fast];
    return slow;
}
int removeDuplicates3(vector<int> &nums) {
    int count = 0;
    for (int i = 1; i < nums.size(); ++i) {
        if (nums[i] == nums[i - 1])
            ++count;
        else
            nums[i - count] = nums[i];
    }
    return nums.size() - count;
}

/*
 * 283. Move Zeroes 8
 */
void moveZeroes(vector<int> &nums) {
    int slow = 0;
    for (int fast = 0; fast < nums.size(); ++fast)
        if (nums[fast] != 0)
            nums[slow++] = nums[fast];
    while (slow < nums.size())
        nums[slow++] = 0;
}
void moveZeroes2(vector<int> &nums) {
    int snowBallSize = 0;
    for (int i = 0; i < nums.size(); ++i) {
        if (nums[i] == 0)
            ++snowBallSize;
        else if (snowBallSize > 0) {
            nums[i - snowBallSize] = nums[i];
            nums[i] = 0;
        }
    }
}

/*
 * 844. Backspace String Compare 9 __FIRST__
 */
bool backspaceCompare(string s, string t) {
    int i = s.size() - 1, j = t.size() - 1;
    while (true) {
        int count = 0;
        while (i >= 0) {
            if (s[i] == '#')
                ++count;
            else if (count > 0)
                --count;
            else if (count == 0)
                break;
            --i;
        }
        count = 0;
        while (j >= 0) {
            if (t[j] == '#')
                ++count;
            else if (count > 0)
                --count;
            else if (count == 0)
                break;
            --j;
        }
        if (i >= 0 && j >= 0 && s[i] == t[j])   {
            --i;
            --j;
        } else {
            break;
        }
    }
    return i == -1 && j == -1;
}
bool backspaceCompare2(string s, string t) {
    int slowS = 0, slowT = 0;
    for (int fast = 0; fast < s.size(); ++fast) {
        if (s[fast] != '#')
            s[slowS++] = s[fast];
        else if (slowS > 0)
            --slowS;
    }
    for (int fast = 0; fast < t.size(); ++fast) {
        if (t[fast] != '#')
            t[slowT++] = t[fast];
        else if (slowT > 0)
            --slowT;
    }
    if (slowS != slowT) return false;
    for (int i = 0; i < slowS; ++i)
        if (s[i] != t[i]) return false;
    return true;
}

/*
 * 977. Squares of a Sorted Array 10
 *
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sortedSquares(int* nums, int numsSize, int* returnSize){
    int left = 0, right = numsSize - 1, pos = right;
    int *ret = (int*)malloc((*returnSize = numsSize) * sizeof(int));
    while (left < right) {
        nums[left] = nums[left] < 0 ? -nums[left] : nums[left];
        nums[right] = nums[right] < 0 ? -nums[right] : nums[right];
        if (nums[left] < nums[right]) {
            ret[pos--] = nums[right] * nums[right];
            --right;
        } else {
            ret[pos--] = nums[left] * nums[left];
            ++left;
        }
    }
    ret[pos] = nums[left] * nums[left];
    return ret;
}
/*
 * -------------------------------------------
 * 27=========================================
 */

/*
 * 209=========================================
 * -------------------------------------------
 */

/*
 * 209. Minimum Size Subarray Sum 11
 */
int minSubArrayLen(int target, vector<int> &nums) {
    int left = 0, sum = 0, minLen = INT_MAX;
    for (int right = 0; right < nums.size(); ++right) {
        sum += nums[right];
        while (sum >= target) {
            minLen = right - left + 1 < minLen ? right - left + 1 : minLen;
            sum -= nums[left++];
        }
    }
    return minLen == INT_MAX ? 0 : minLen;
}

int minSubArrayLen2(int target, vector<int> &nums) {
    int left = 0, minLen = INT_MAX;
    for (int right = 0; right < nums.size(); ++right) {
        target -= nums[right];
        while (target <= 0) {
            minLen = right - left + 1 < minLen ? right - left + 1 : minLen;
            target += nums[left++];
        }
    }
    return minLen = INT_MAX ? 0 : minLen;
}
int upperBound(int begin, int end, int target, const vector<int> &vec) {
    int mid;
    while (begin < end) {
        mid = begin + ((end - begin) >> 1);
        if (vec[mid] > target)
            end = mid;
        else
            begin = mid + 1;
    }
    return begin;
}
int minSubArrayLen3(int target, vector<int> &nums) { // __FIRST__
    int n = nums.size(), minLen = INT_MAX;
    vector<int> sums(n + 1);
    for (int i = 1; i <= n; ++i)
        sums[i] = nums[i - 1] + sums[i - 1];
    for (int i = n; i > 0 && sums[i] >= target; --i) {
        int j = upperBound(0, i, sums[i] - target, sums);
        minLen = std::min(minLen, i - j + 1);
    }
    return minLen == INT_MAX ? 0 : minLen;
}

/*
 * 904. Fruit Into Baskets 12
 */
int totalFruit(vector<int> &fruits) {
    std::unordered_map<int, int> count;
    int i, j;
    for (i = 0, j = 0; j < fruits.size(); ++j) {
        ++count[fruits[j]];
        if (count.size() > 2) {
            if (--count[fruits[i]] == 0)
                count.erase(fruits[i]);
        ++i;
        }
    }
    return j - i;
}
int totalFruit2(vector<int> &fruits) {
    int left = 0, right = 0, ret = 0;
    int ln = fruits[left], rn = fruits[right];
    while (right < fruits.size()) {
        if (fruits[right] == ln || fruits[right] == rn) {
            ret = std::max(ret, right - left + 1);
            ++right;
        } else {
            left = right - 1;
            ln = fruits[left];
            while (left > 0 && fruits[left - 1] == ln) --left;
            rn = fruits[right];
        }
    }
    return ret;
}

int lengthOfLongestSubstringTwoDistinct(string s) {
    vector<int> map(128, 0);
    int counter = 0, begin = 0, end = 0, ret = 0;
    while (end < s.size()) {
        if (map[s[end++]]++ == 0) ++counter;
        while (counter > 2) if (map[s[begin++]]-- == 1) --counter;
        ret = std::max(ret, end - begin);
    }
    return ret;
}

/*
 * 3. Longest Substring Without Repeating Characters 13
 */
int lenthOfLongestSubstring(string s) {
    vector<int> map(128, 0);
    int counter = 0, begin = 0, end = 0, ret = 0;
    while (end < s.size()) {
        if (map[s[end++]]++ > 0) ++counter;
        while (counter > 0) if (map[s[begin++]]-- > 1) --counter;
        ret = std::max(ret, end - begin);
    }
    return ret;
}

int lengthOfLongestSubstring2(string s) {
    vector<int> map(128, 0);
    int ret = 0;
    for (int i = 0, j = 0; j < s.size(); ++j) {
        if (map[s[j]] > 0)
            i = std::max(i, map[s[j]]);
        ret = std::max(ret, j - i + 1);
        map[s[j]] = j + 1;
    }
    return ret;
}

/*
 * 76. Minimum Window Substring 14
 */
string minWindow(string s, string t) {
    vector<int> map('z' + 1);
    for (auto &c : t) ++map[c];
    int beg = 0, end = 0, head = 0, counter = t.size(), minLen = INT_MAX;
    while (end < s.size()) {
        if (--map[s[end++]] >= 0) --counter;
        if (counter == 0) {
            while (map[s[beg]] < 0) ++map[s[beg++]];
            if (minLen > end - beg) minLen = end - (head = beg);
        }
    }
    return minLen == INT_MAX ? "" : s.substr(head, minLen);
}

char* minWindow(char *s, char *t) {
    int map['z' + 1] = {0}, counter = 0, minLen = INT_MAX;
    while (t[counter]) ++map[t[counter++]];
    char *p = s, *q = s;
    while (*q) {
        if (--map[*q++] >= 0) --counter;
        if (!counter) {
            while (map[*p] < 0) ++map[*p++];
            if (minLen > q - p) minLen = q - (s = p);
        }
    }
    return (*(s + (minLen == INT_MAX ? 0 : minLen)) = 0) ? s : s;
}

/*
 * -------------------------------------------
 * 209=========================================
 */

/**
 * 59. Spiral Matrix II 15
 *
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** generateMatrix(int n, int* returnSize, int** returnColumnSizes){
    int **ret = (int**)malloc((*returnSize = n) * sizeof(int*));
    *returnColumnSizes = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i)
        ret[i] = (int*)malloc(((*returnColumnSizes)[i] = n) * sizeof(int));
    int k = 1, i = 0;
    while (k <= n * n) {
        int j = i;
        while (j < n - i)
            ret[i][j++] = k++;
        j = i + 1;
        while (j < n - i)
            ret[j++][n - i - 1] = k++;
        j = n - i - 2;
        while (j > i)
            ret[n - i - 1][j--] = k++;
        j = n - i - 1;
        while (j > i)
            ret[j--][i] = k++;
        ++i;
    }
    return ret;
}

/**
 * 54. Spiral Matrix 16
 *
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize){
    int *ret = (int*)malloc((*returnSize = *matrixColSize * matrixSize) * sizeof(int));
    int k = 0, i = 0;
    while (k < *returnSize) {
        int j = i;
        while (j < *matrixColSize - i)
            ret[k++] = matrix[i][j++];
        j = i + 1;
        while (j < matrixSize - i)
            ret[k++] = matrix[j++][*matrixColSize - i - 1];
        j = *matrixColSize - i - 2;
        while (j > i && k < *returnSize)
            ret[k++] = matrix[matrixSize - i - 1][j--];
        j = matrixSize - i - 1;
        while (j > i && k < *returnSize)
            ret[k++] = matrix[j--][i];
        ++i;
    }
    return ret;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 *
 * no need to understand
 */
int* spiralOrder2(int** matrix, int matrixsize, int* matrixcolsize, int* returnsize){
    int* ret = (int*)malloc((*returnsize = matrixsize * *matrixcolsize) * sizeof(int));
    int dirs[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int nr = matrixsize;      if (nr == 0) return ret;
    int nc = *matrixcolsize;  if (nc == 0) return ret;
    int nsteps[] = {nc, nr - 1};
    int idir = 0;
    int ir = 0, ic = -1, k = 0;
    while (nsteps[idir & 0x01]) {
        for (int i = 0; i < nsteps[idir & 0x01]; ++i) {
            ir += dirs[idir][0]; ic += dirs[idir][1];
            ret[k++] = matrix[ir][ic];
        }
        --nsteps[idir & 0x01];
        idir = (idir + 1) % 4;
    }
    return ret;
}
