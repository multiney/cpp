#include "../include-file.h"

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
