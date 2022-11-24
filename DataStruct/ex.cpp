#include <vector>
#include <string>
#include <climits>
#include <algorithm>
#include <unordered_map>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* reverse(ListNode *pre, ListNode *curr) {
    if (!curr) return pre;
    ListNode *temp = curr->next;
    curr->next = pre;
    return reverse(curr, temp);
}

ListNode* reverseList(ListNode* head) {
    return reverse(nullptr, head);
}
