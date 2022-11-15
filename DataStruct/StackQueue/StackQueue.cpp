#include <stack>
#include <queue>
#include <string>
#include <vector>
#include <deque>
#include <iostream>

using std::stack;
using std::queue;
using std::string;
using std::vector;
using std::deque;
using std::cout;
using std::endl;
/*
 * 232. Implement Queue using Stacks
 *
 * Constraints:
 * 1 <= x <= 9
 * At most 100 calls will be made to push, pop, peek, and empty.
 * All the calls to pop and peek are valid.
 */
class MyQueue {
private:
    stack<int> in_stack_;
    stack<int> out_stack_;
public:
    MyQueue() {
        
    }
    
    void push(int x) {
        in_stack_.push(x);
    }
    
    int pop() {
        int ret = peek();
        out_stack_.pop();
        return ret;
    }
    
    int peek() {
        if (out_stack_.empty())
            while (!in_stack_.empty()) {
                out_stack_.push(in_stack_.top());
                in_stack_.pop();
            }
        return out_stack_.top();
    }
    
    bool empty() {
        return in_stack_.empty() && out_stack_.empty();
    }
};

/*
 * 225. Implement Stack using Queues
 *
 * Constraints:
 * 1 <= x <= 9
 * At most 100 calls will be made to push, pop, top, and empty.
 * All the calls to pop and top are valid.
 */
class MyStack {
private:
    queue<int> queue1_;
    queue<int> queue2_;

    int pop_back(queue<int> &queue1, queue<int> &queue2) {
        while (queue1.size() != 1) {
            queue2.push(queue1.front());
            queue1.pop();
        }
        int ret = queue1.front();
        queue1.pop();
        return ret;
    }
public:
    MyStack() {
        
    }
    
    void push(int x) {
        if (queue1_.empty())
            queue2_.push(x);
        else
            queue1_.push(x);
    }
    
    int pop() {
        if (queue1_.empty())
            return pop_back(queue2_, queue1_);
        return pop_back(queue1_, queue2_);
    }
    
    int top() {
        if (queue1_.empty())
            return queue2_.back();
        return queue1_.back();
    }
    
    bool empty() {
        return queue1_.empty() && queue2_.empty();
    }
};

/*
 * 20. Valid Parentheses
 *
 * Constraints:
 * 1 <= s.length <= 104
 * s consists of parentheses only '()[]{}'.
 */
bool isValid(string s) {
    stack<char> stk;
    for (char c : s) {
        if (c == '(') stk.push(')');
        else if (c == '[') stk.push(']');
        else if (c == '{') stk.push('}');
        else if (stk.empty() || stk.top() != c) return false;
        else stk.pop();
    }
    return stk.empty();
}

/*
 * 1047. Remove All Adjacent Duplicates In String
 *
 * Constraints:
 * 1 <= s.length <= 105
 * s consists of lowercase English letters.
 */
string removeDuplicates(string s) {
    string ret;
    for (char c : s) {
        if (ret.empty() || ret.back() != c)
            ret.push_back(c);
        else
            ret.pop_back();
    }
    return ret;
}

/*
 * 150. Evaluate Reverse Polish Notation
 *
 * Constraints:
 * 1 <= tokens.length <= 104
 * tokens[i] is either an operator: "+", "-", "*", or "/", or an integer in the range [-200, 200].
 */
int evalRPN(vector<string>& tokens) {
    stack<long long> stk;
    for (const string &s : tokens) {
        if (s == "+" || s == "-" || s == "*" || s == "/") {
            long long num1 = stk.top(); stk.pop();
            long long num2 = stk.top(); stk.pop();
            if (s == "+") stk.push(num2 + num1);
            else if (s == "-") stk.push(num2 - num1);
            else if (s == "*") stk.push(num2 * num1);
            else stk.push(num2 / num1);
        }
        else
            stk.push(stoll(s));
    }
    return stk.top();
}

/*
 * 239. Sliding Window Maximum
 *
 * Constraints:
 * 1 <= nums.length <= 105
 * -104 <= nums[i] <= 104
 * 1 <= k <= nums.length
 */
class OrderedQueue {
private:
    deque<int> deque_;
public:
    OrderedQueue() {

    }

    void pop(int val) {
        if (!deque_.empty() && deque_.front() == val)
            deque_.pop_front();
    }

    void push(int val) {
        while (!deque_.empty() && deque_.back() < val)
            deque_.pop_back();
        deque_.push_back(val);
    }

    int front() {
        return deque_.front();
    }
};

vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    OrderedQueue que;
    vector<int> ret;
    for (int i = 0; i < k; ++i)
        que.push(nums[i]);
    ret.push_back(que.front());
    for (int i = k; i < nums.size(); ++i) {
        que.pop(nums[i - k]);
        que.push(nums[i]);
        ret.push_back(que.front());
    }
    return ret;
}

vector<int> maxSlidingWindow2(vector<int> &nums, int k ) {
    deque<int> dq;
    vector<int> ret;
    for (int i = 0; i < nums.size(); ++i) {
        if (!dq.empty() && dq.front() == i - k) dq.pop_front();
        while (!dq.empty() && nums[dq.back()] < nums[i]) dq.pop_back();
        dq.push_back(i);
        if (i >= k - 1) ret.push_back(nums[dq.front()]);
    }
    return ret;
}
