#include <vector>
#include <string>
using namespace std;

vector<int> sortedSquares(vector<int>& nums) {
    int left = 0, right = nums.size() - 1, index = nums.size();
    vector<int> ret(index);
    while (left <= right) {
        nums[left] = nums[left] < 0 ? -nums[left] : nums[left];
        nums[right] = nums[right] < 0 ? -nums[right] : nums[right];
        if (nums[left] > nums[right]) {
            ret[--index] = nums[left] * nums[left];
            ++left;
        } else {
            ret[--index] = nums[right] * nums[right];
            --right;
        }
    }
    return ret;
}
