#include <stack>
#include <queue>
#include <iostream>

using std::stack;
using std::queue;
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

