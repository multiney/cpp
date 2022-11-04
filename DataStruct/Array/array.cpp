#include <malloc.h>

#include <vector>
#include <string>

using std::vector;
using std::string;

/*
 * 704==================================================================
 * ---------------------------------------------------------------------
 */
/*
 * 704. Binary Search
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
 * 35. Search Insert Position
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
 * 34. Find First and Last Position of Element in Sorted Array
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
 * 69. Sqrt(x)
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
 * 367. Valid Perfect Square
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
 * 27. Remove Element
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
 * 26. Remove Duplicates from Sorted array
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
 * 283. Move Zeroes
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
 * 844. Backspace String Compare
 */
bool BackspaceCompare(string s, string t) {
    int i = s.size() - 1, j = t.size() - 1;
    while (i >= 0 && j >= 0) {
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
        if (i == 0)
    }
}
