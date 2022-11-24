#include <iostream>

using std::cout;
using std::cin;
using std::ios_base;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

static const auto fast=[](){ios_base::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);return nullptr;}();

/*
 * 203. Remove Linked List Elements 1
 */
ListNode* removeElements(ListNode *head, int val) {
    ListNode *sentinel = new ListNode(0, head);
    head = sentinel;
    while (head->next) {
        if (head->next->val == val)
            head->next = head->next->next;
        else
            head = head->next;
    }
    head = sentinel->next;
    delete sentinel;
    return head;
}
ListNode* removeElements2(ListNode *head, int val) {
    if (!head) return nullptr;
    head->next = removeElements2(head->next, val);
    return head->val == val ? head->next : head;
}

/*
 * 707. Design Linked List 2
 */
class MyLinkedList {
public:
    struct LinkedNode {
        int val;
        LinkedNode* next;
        LinkedNode(int val) : val(val), next(nullptr) {}
        LinkedNode(int val, LinkedNode *next) : val(val), next(next) {}
    };

    MyLinkedList() {
        sentinel_ = new LinkedNode(0);
        size_ = 0;
    }
    
    int get(int index) {
        if (index < 0 || index >= size_)
            return -1;
        LinkedNode *p = sentinel_->next;
        while (index--)
            p = p->next;
        return p->val;
    }
    
    void addAtHead(int val) {
        LinkedNode *node = new LinkedNode(val, sentinel_->next);
        sentinel_->next = node;
        ++size_;
    }
    
    void addAtTail(int val) {
        LinkedNode *p = sentinel_;
        while (p->next)
            p = p->next;
        p->next = new LinkedNode(val);
        ++size_;
    }
    
    void addAtIndex(int index, int val) {
        if (index > size_ || index < 0)
            return;
        LinkedNode *p = sentinel_;
        while (index--)
            p = p->next;
        LinkedNode *node = new LinkedNode(val, p->next);
        p->next = node;
        ++size_;
    }
    
    void deleteAtIndex(int index) {
        if (index >= size_ || index < 0)
            return;
        LinkedNode *p = sentinel_;
        while (index--)
            p = p->next;
        LinkedNode *tmp = p->next;
        p->next = tmp->next;
        delete tmp;
        --size_;
    }

private:
    int size_;
    LinkedNode *sentinel_;
};

/*
 * 206. Reverse Linked List 3
 */
ListNode* reverseList(ListNode *head) {
    ListNode *prev = nullptr, *curr = head, *tmp = nullptr;
    while (curr) {
        tmp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = tmp;
    }
    return prev;
}
ListNode* reverse(ListNode *prev, ListNode *curr) {
    if (!curr) return prev;
    ListNode *tmp = curr->next;
    curr->next = prev;
    return reverse(curr, tmp); // 相当于做了如下两步: prev = curr; curr = tmp;
}
ListNode* reverseList2(ListNode *head) {
    return reverse(nullptr, head); // 等价于: prev = nullptr; curr = head;
}

/*
 * 24. Swap Nodes in Pairs 4
 */
/*
 * Pointer-pointer pp points to the pointer to the current node. So at first, pp points to head, and later it points to the next field of ListNodes. Additionally, for convenience and clarity, pointers a and b point to the current node and the next node.

We need to go from *pp == a -> b -> (b->next) to *pp == b -> a -> (b->next). The first three lines inside the loop do that, setting those three pointers (from right to left). The fourth line moves pp to the next pair.
 */
ListNode* swapPairs(ListNode *head) {
    ListNode **pp = &head, *a, *b;
    while ((a = *pp) && (b = a->next)) {
        a->next = b->next;
        b->next = a;
        *pp = b;
        pp = &(a->next);
    }
    return head;
}

ListNode* swapPairs2(ListNode *head) {
    if (!head || !head->next) return head;
    ListNode *node = head->next;
    head->next = swapPairs2(node->next);
    node->next = head;
    return node;
}

/*
 * 19. Remove Nth Node From End of List 5
 *
 * Constraints:
 *
 * The number of nodes in the list is sz.
 * 1 <= sz <= 30
 * 0 <= Node.val <= 100
 * 1 <= n <= sz
 */
ListNode* removeNthFromEnd(ListNode *head, int n) {
    ListNode *sentinel = new ListNode(0, head);
    ListNode *right = head;
    while (n--)
        right = right->next;
    ListNode *left = sentinel;
    while (right) {
        right = right->next;
        left = left->next;
    }
    ListNode *tmp = left->next;
    left->next = left->next->next;
    delete tmp;
    head = sentinel->next;
    delete sentinel;
    return head;
}

ListNode* removeNthFromEnd2(ListNode *head, int n) {
    ListNode **slow = &head, *fast = head;
    while (--n)
        fast = fast->next;
    while (fast->next) {
        slow = &((*slow)->next);
        fast = fast->next;
    }
    *slow = (*slow)->next;
    return head;
}

/*
 * 160. Intersection of Two Linked Lists 6
 *
 * Constraints:
 *
 * The number of nodes of listA is in the m.
 * The number of nodes of listB is in the n.
 * 1 <= m, n <= 3 * 104
 * 1 <= Node.val <= 105
 * 0 <= skipA < m
 * 0 <= skipB < n
 * intersectVal is 0 if listA and listB do not intersect.
 * intersectVal == listA[skipA] == listB[skipB] if listA and listB intersect.
 */
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    ListNode *currA = headA, *currB = headB;
    int lenA = 0, lenB = 0;
    while (currA) {
        ++lenA;
        currA = currA->next;
    }
    while (currB) {
        ++lenB;
        currB = currB->next;
    }
    if (lenB > lenA) {
        std::swap(lenA, lenB);
        currA = headB;
        currB = headA;
    } else {
        currA = headA;
        currB = headB;
    }
    int gap = lenA - lenB;
    while (gap--)
        currA = currA->next;
    while (currA) {
        if (currA == currB)
            return currA;
        currA = currA->next;
        currB = currB->next;
    }
    return nullptr;
}

ListNode* getIntersectionNode2(ListNode *headA, ListNode *headB) {
    ListNode *p1 = headA, *p2 = headB;
    while (p1 != p2) {
        p1 = p1 ? p1->next : headB;
        p2 = p2 ? p2->next : headA;
    }
    return p1;
}

/*
 * 142. Linked List Cycle II 7
 *
 * Constraints:
 *
 * The number of the nodes in the list is in the range [0, 104].
 * -105 <= Node.val <= 105
 * pos is -1 or a valid index in the linked-list.
 */
ListNode *detectCycle(ListNode *head) {
    ListNode *slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            slow = head;
            while (slow != fast) {
                slow = slow->next;
                fast = fast->next;
            }
            return slow;
        }
    }
    return nullptr;
}
