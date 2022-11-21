#include "../include-file.h"
#include <queue>

/**
 * Definition for a binary tree node.
 */
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/**
 * Definition for a Node.
 */
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};

/**
 * 144. Binary Tree Preorder Traversal
 *
 * Constraints:
 * The number of nodes in the tree is in the range [0, 100].
 * -100 <= Node.val <= 100
 */
void preorder(TreeNode *root, vector<int> &vec) {
    if (!root) return;
    vec.push_back(root->val);
    preorder(root->left, vec);
    preorder(root->right, vec);
}

vector<int> preorderTraversal(TreeNode* root) {
    vector<int> ret;
    preorder(root, ret);
    return ret;
}

vector<int> preorderTraversal2(TreeNode *root) {
    vector<int> ret;
    if (!root) return ret;

    stack<TreeNode*> stk;
    stk.push(root);

    while (!stk.empty()) {
        TreeNode *node = stk.top();
        stk.pop();
        ret.push_back(node->val);

        if (node->right) stk.push(node->right);
        if (node->left) stk.push(node->left);
    }
    return ret;
}

vector<int> preorderTraversal3(TreeNode *root) {
    vector<int> ret;
    if (!root) return ret;

    stack<TreeNode*> stk;
    stk.push(root);

    while (!stk.empty()) {
        TreeNode *node = stk.top();
        stk.pop();

        if (node) {
            if (node->right) stk.push(node->right);
            if (node->left) stk.push(node->left);
            stk.push(node);
            stk.push(nullptr);
        } else {
            ret.push_back(stk.top()->val);
            stk.pop();
        }
    }
    return ret;
}

vector<int> preorderTraversal4(TreeNode *root) {
    vector<int> ret;
    stack<TreeNode*> stk;
    while (root || !stk.empty()) {
        if (root) {
            ret.push_back(root->val);
            if (root->right)
                stk.push(root->right);
            root = root->left;
        } else {
            root = stk.top();
            stk.pop();
        }
    }
    return ret;
}

vector<int> preorderTraversal5(TreeNode *root) {
    vector<int> ret;
    while (root) {
        if (root->left) {
            TreeNode *pre = root->left;
            while (pre->right && pre->right != root)
                pre = pre->right;
            if (!pre->right) {
                pre->right = root;
                ret.push_back(root->val);
                root = root->left;
            } else {
                pre->right = nullptr;
                root = root->right;
            }
        } else {
            ret.push_back(root->val);
            root = root->right;
        }
    }
    return ret;
}
/**
 * 94. Binary Tree Inorder Traversal
 *
 * Constraints:
 * The number of nodes in the tree is in the range [0, 100].
 * -100 <= Node.val <= 100
 */
vector<int> inorderTraversal(TreeNode* root) {
    vector<int> ret;
    stack<TreeNode*> stk;
    while (root || !stk.empty()) {
        if (root) {
            stk.push(root);
            root = root->left;
        } else {
            root = stk.top();
            stk.pop();
            ret.push_back(root->val);
            root = root->right;
        }
    }
    return ret;
}

vector<int> inorderTraversal2(TreeNode *root) {
    vector<int> ret;
    TreeNode *pre;
    while (root) {
        if (root->left) {
            pre = root->left;
            while (pre->right && pre->right != root)
                pre = pre->right;
            if (!pre->right) {
                pre->right = root;
                root = root->left;
            } else {
                pre->right = nullptr;
                ret.push_back(root->val);
                root = root->right;
            }
        } else {
            ret.push_back(root->val);
            root = root->right;
        }
    }
    return ret;
}

/**
 * 145. Binary Tree Postorder Traversal
 *
 * Constraints:
 * The number of the nodes in the tree is in the range [0, 100].
 * -100 <= Node.val <= 100
 */
vector<int> postorderTraversal(TreeNode* root) {
    vector<int> ret;
    stack<TreeNode*> stk;
    TreeNode *last = nullptr;
    while (root || !stk.empty()) {
        if (root) {
            stk.push(root);
            root = root->left;
        } else {
            TreeNode *node = stk.top();
            if (node->right && last != node->right)
                root = node->right;
            else {
                ret.push_back(node->val);
                last = node;
                stk.pop();
            }
        }
    }
    return ret;
}

// class Solution {
// public:
//     vector<int> postorderTraversal(TreeNode* root) {
//         vector<int> nodes;
//         TreeNode* dummy = new TreeNode(0);
//         dummy -> left = root;
//         TreeNode* cur = dummy;
//         while (cur) {
//             if (cur -> left) {
//                 TreeNode* pre = cur -> left;
//                 while (pre -> right && (pre -> right != cur)) {
//                     pre = pre -> right;
//                 }
//                 if (!(pre -> right)) {
//                     pre -> right = cur;
//                     cur = cur -> left;
//                 } else {
//                     reverseAddNodes(cur -> left, pre, nodes);
//                     pre -> right = NULL;
//                     cur = cur -> right;
//                 }
//             } else {
//                 cur = cur -> right;
//             }
//         }
//         return nodes;
//     }
// private:
//     void reverseNodes(TreeNode* start, TreeNode* end) {
//         if (start == end) {
//             return;
//         }
//         TreeNode* x = start;
//         TreeNode* y = start -> right;
//         TreeNode* z;
//         while (x != end) {
//             z = y -> right;
//             y -> right = x;
//             x = y;
//             y = z;
//         }
//     }
//     void reverseAddNodes(TreeNode* start, TreeNode* end, vector<int>& nodes) {
//         reverseNodes(start, end);
//         TreeNode* node = end;
//         while (true) {
//             nodes.push_back(node -> val);
//             if (node == start) {
//                 break;
//             }
//             node = node -> right;
//         }
//         reverseNodes(end, start);
//     }
// };

