#include <climits>
#include <malloc.h>
#include <stdbool.h>
#include <memory.h>
#include <stdlib.h>
#include <algorithm>

#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <bits/stdc++.h>

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::unordered_map;

/* 704 */
int search(int* nums, int numsSize, int target){
    int left = 0, right = numsSize, mid;
    while (left < right) {
        mid = left + ((right - left) >> 1);
        if (nums[mid] >= target)
            right = mid;
        else
            left = mid + 1;
    }
    return left < numsSize && nums[left] == target ? left : -1;
}

/* 35 */
int searchInsert(int* nums, int numsSize, int target){
    int left = 0, right = numsSize, mid;
    while (left < right) {
        mid = left + ((right - left) >> 1);
        if (nums[mid] >= target)
            right = mid;
        else
            left = mid + 1;
    }
    return left;
}

/* 34 */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* searchRange(int* nums, int numsSize, int target, int* returnSize){
    int *ret = (int*)malloc((*returnSize = 2) * sizeof(int));
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
    ret[0] = left;
    right = numsSize - 1;
    while (left < right) {
        mid = left + ((right - left) >> 1) + 1;
        if (nums[mid] > target)
            right = mid - 1;
        else
            left = mid;
    }
    ret[1] = right;
    return ret;
}


int** generateMatrix(int n, int* returnSize, int** returnColumnSizes){
    int** ret = (int**)malloc((*returnSize = n) * sizeof(int*));
    *returnColumnSizes = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i)
        *ret = (int*)malloc(n * sizeof(int));
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
            ret[n - i][j--] = k++;
        j = n - i - 1;
        while (j > i)
            ret[j--][i] = k++;
        ++i;
    }
    return ret;
}



int mySqrt(int x){
    if (x == 0) return 0;
    int small = 1, large = x, mid;
    while (small <= large) {
        mid = small + ((large - small) >> 1);
        if (mid <= x / mid)
            small = mid + 1;
        else
            large = mid - 1;
    }
    return small - 1;
}

int mySqrtNewton(int x) {
    long r = x;
    while (r * r > x)
        r = (r + x / r) / 2;
    return r;
}

bool isPerfectSquare(int num){
    if (num == 0 || num == 1 || num == 4) return true;
    long long left = 3, right = num, mid, multiplition;
    while (left < right) {
        mid = left + ((right - left) >> 1);
        multiplition = mid * mid;
        if (multiplition < num)
            left = mid + 1;
        else if (multiplition > num)
            right = mid;
        else
            return true;
    }
    return false;
}

bool isPerfectSquareMath(int num) {
    int i = 1;
    while (num > 0) {
        num -= i;
        i += 2;
    }
    return num == 0;
}

int removeDuplicates(int* nums, int numsSize){
    int slow = 1;
    for (int fast = slow; fast < numsSize; ++fast)
        if (nums[fast] != nums[fast - 1])
            nums[slow++] = nums[fast];
    return slow;
}

int removeDuplicatesAlt(int* nums, int numsSize) {
    int count = 0;
    for (int i = 1; i < numsSize; ++i) {
        if (nums[i] == nums[i - 1])
            ++count;
        else
            nums[i - count] = nums[i];
    }
    return numsSize - count;
}

void moveZeroes(int* nums, int numsSize){
    int slow = 0;
    // move all the nonzero elements advance
    for (int fast = slow; fast < numsSize; ++fast)
        if (nums[fast] != 0)
            nums[slow++] = nums[fast];
    for (; slow < numsSize; ++slow)
        nums[slow] = 0;
}

void moveZeroesSnow(int* nums, int numsSize) {
    int snowBallSize = 0;
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] == 0)
            ++snowBallSize;
        else if (snowBallSize > 0) {
            nums[i - snowBallSize] = nums[i];
            nums[i] = 0;
        }
    }
}

bool backspaceCompare(char * s, char * t){
    int slowS = 0, slowT = 0;
    for (int fast = slowS; s[fast] != '\0'; ++fast) {
        if (s[fast] != '#')
            s[slowS++] = s[fast];
        else if (slowS > 0)
            --slowS;
    }
    for (int fast = slowT; t[fast] != '\0'; ++fast) {
        if (t[fast] != '#')
            t[slowT++] = t[fast];
        else if (slowT > 0)
            --slowT;
    }
    if (slowS != slowT)
        return false;
    for (int i = 0; i < slowS; ++i)
        if (s[i] != t[i])
            return false;
    return true;
}

