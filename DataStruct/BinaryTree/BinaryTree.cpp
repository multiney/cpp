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

/**
 * 94. Binary Tree Inorder Traversal
 *
 * Constraints:
 * The number of nodes in the tree is in the range [0, 100].
 * -100 <= Node.val <= 100
 */
vector<int> inorderTraversal(TreeNode* root) {
    vector<int> ret;
    if (!root) return ret;

    stack<TreeNode*> stk;
    TreeNode *curr = root;
    while (curr || !stk.empty()) {
        if (curr) {
            stk.push(curr);
            curr = curr->left;
        } else {
            curr = stk.top();
            stk.pop();
            ret.push_back(curr->val);
            curr = curr->right;
        }
    }
    return ret;
}