/**
 * 102=======================================
 * ------------------------------------------
 */

/**
 * 102. Binary Tree Level Order Traversal
 *
 * Constraints:
 * The number of nodes in the tree is in the range [0, 2000].
 * -1000 <= Node.val <= 1000
 */
vector<vector<int>> levelOrder(TreeNode* root) {
    if (!root) return {};
    vector<vector<int>> ret;
    queue<TreeNode*> que;
    que.push(root);
    TreeNode *node;
    int size;
    while (!que.empty()) {
        size = que.size();
        vector<int> level;
        while (size--) {
            node = que.front();
            que.pop();
            level.push_back(node->val);
            if (node->left) que.push(node->left);
            if (node->right) que.push(node->right);
        }
        ret.push_back(level);
    }
    return ret;
}

vector<vector<int>> retVec;

void buildVec(TreeNode *root, int depth) {
    if (!root) return;
    if (retVec.size() == depth)
        retVec.push_back(vector<int>());
    retVec[depth].push_back(root->val);
    if (root->left) buildVec(root->left, depth + 1);
    if (root->right) buildVec(root->right, depth + 1);
}

vector<vector<int>> levelOrder2(TreeNode *root) {
    buildVec(root, 0);
    return retVec;
}

/**
 * 107. Binary Tree Level Order Traversal II
 *
 * The number of nodes in the tree is in the range [0, 2000].
 * -1000 <= Node.val <= 1000
 */
int findDepth(TreeNode *root) {
    if (!root) return 0;
    return std::max(findDepth(root->left), findDepth(root->right)) + 1;
}
vector<vector<int>> levelOrderBottom(TreeNode* root) {
    if (!root) return {};
    int depth = findDepth(root);
    vector<vector<int>> ret(depth);
    queue<TreeNode*> que;
    que.push(root);
    int size;
    TreeNode *node;
    for (int i = depth - 1; i >= 0; --i) {
        size = que.size();
        while (size--) {
            node = que.front();
            que.pop();
            ret[i].push_back(node->val);
            if (node->left) que.push(node->left);
            if (node->right) que.push(node->right);
        }
    }
    return ret;
}

/**
 * 199. Binary Tree Right Side View __U__
 *
 * Constraints:
 * The number of nodes in the tree is in the range [0, 100].
 * -100 <= Node.val <= 100
 */
vector<int> rightSideView(TreeNode* root) {
    if (!root)
        return {};
    vector<int> ret;
    queue<TreeNode*> que;
    que.push(root);
    TreeNode *node;
    int size;
    while (!que.empty()) {
        size = que.size();
        while (size--) {
            node = que.front();
            que.pop();
            if (size == 0)
                ret.push_back(node->val);
            if (node->left) que.push(node->left);
            if (node->right) que.push(node->right);
        }
    }
    return ret;
}

/**
 * 637. Average of Levels in Binary Tree __U__
 *
 * Constraints:
 * The number of nodes in the tree is in the range [1, 104].
 * -231 <= Node.val <= 231 - 1
 */
vector<double> averageOfLevels(TreeNode* root) {
    vector<double> ret;
    queue<TreeNode*> que;
    que.push(root);
    int size;
    double sum;
    TreeNode *node;
    while (!que.empty()) {
        size = que.size();
        sum = 0;
        for (int i = 0; i < size; ++i) {
            node = que.front();
            que.pop();
            sum += node->val;
            if (node->left) que.push(node->left);
            if (node->right) que.push(node->right);
        }
        ret.push_back(sum / size);
    }
    return ret;
}

/**
 * 429. N-ary Tree Level Order Traversal __U__
 *
 * Constraints:
 * The height of the n-ary tree is less than or equal to 1000
 * The total number of nodes is between [0, 104]
 */
vector<vector<int>> levelOrder(Node* root) {
    if (!root) return {};
    vector<vector<int>> ret;
    queue<Node*> que;
    que.push(root);
    int size;
    Node *node;
    while (!que.empty()) {
        size = que.size();
        vector<int> vec;
        while (size--) {
            node = que.front();
            que.pop();
            vec.push_back(node->val);
            for (Node *n : node->children)
                que.push(n);
        }
        ret.push_back(vec);
    }
    return ret;
}

void buildVec(Node *root, int depth) {
    if (!root) return;
    if (retVec.size() == depth)
        retVec.push_back(vector<int>());
    retVec[depth].push_back(root->val);
    for (Node *node : root->children)
        buildVec(node, depth + 1);
}

vector<vector<int>> levelOrder2(Node* root) {
    buildVec(root, 0);
    return retVec;
}


/**
 * ------------------------------------------
 * 102=======================================
 */