bool backspaceCompare(string s, string t) {
    int slowS = 0, slowT = 0;
    for (int fast = 0; fast < s.length(); ++fast) {
        if (s[fast] != '#')
            s[slowS++] = s[fast];
        else if (slowS > 0)
            --slowS;
    }
    for (int fast = 0; fast < t.length(); ++fast) {
        if (t[fast] != '#')
            t[slowT++] = t[fast];
        else if (slowT > 0)
            --slowT;
    }
    if (slowS != slowT)
        return false;
    for (int i = 0; i < slowS; ++i)
        if (s[i] != t[i])
            return false;
    return true;
}

bool backspaceCompareBack(string s, string t) {
    int i = s.length() - 1, j = t.length() - 1;
    while (true) {
        int back = 0;
        while (i >= 0 && (back > 0 || s[i] == '#')) {
            back += s[i] == '#' ? 1 : -1;
            --i;
        }
        back = 0;
        while (j >= 0 && (back > 0 || t[j] == '#')) {
            back += t[j] == '#' ? 1 : -1;
            --j;
        }
        if (i >= 0 && j >= 0 && s[i] == t[j]) {
            --i;
            --j;
        } else {
            break;
        }
    }
    return i == -1 && j == -1;
}

/**
 * 977. Squares of a Sorted Array
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sortedSquares(int* nums, int numsSize, int* returnSize){
    int left = 0, right = numsSize - 1;    
    int* ret = (int*)malloc((*returnSize = numsSize--) * sizeof(int));
    while (left <= right) {
        nums[left] = nums[left] >= 0 ? nums[left] : -nums[left];
        nums[right] = nums[right] >= 0 ? nums[right] : -nums[right];
        if (nums[left] > nums[right]) {
            ret[numsSize--] = nums[left] * nums[left];
            ++left;
        }
        else {
            ret[numsSize--] = nums[right] * nums[right];
            --right;
        }
    }
    return ret;
}

/**
 * 209
 */
int minSubArrayLen(int target, int* nums, int numsSize){
    int left = 0, sum = 0, ret = numsSize + 1;
    for (int right = 0; right < numsSize; ++right) {
        sum += nums[right];
        while (sum >= target) {
            ret = ret > right - left + 1 ? right - left + 1 : right;
            sum -= nums[left++];
        }
    }
    return ret;
}

/**
 * 904
 */
void printRet(int** con, int size) {
    for (int i = 0; i < size; ++i)
        cout << con[i][0] << " ";
    cout << endl;
}

struct MyMap {
    int** container;
    int size;
    int capacity;
};

void insert(struct MyMap* myMap, int x) {
    if (myMap->size == myMap->capacity)
        myMap->container = (int**)realloc(myMap->container, (myMap->capacity = myMap->capacity == 0 ? 1 : (myMap->capacity << 1)) * sizeof(int*));
    myMap->container[myMap->size] = (int*)malloc(2 * sizeof(int));
    myMap->container[myMap->size][0] = x;
    myMap->container[myMap->size][1] = 1;
    //cout << x << '-' << endl;
    ++myMap->size;
}

void incr(struct MyMap* myMap, int x) {
    for (int i = 0; i < myMap->size; ++i)
        if (myMap->container[i][0] == x) {
            ++myMap->container[i][1];
            return;
        }
    insert(myMap, x);
}

void decr(struct MyMap* myMap, int x) {
    for (int i = 0; i < myMap->size; ++i) {
        if (myMap->container[i][0] == x) {
            if (myMap->container[i][1] == 1) {
                free(myMap->container[i]);
                char *pCon = (char*) (myMap->container + i);
                int times = sizeof(int*) / sizeof(char);
                for (++i; i < myMap->size; ++i)
                    for (int time = 0; time < times; ++time) {
                        *pCon = *(pCon + times);
                        ++pCon;
                    }
                --myMap->size;
            }
            else --myMap->container[i][1];
            break;
        }
    }
}

void freeMap(struct MyMap* myMap) {
    for (int i = 0; i < myMap->size; ++i)
        free(myMap->container[i]);
    free(myMap->container);
}

int totalFruit(int* fruits, int fruitsSize){
    struct MyMap myMap = {NULL, 0, 0};
    int i, j;
    for (i = 0, j = 0; j < fruitsSize; ++j) {
        incr(&myMap, fruits[j]);
        if (myMap.size > 2)
            decr(&myMap, fruits[i++]);
    }
    return j - i;
}

