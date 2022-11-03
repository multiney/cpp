#ifndef CALCULATOR_H_
#define CALCULATOR_H_

#include <cstddef>
#include <string>
#include <iostream>
#include <cstring>

using std::string;
using std::cout;
using std::endl;
using std::ostream;

class Node {
public:
    Node() = default;
    Node(const string &val) : _val(val) {}
    Node(const char &val) {
        _val += val; // equal to 'string _val(val);'? NO!
    }
    Node(const char *val, size_t left, size_t right) {
        while (left != right)
            _val += val[left++];
    }

public:
// function
    const string& val() {
        return _val;
    }

    // calculate
    virtual int calc(int x, int y) {
        return 0;
    }

public:
// overloading operator function
    friend ostream& operator<<(ostream &os, const Node &node) {
        os << node._val;
        return os;
    }

private:
    string _val;
};

class NumberNode : public Node {
    using Node::Node;
};

class BinaryNode : public Node {
    using Node::Node;

public:
    virtual int calc(int x, int y) {
        return 0;
    }
};

class AddNode : public BinaryNode {
    using BinaryNode::BinaryNode;

public:
    virtual int calc(int x, int y) {
        return x + y;
    }
};

class MinusNode : public BinaryNode {
    using BinaryNode::BinaryNode;

public:
    virtual int calc(int x, int y) {
        return x - y;
    }
};

class MultiplyNode : public BinaryNode {
    using BinaryNode::BinaryNode;

public:
    virtual int calc(int x, int y) {
        return x * y;
    }
};

class DivideNode : public BinaryNode {
    using BinaryNode::BinaryNode;

public:
    virtual int calc(int x, int y) {
        return x / y;
    }
};

class CalTree;

bool isDigit(const char &ch);
CalTree* parseExpr(const char *expr, size_t left, size_t right);
CalTree* parseExpr(const char *expr);
void inorder(CalTree *root);

class CalTree {
public:
    // TODO: _node(new Node()) 是构造还是赋值
    CalTree() : _node(new Node()), _left(nullptr), _right(nullptr) {}
    CalTree(Node *node) : _node(node), _left(nullptr), _right(nullptr) {}
    CalTree(Node *node, CalTree *left, CalTree *right) : _node(node), _left(left), _right(right) {}
    ~CalTree() {
    }

public:
    // calculate the expression result
    int calculate() {
        if (!_left)
            return std::stoi(_node->val());
        int ret = _node->calc(_left->calculate(), _right->calculate());
        return ret;
    }

    friend bool isDigit(const char &ch) {
        return ch >= '0' && ch <= '9';
    }

    // inorder create CalTree
    friend CalTree* parseExpr(const char *expr, size_t left, size_t right) {
        if (left == right)
            return nullptr;
        size_t pos = -1;
        Node *node;

        for (size_t i = left; i < right; ++i) {
            if (expr[i] == '+') {
                pos = i;
                node = new AddNode(expr[i]);
                break;
            }
            else if (expr[i] == '-') {
                pos = i;
                node = new MinusNode(expr[i]);
                break;
            }
        }

        if (pos == -1)
            for (size_t i = left; i < right; ++i) {
                if (expr[i] == '*') {
                    pos = i;
                    node = new MultiplyNode(expr[i]);
                    break;
                }
                else if (expr[i] == '/') {
                    pos = i;
                    node = new DivideNode(expr[i]);
                    break;
                }
            }

        if (pos != -1) {
            CalTree *root = new CalTree(node);
            root->_left = parseExpr(expr, left, pos);
            root->_right = parseExpr(expr, pos + 1, right);
            return root;
        }
        else
            return new CalTree(new NumberNode(expr, left, right));
    }

    friend CalTree* parseExpr(const char *expr) {
        return parseExpr(expr, 0, std::strlen(expr));
    }

    friend void inorder(CalTree *root) {
        if (root) {
            inorder(root->_left);
            cout << root->_node;
            inorder(root->_right);
        }
    }

public:
// function
    Node node() {
        return *_node;
    }

    CalTree& left() {
        return *_left;
    }

    CalTree& right() {
        return *_right;
    }

    void deleteTree() {
        autoDel();
        delete this;
    }

private:
    void autoDel() {
        if (_node)
            delete _node;
        if (_left) {
            _left->autoDel();
            delete _left;
        }
        if (_right) {
            _right->autoDel();
            delete _right;
        }
    }

private:
    CalTree *_left;
    CalTree *_right;
    Node *_node;
};

#endif // !CALCULATOR_H_
