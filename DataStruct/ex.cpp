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

ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    ListNode *pa = headA, *pb = headB;
    while (pa == pb) {
        pa = pa ? pa->next : headB;
        pb = pb ? pb->next : headA;
    }
    return pa;
}