int totalFruitLR(int* fruits, int fruitsSize) {
    int left = 0, right = 0, ret = 0;
    int ln = fruits[left], rn = fruits[right];
    while (right < fruitsSize) {
        if (fruits[right] == ln || fruits[right] == rn) {
            ret = ret < right - left + 1 ? right - left + 1 : ret;
            ++right;
        }
        else {
            left = right - 1;
            ln = fruits[left];
            while (left >= 1 && fruits[left - 1] == ln) --left;
            rn = fruits[right];
            ret = ret < right - left + 1 ? right - left + 1 : ret;
        }
    }
    return ret;
}

int totalFruit(vector<int>& fruits) {
    unordered_map<int, int> count;
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

int totalFruitLR(vector<int>& fruits) {
    int left = 0, right = 0, ret = 0;
    int ln = fruits[left], rn = fruits[right];
    while (right < fruits.size()) {
        if (fruits[right] == ln || fruits[right] == rn) {
            ret = std::max(ret, right - left + 1);
            ++right;
        }
        else {
            left = right - 1;
            ln = fruits[left];
            while (left >= 1 && fruits[left - 1] == ln) --left;
            rn = fruits[right];
            ret = std::max(ret, right - left + 1);
        }
    }
    return ret;
}

/**
 * 76
 */
bool isEnough(unordered_map<char, int>& count) {
    for (auto p : count)
        if (p.second > 0)
            return false;
    return true;
}
string minWindow(string s, string t) {
    int ret = s.length() + 1, pos = 0;
    unordered_map<char, int> count;        
    for (auto c : t)
        count[c]++;
    int left = 0;
    while (left < s.length() && count.find(s[left]) == count.cend()) ++left;
    int right = left;
    while (right < s.length()) {
        if (count.find(s[right]) != count.cend()) {
            --count[s[right]];
            while (isEnough(count)) {
                if (ret > right - left + 1) {
                    ret = right - left + 1;
                    pos = left;
                }
                ++count[s[left++]];
                while (left < s.length() && count.find(s[left]) == count.cend()) ++left;
            }
        }
        ++right;
    }
    return ret == s.length() + 1 ? "" : s.substr(pos, ret);
}

string minWindowVec(string s, string t) {
    vector<int> map(128, 0);
    for (auto c : t) ++map[c];
    int beg = 0, end = 0, counter = t.size(), head = 0, minLen = INT_MAX;
    while (end < s.size()) {
        if (map[s[end++]]-- > 0) --counter;
        while (counter == 0) {
            if (end - beg < minLen) minLen = end - (head = beg);
            if (map[s[beg++]]++ == 0) ++counter;
        }
    }
    return minLen == INT_MAX ? "" : s.substr(head, minLen);
}

string minWindowClear(string s, string t) {
    vector<int> map('z' + 1, 0);
    for (auto c : t) ++map[c];
    int beg = 0, end = 0, counter = t.length(), head = 0, minLen = INT_MAX;
    while (end < s.size()) {
        if (map[s[end++]]-- > 0) --counter;
        if (counter == 0) {
            while (map[s[beg]]++ < 0) ++beg;
            if (minLen > end - beg) minLen = end - (head = beg);
            ++beg;
            ++counter;
        }
    }
    return minLen == INT_MAX ? "" : s.substr(head, minLen);
}

char * minWindow(char * s, char * t){
    int map['z' + 1] = {0}, counter = 0, minLen = INT_MAX;
    while (t[counter]) ++map[t[counter++]];
    char *p = s, *q = s;
    while (*q) {
        if (--map[*q++] >= 0) --counter;
        while (map[*p] < 0) ++map[*p++];
        if (!counter && minLen > q - p) minLen = q - (s = p);
    }
    return (*(s + (minLen == INT_MAX ? 0 : minLen)) = 0) ? s : s;
}

/**
 * 1365
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* smallerNumbersThanCurrent(int* nums, int numsSize, int* returnSize){
    int* ret = (int*)malloc((*returnSize = numsSize) * sizeof(int));
    int hash[101] = {0};
    for (int i = 0; i < numsSize; ++i)
        ++hash[nums[i]];
    for (int i = 1; i < 101; ++i)
        hash[i] += hash[i - 1];
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] == 0)
            ret[i] = 0;
        else
            ret[i] = hash[nums[i] - 1];
    }
    return ret;
}

vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
    vector<int> vec = nums;
    int hash[101];
    std::sort(vec.begin(), vec.end());
    for (int i = vec.size() - 1; i >= 0; --i)
        hash[vec[i]] = i;
    for (int i = 0; i < nums.size(); ++i)
        vec[i] = hash[nums[i]];
    return vec;
}

/**
 * 941
 */
bool validMountainArray(int* arr, int arrSize){
    if (arrSize < 3) return false;
    int left = 0, right = arrSize - 1;
    while (left < right && arr[left] < arr[left + 1]) {
        ++left;
        if (arr[right] < arr[right - 1]) --right;
    }
    while (right > left && arr[right] < arr[right - 1]) --right;
    return left != 0 && right != arrSize - 1 && left == right;
}

bool validMountainArray(vector<int>& arr) {
    if (arr.size() < 3) return false;
    int left = 0, right = arr.size() - 1;
    while (left < right && arr[left] < arr[left + 1]) {
        ++left;
        if (arr[right] < arr[right - 1]) --right;
        else {
            if (right == arr.size() - 1) return false;
            while (left < right && arr[left] < arr[left + 1]) ++left;
            return left == right;
        }
    }
    if (left == 0) return false;
    while (right > left && arr[right] < arr[right - 1]) --right;
    return left == right;
}

/**
 * 1207
 */
bool uniqueOccurrences(int* arr, int arrSize){
    int count[2001] = {0};
    for (int i = 0; i < arrSize; ++i)
        count[arr[i] + 1000]++;
    bool fre[1001] = {false};
    for (int i = 0; i < 2001; ++i) {
        if (count[i]) {
            if (fre[count[i]] == false) fre[count[i]] = true;
            else return false;
        }
    }
    return true;
}

/**
 * 189
 */
void rotate(int* nums, int numsSize, int k){
    int* p = nums, temp;
    for (; k %= numsSize; numsSize -= k, p += k)
        for (int i = 0; i < k; ++i) {
            temp = p[i];
            p[i] = p[i + numsSize - k];
            p[i + numsSize - k] = temp;
        }
}

void myReverse(int * nums, int beg, int end) {
    int temp;
    while (beg < end) {
        temp = nums[beg];
        nums[beg] = nums[end];
        nums[end] = temp;
        ++beg;
        --end;
    }
}

void rotateRev(int * nums, int numsSize, int k) {
    k %= numsSize;
    myReverse(nums, 0, numsSize - 1);
    myReverse(nums, 0, k - 1);
    myReverse(nums, k, numsSize - 1);
}

/**
 * 724
 */
int pivotIndex(int* nums, int numsSize){
    int countL[numsSize], countR[numsSize];
    countL[0] = nums[0];
    for (int i = 1; i < numsSize; ++i)
        countL[i] = nums[i] + countL[i - 1];
    countR[numsSize - 1] = nums[numsSize - 1];
    for (int i = numsSize - 1; i > 0; --i)
        countR[i - 1] = countR[i] + nums[i - 1];
    for (int i = 0; i < numsSize; ++i)
        if (countL[i] == countR[i])
            return i;
    return -1;
}

/**
 * 28
 */
void getNext(int *next, const string& s) {
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

int main (int argc, char *argv[])
{

    size_t size = 2;
    int** ppi = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; ++i)
        ppi[i] = (int*)malloc(8 * sizeof(int));
    ppi[0][0] = 1;
    ppi[0][1] = 2;
    cout << &ppi << endl;
    cout << ppi << endl;
    cout << ppi + 1 << endl;
    cout << *ppi << endl;
    cout << *ppi + 1 << endl;
    cout << **ppi << endl;
    cout << *(*ppi + 1) << endl;
    ppi[1][0] = 3;
    ppi[1][1] = 4;
    ++ppi;
    cout << ppi << endl;
    cout << *ppi << endl;
    cout << *ppi + 1 << endl;
    cout << **ppi << endl;
    char* pc = (char*) (ppi - 1);
    cout << **ppi << endl;
    cout << (void*) pc << endl;
    free(ppi[-1]);
    cout << ppi[0] << endl;
    for (int i = 0; i < 8; ++i) {
        *pc = *(pc + 8);
        ++pc;
    }
    cout << (void*) (pc - 8) << "?" << (void*) pc << endl;
    cout << **(ppi - 1) << endl;

    char str[2] = {"a"};
    cout << strlen(str) << endl;
    return 0;
}
