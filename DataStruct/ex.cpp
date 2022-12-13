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
#include <string>
#include "./include-file.h"
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

int evalRPN(vector<string>& tokens) {
    stack<int> stk;
    int left, right;
    for (string &token : tokens) {
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            right = stk.top(); stk.pop();
            left = stk.top(); stk.pop();
            if (token == "+")
                stk.push(left + right);
            else if (token == "-")
                stk.push(left - right);
            else if (token == "*")
                stk.push(left * right);
            else stk.push(left / right);
        } else stk.push(std::stoi(token));
    }
    return stk.top();
}
