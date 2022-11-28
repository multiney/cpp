#include "../include-file.h"
#include <algorithm>
#include <climits>
#include <queue>
#include <string>
#include <sys/types.h>

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
 * 515. Find Largest Value in Each Tree Row __U__
 *
 * Constraints:
 * The number of nodes in the tree will be in the range [0, 104].
 * -231 <= Node.val <= 231 - 1
 */
vector<int> largestValues(TreeNode* root) {
    if (!root) return {};
    vector<int> ret;
    queue<TreeNode*> que;
    que.push(root);
    TreeNode *node;
    int size, maxVal;
    while (!que.empty()) {
        size = que.size();
        maxVal = que.front()->val;
        while (size--) {
            node = que.front();
            que.pop();
            maxVal = std::max(maxVal, node->val);
            if (node->left) que.push(node->left);
            if (node->right) que.push(node->right);
        }
        ret.push_back(maxVal);
    }
    return ret;
}

void largestValuesTraversal(TreeNode *root, int depth, vector<int> &vec) {
    if (!root) return;
    if (vec.size() == depth) vec.push_back(INT_MIN);
    vec[depth] = std::max(vec[depth], root->val);
    largestValuesTraversal(root->left, depth + 1, vec);
    largestValuesTraversal(root->right, depth + 1, vec);
}

vector<int> largestValues2(TreeNode* root) {
    vector<int> ret;
    largestValuesTraversal(root, 0, ret);
    return ret;
}

/*
 * Definition for a Node.
 */
class Node2 {
public:
    int val;
    Node2* left;
    Node2* right;
    Node2* next;

    Node2() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node2(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node2(int _val, Node2* _left, Node2* _right, Node2* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

/**
 * 116. Populating Next Right Pointers in Each Node __U__
 *
 * Constraints:
 * The number of nodes in the tree is in the range [0, 212 - 1].
 * -1000 <= Node.val <= 1000
 */
Node2* connect(Node2* root) {
    if (!root) return nullptr;
    queue<Node2*> que;
    que.push(root);
    Node2* node;
    int size;
    while (!que.empty()) {
        size = que.size();
        while (size--) {
            node = que.front();
            que.pop();
            if (size)
                node->next = que.front();
            else
                node->next = nullptr;
            if (node->left) que.push(node->left);
            if (node->right) que.push(node->right);
        }
    }
    return root;
}

/**
 * 117. Populating Next Right Pointers in Each Node II __U__
 *
 * Constraints:
 * The number of nodes in the tree is in the range [0, 6000].
 * -100 <= Node.val <= 100
 */
Node2* connect2(Node2* root) {
    Node2* levelStart = root;
    Node2* curr;
    while (levelStart) {
        curr = levelStart;
        while (curr) {
            if (curr->left) curr->left->next = curr->right;
            if (curr->right && curr->next) curr->right->next = curr->next->left;
            curr = curr->next;
        }
        levelStart = levelStart->left;
    }
    return root;
}

/**
 * 104. Maximum Depth of Binary Tree
 *
 * Constraints:
 * The number of nodes in the tree is in the range [0, 104].
 * -100 <= Node.val <= 100
 */
int maxDepth(TreeNode* root) { // postorder
    return root ? std::max(maxDepth(root->left), maxDepth(root->right)) + 1 : 0;
}

int maxDepth2(TreeNode *root) {
    if (!root) return 0;
    stack<TreeNode*> nodeStk;
    stack<int> depthStk;
    nodeStk.push(root);
    depthStk.push(1);
    TreeNode *node;
    int ret = 0, temp;
    while (!nodeStk.empty()) {
        node = nodeStk.top(); nodeStk.pop();
        temp = depthStk.top(); depthStk.pop();
        ret = std::max(ret, temp);
        if (node->left) {
            nodeStk.push(node->left);
            depthStk.push(temp + 1);
        }
        if (node->right) {
            nodeStk.push(node->right);
            depthStk.push(temp + 1);
        }
    }
    return ret;
}

int retDepth;

void getDepth(TreeNode *root, int depth) {
    retDepth = retDepth < depth ? depth : retDepth; // mid
    if (!root->left && !root->right) return;
    if (root->left) getDepth(root->left, depth + 1); // left
    if (root->right) getDepth(root->right, depth + 1); // right
}

int maxDepth3(TreeNode *root) {
    retDepth = 0;
    if (!root) return 0;
    getDepth(root, 1);
    return retDepth;
}

int getDepth(TreeNode* cur) { // TODO: figure out it
    stack<TreeNode*> st;
    if (cur != NULL) st.push(cur);
    int depth = 0; // 记录深度
    int result = 0;
    while (!st.empty()) {
        TreeNode* node = st.top();
        if (node != NULL) {
            st.pop();
            st.push(node);                          // 中
            st.push(NULL);
            depth++;
            if (node->right) st.push(node->right);  // 右
            if (node->left) st.push(node->left);    // 左

        } else {
            st.pop();
            node = st.top();
            st.pop();
            depth--;
        }
        result = result > depth ? result : depth;
    }
    return result;
}

/**
 * 559. Maximum Depth of N-ary Tree
 *
 * Constraints:
 * The total number of nodes is in the range [0, 104].
 * The depth of the n-ary tree is less than or equal to 1000.
 */
int maxDepth(Node* root) {
    if (!root) return 0;
    int depth = 0;
    for (Node *node : root->children)
        depth = std::max(maxDepth(node), depth);
    return depth + 1;
}

/**
 * 111. Minimum Depth of Binary Tree
 *
 * Constraints:
 * The number of nodes in the tree is in the range [0, 105].
 * -1000 <= Node.val <= 1000
 */
int minDepth(TreeNode* root) {
    if (!root) return 0;
    if (!root->left && !root->right) return 1;
    if (root->left && root->right)
        return std::min(minDepth(root->left), minDepth(root->right)) + 1;
    else if (root->left)
        return minDepth(root->left) + 1;
    else
        return minDepth(root->right) + 1;
}

/**
 * ------------------------------------------
 * 102=======================================
 */

/**
 * 226. Invert Binary Tree
 *
 * Constraints:
 * The number of nodes in the tree is in the range [0, 100].
 * -100 <= Node.val <= 100
 */
TreeNode* invertTree(TreeNode* root) {
    if (!root) return nullptr;
    std::swap(root->left, root->right); // 后序也可
    invertTree(root->left);
    invertTree(root->right);
    return root;
}

TreeNode* invertTree2(TreeNode *root) {
    if (!root) return nullptr;
    invertTree(root->left);
    std::swap(root->left, root->right);
    invertTree(root->left);
    return root;
}

void printStack(stack<TreeNode*> &stk) {
    if (stk.empty()) return;
    stack<TreeNode*> temp;
    while (!stk.empty()) {
        temp.push(stk.top());
        stk.pop();
    }
    while (!temp.empty()) {
        cout << temp.top()->val << " ";
        stk.push(temp.top());
        temp.pop();
    }
    cout << "stk" << endl;
}

TreeNode* invertTree3(TreeNode *root) {
    if (!root) return nullptr;
    stack<TreeNode*> stk;
    TreeNode *curr = root;
    while (curr || !stk.empty()) {
        if (curr) {
            std::swap(curr->left, curr->right);
            stk.push(curr);
            curr = curr->left;
        } else {
            curr = stk.top()->right;
            stk.pop();
        }
    }
    return root;
}

/**
 * 101. Symmetric Tree // TODO: 100 572
 *
 * Constraints:
 * The number of nodes in the tree is in the range [1, 1000].
 * -100 <= Node.val <= 100
 */
bool isEqual(TreeNode *left, TreeNode *right) {
    if (!left && !right) return true;
    if (!left || !right || (left->val != right->val)) return false;
    return isEqual(left->left, right->right) && isEqual(left->right, right->left);
}
bool isSymmetric(TreeNode* root) {
    return isEqual(root->left, root->right);
}

bool isSymmetric2(TreeNode *root) {
    stack<TreeNode*> stk;
    stk.push(root->right);
    stk.push(root->left);
    TreeNode *left, *right;
    while (!stk.empty()) {
        left = stk.top(); stk.pop();
        right = stk.top(); stk.pop();
        if (!left && !right) continue;
        if (!left || !right || left->val != right->val) return false;
        stk.push(right->left);
        stk.push(left->right);
        stk.push(right->right);
        stk.push(left->left);
    }
    return true;
}

bool isSymmetric3(TreeNode * root) {
    queue<TreeNode*> que;
    que.push(root->left);
    que.push(root->right);
    TreeNode *left, *right;
    while (!que.empty()) {
        left = que.front(); que.pop();
        right = que.front(); que.pop();
        if (!left && !right) continue;
        if (!left || !right || left->val != right->val) return false;
        que.push(left->left);
        que.push(right->right);
        que.push(left->right);
        que.push(right->left);
    }
    return true;
}

/**
 * 222. Count Complete Tree Nodes
 *
 * Constraints:
 * The number of nodes in the tree is in the range [0, 5 * 104].
 * 0 <= Node.val <= 5 * 104
 * The tree is guaranteed to be complete.
 */
int countNodes(TreeNode* root) {
    return root ? 1 + countNodes(root->left) + countNodes(root->right) : 0;
}

int countNodes2(TreeNode* root) {
    stack<TreeNode*> stk;
    TreeNode *curr = root;
    int ret = 0;
    while (curr || !stk.empty()) {
        if (curr) {
            stk.push(curr);
            curr = curr->left;
            ++ret;
        } else {
            curr = stk.top()->right;
            stk.pop();
        }
    }
    return ret;
}

/**
 * 110. Balanced Binary Tree
 *
 * Constraints:
 * The number of nodes in the tree is in the range [0, 5000].
 * -104 <= Node.val <= 104
 */
int getHeight(TreeNode *node) {
    if (!node) return 0;
    int leftHeight = getHeight(node->left);
    if (leftHeight == -1) return -1;
    int rightHeight = getHeight(node->right);
    if (rightHeight == -1) return -1;
    return std::abs(leftHeight - rightHeight) > 1 ? -1 : std::max(leftHeight, rightHeight) + 1;
}

bool isBalanced(TreeNode* root) {
    return getHeight(root) != -1;
}

/**
 * 257. Binary Tree Paths
 *
 * Constraints:
 * The number of nodes in the tree is in the range [1, 100].
 * -100 <= Node.val <= 100
 */
void pathTraversal(TreeNode *curr, string path, vector<string> &vec) {
    path += std::to_string(curr->val);
    if (!curr->left && !curr->right) {
        vec.push_back(path);
        return;
    }
    if (curr->left) pathTraversal(curr->left, path + "->", vec);
    if (curr->right) pathTraversal(curr->right, path + "->", vec);
}

vector<string> binaryTreePaths(TreeNode* root) {
    vector<string> ret;
    string path;
    pathTraversal(root, path, ret);
    return ret;
}

vector<string> binaryTreePaths2(TreeNode *root) {
    vector<string> ret;
    stack<TreeNode*> nodeStk;
    stack<string> pathStk;
    nodeStk.push(root);
    pathStk.push(std::to_string(root->val));
    while (!nodeStk.empty()) {
        TreeNode *curr = nodeStk.top(); nodeStk.pop();
        string path = pathStk.top(); pathStk.pop();
        if (!curr->left && !curr->right)
            ret.push_back(path);
        if (curr->left) {
            nodeStk.push(curr->left);
            pathStk.push(path + "->" + std::to_string(curr->left->val));
        }
        if (curr->right) {
            nodeStk.push(curr->right);
            pathStk.push(path + "->" + std::to_string(curr->right->val));
        }
    }
    return ret;
}

/**
 * 404. Sum of Left Leaves
 *
 * Constraints:
 * The number of nodes in the tree is in the range [1, 1000].
 * -1000 <= Node.val <= 1000
 */
int sumOfLeftLeaves(TreeNode* root) {
    if (!root) return 0;
    if (root->left && !root->left->left && !root->left->right) return root->left->val + sumOfLeftLeaves(root->right);
    return sumOfLeftLeaves(root->left) + sumOfLeftLeaves(root->right);
}

int sumOfLeftLeaves2(TreeNode* root) {
    stack<TreeNode*> stk;
    int ret = 0;
    while (root || !stk.empty()) {
        if (root) {
            stk.push(root);
            if (root->left && !root->left->left && !root->left->right) {
                ret += root->left->val;
                root = nullptr;
                continue;
            }
            root = root->left;
        } else {
            root = stk.top()->right;
            stk.pop();
        }
    }
    return ret;
}

/**
 * 513. Find Bottom Left Tree Value
 *
 * Constraints:
 * The number of nodes in the tree is in the range [1, 104].
 * -231 <= Node.val <= 231 - 1
 */
void findBottomLeftValueTraversal(TreeNode* root, int depth, int &maxDepth, int &ret) {
    if (!root) return;
    if (root->left) findBottomLeftValueTraversal(root->left, depth + 1, maxDepth, ret);
    if (root->right) findBottomLeftValueTraversal(root->right, depth + 1, maxDepth, ret);
    if (depth > maxDepth) {
        maxDepth = depth;
        ret = root->val;
    }
}
int findBottomLeftValue(TreeNode* root) {
    int maxDepth = INT_MIN;
    int ret;
    findBottomLeftValueTraversal(root, 0, maxDepth, ret);
    return ret;
}

/**
 * 112. Path Sum
 *
 * Constraints:
 * The number of nodes in the tree is in the range [0, 5000].
 * -1000 <= Node.val <= 1000
 * -1000 <= targetSum <= 1000
 */
bool hasPathSum(TreeNode* root, int targetSum) {
    if (!root) return false;
    if (!root->left && !root->right && targetSum == root->val) return true;
    return hasPathSum(root->left, targetSum - root->val) || hasPathSum(root->right, targetSum - root->val);
}

/*
bool hasPathSum2(TreeNode *root, int targetSum) { TODO: figure out it
    stack<TreeNode*> stk;
    stack<int> numStk;
    while (root || !stk.empty()) {
        if (root) {
            stk.push(root);
            numStk.push
            if (!root->left && !root->right && targetSum == numStk.top()) return true;
        }
    }
}
*/

/**
 * 106. Construct Binary Tree from Inorder and Postorder Traversal
 *
 * Constraints:
 * 1 <= inorder.length <= 3000
 * postorder.length == inorder.length
 * -3000 <= inorder[i], postorder[i] <= 3000
 * inorder and postorder consist of unique values.
 * Each value of postorder also appears in inorder.
 * inorder is guaranteed to be the inorder traversal of the tree.
 * postorder is guaranteed to be the postorder traversal of the tree.
 */
TreeNode* buildTreeHelper(vector<int> &inorder, int inBeg, int inEnd, vector<int> &postorder, int postBeg, int postEnd) {
    if (inBeg >= inEnd) return nullptr;
    TreeNode *root = new TreeNode(postorder[postEnd - 1]);
    int delimiterIndex;
    for (delimiterIndex = inBeg; delimiterIndex < inEnd; ++delimiterIndex)
        if (inorder[delimiterIndex] == postorder[postEnd - 1]) break;
    root->left = buildTreeHelper(inorder, inBeg, delimiterIndex, postorder, postBeg, postBeg + (delimiterIndex - inBeg));
    root->right = buildTreeHelper(inorder, delimiterIndex + 1, inEnd, postorder, postBeg + (delimiterIndex - inBeg), postEnd - 1);
    return root;
}
TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
    return buildTreeHelper(inorder, 0, inorder.size(), postorder, 0, postorder.size());
}

/**
 * 654. Maximum Binary Tree
 *
 * Constraints:
 * 1 <= nums.length <= 1000
 * 0 <= nums[i] <= 1000
 * All integers in nums are unique.
 */
TreeNode* constructMaximumBinaryTreeHelper(vector<int> &nums, int beg, int end) {
    if (beg == end) return nullptr;
    int maxIndex = beg;
    for (int i = beg; i < end; ++i)
        if (nums[maxIndex] < nums[i])
            maxIndex = i;
    TreeNode *root = new TreeNode(nums[maxIndex]);
    root->left = constructMaximumBinaryTreeHelper(nums, beg, maxIndex);
    root->right = constructMaximumBinaryTreeHelper(nums, maxIndex + 1, end);
    return root;
}
TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
    return constructMaximumBinaryTreeHelper(nums, 0, nums.size());
}

/**
 * 617. Merge Two Binary Trees
 * 
 * Constraints:
 * The number of nodes in both trees is in the range [0, 2000].
 * -104 <= Node.val <= 104
 */
TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
    if (!root1) return root2;
    if (!root2) return root1;
    root1->val += root2->val;
    root1->left = mergeTrees(root1->left, root2->left);
    root1->right = mergeTrees(root1->right, root2->right);
    return root1;
}

/*
TreeNode* mergeTrees2(TreeNode* root1, TreeNode* root2) { TODO: figure out it
    stack<TreeNode*> stk;
    TreeNode *curr1 = root1, *curr2 = root2;
    while (curr1 || !stk.empty()) {
        if (!curr1->left) {
            
        }
        if (curr1) {
            
        }
    }
}
*/

TreeNode* mergeTrees2(TreeNode* t1, TreeNode* t2) {
    if (t1 == NULL) return t2;
    if (t2 == NULL) return t1;
    queue<TreeNode*> que;
    que.push(t1);
    que.push(t2);
    while(!que.empty()) {
        TreeNode* node1 = que.front(); que.pop();
        TreeNode* node2 = que.front(); que.pop();
        // 此时两个节点一定不为空，val相加
        node1->val += node2->val;

        // 如果两棵树左节点都不为空，加入队列
        if (node1->left != NULL && node2->left != NULL) {
            que.push(node1->left);
            que.push(node2->left);
        }
        // 如果两棵树右节点都不为空，加入队列
        if (node1->right != NULL && node2->right != NULL) {
            que.push(node1->right);
            que.push(node2->right);
        }

        // 当t1的左节点 为空 t2左节点不为空，就赋值过去
        if (node1->left == NULL && node2->left != NULL) {
            node1->left = node2->left;
        }
        // 当t1的右节点 为空 t2右节点不为空，就赋值过去
        if (node1->right == NULL && node2->right != NULL) {
            node1->right = node2->right;
        }
    }
    return t1;
}

/**
 * 700. Search in a Binary Search Tree
 *
 * Constraints:
 * The number of nodes in the tree is in the range [1, 5000].
 * 1 <= Node.val <= 107
 * root is a binary search tree.
 * 1 <= val <= 107
 */
TreeNode* searchBST(TreeNode* root, int val) {
    if (!root) return nullptr;
    if (root->val > val) return searchBST(root->left, val);
    if (root->val < val) return searchBST(root->right, val);
    return root;
}

TreeNode* searchBST2(TreeNode *root, int val) {
    while (root) {
        if (root->val > val) root = root->left;
        else if (root->val < val) root = root->right;
        else return root;
    }
    return nullptr;
}

/**
 * 98. Validate Binary Search Tree
 *
 * Constraints:
 * The number of nodes in the tree is in the range [1, 104].
 * -231 <= Node.val <= 231 - 1
 */
TreeNode *pre = nullptr;
bool isValidBST(TreeNode* root) {
    if (!root) return true;
    bool left = isValidBST(root->left);
    if (pre != nullptr && pre->val >= root->val) return false;
    pre = root;
    bool right = isValidBST(root->right);
    return left && right;
}

bool isValidBST2(TreeNode *root) {
    stack<TreeNode*> stk;
    TreeNode *pre = nullptr;
    while (root || !stk.empty()) {
        if (root) {
            stk.push(root);
            root = root->left;
        } else {
            root = stk.top();
            stk.pop();
            if (pre && pre->val >= root->val) return false;
            pre = root;
            root = root->right;
        }
    }
    return true;
}

/**
 * 530. Minimum Absolute Difference in BST
 * 
 * Constraints:
 * The number of nodes in the tree is in the range [2, 104].
 * 0 <= Node.val <= 105
 */
int minDifference = INT_MAX;
TreeNode *preNode = nullptr;
int getMinimumDifference(TreeNode* root) {
    if (!root) return 0;
    getMinimumDifference(root->left);
    if (preNode) minDifference = std::min(minDifference, root->val - preNode->val);
    preNode = root;
    getMinimumDifference(root->right);
    return minDifference;
}

int getMinimumDifference2(TreeNode *root) {
    stack<TreeNode*> stk;
    TreeNode *preNode = nullptr;
    int ret = INT_MAX;
    while (root || !stk.empty()) {
        if (root) {
            stk.push(root);
            root = root->left;
        } else {
            root = stk.top();
            stk.pop();
            if (preNode) ret = std::min(ret, root->val - preNode->val);
            preNode = root;
            root = root->right;
        }
    }
    return ret;
}

/**
 * 501. Find Mode in Binary Search Tree
 * 
 * Constraints:
 * The number of nodes in the tree is in the range [1, 104].
 * -105 <= Node.val <= 105
 */
vector<int> findModeRet;
int findModeMaxCount = 0, findModeCount = 0;
TreeNode *findModePre = nullptr;
void findModeTraversal(TreeNode *root) {
    if (!root) return;
    findModeTraversal(root->left);
    if (!findModePre || root->val != findModePre->val)
        findModeCount = 1;
    else
        ++findModeCount;
    findModePre = root;
    if (findModeCount == findModeMaxCount)
        findModeRet.push_back(root->val);
    if (findModeCount > findModeMaxCount) {
        findModeRet.clear();
        findModeRet.push_back(root->val);
        findModeMaxCount = findModeCount;
    }
    findModeTraversal(root->right);
}

vector<int> findMode(TreeNode* root) {
    findModeTraversal(root);
    return findModeRet;
}

/**
 * 236. Lowest Common Ancestor of a Binary Tree
 *
 * Constraints:
 * The number of nodes in the tree is in the range [2, 105].
 * -109 <= Node.val <= 109
 * All Node.val are unique.
 * p != q
 * p and q will exist in the tree.
 */
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root || root == p || root == q) return root;
    TreeNode *left = lowestCommonAncestor(root->left, p, q);
    TreeNode *right = lowestCommonAncestor(root->right, p, q);
    if (left && right) return root;
    if (left) return left;
    return right;
}

/**
 * 235. Lowest Common Ancestor of a Binary Search Tree
 *
 * Constraints:
 * The number of nodes in the tree is in the range [2, 105].
 * -109 <= Node.val <= 109
 * All Node.val are unique.
 * p != q
 * p and q will exist in the BST.
 */
TreeNode* lowestCommonAncestor2(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (root->val > p->val && root->val > q->val)
        return lowestCommonAncestor2(root->left, p, q);
    if (root->val < p->val && root->val < q->val)
        return lowestCommonAncestor2(root->right, p, q);
    return root;
}

TreeNode* lowestCommonAncestor3(TreeNode* root, TreeNode* p, TreeNode* q) {
    while (true) {
        if (root->val > p->val && root->val > q->val) root = root->left;
        else if (root->val < p->val && root->val < q->val) root = root->right;
        else return root;
    }
    return nullptr;
}

/**
 * 701. Insert into a Binary Search Tree
 *
 * Constraints:
 * The number of nodes in the tree will be in the range [0, 104].
 * -108 <= Node.val <= 108
 * All the values Node.val are unique.
 * -108 <= val <= 108
 * It's guaranteed that val does not exist in the original BST.
 */
TreeNode *insertIntoBSTPre = nullptr;
void insertIntoBSTHelper(TreeNode *root, int val) {
    if (!root) {
        if (insertIntoBSTPre->val > val)
            insertIntoBSTPre->left = new TreeNode(val);
        else
            insertIntoBSTPre->right = new TreeNode(val);
        return;
    }
    insertIntoBSTPre = root;
    if (root->val > val) insertIntoBSTHelper(root->left, val);
    else insertIntoBSTHelper(root->right, val);
}
TreeNode* insertIntoBST(TreeNode* root, int val) {
    if (!root) return new TreeNode(val);
    insertIntoBSTHelper(root, val);
    return root;
}

TreeNode* insertIntoBST2(TreeNode* root, int val) {
    if (!root) return new TreeNode(val);
    TreeNode *curr = root, *pre;
    while (curr) {
        pre = curr;
        if (curr->val > val) curr = curr->left;
        else curr = curr->right;
    }
    if (pre->val > val) pre->left = new TreeNode(val);
    else pre->right = new TreeNode(val);
    return root;
}

/**
 * 450. Delete Node in a BST
 *
 * Constraints:
 * The number of nodes in the tree is in the range [0, 104].
 * -105 <= Node.val <= 105
 * Each node has a unique value.
 * root is a valid binary search tree.
 * -105 <= key <= 105
 */
TreeNode* deleteNode(TreeNode* root, int key) {
    if (!root) return nullptr;
    if (root->val == key) {
        if (!root->left && !root->right) {
            delete root;
            return nullptr;
        } else if (!root->left) {
            TreeNode *temp = root->right;
            delete root;
            return temp;
        } else if (!root->right) {
            TreeNode *temp = root->left;
            delete root;
            return temp;
        } else {
            TreeNode *curr = root->left;
            while (curr->right)
                curr = curr->right;
            TreeNode *temp = root;
            curr->right = root->right;
            root = root->left;
            delete temp;
            return root;
        }
    }
    if (root->val > key) root->left = deleteNode(root->left, key);
    else root->right = deleteNode(root->right, key);
    return root;
}

TreeNode* deleteTargetNode(TreeNode *target) {
    TreeNode *temp = target;
    if (!target->left) {
        target = target->right;
        delete temp;
        return target;
    }
    TreeNode *node = target->left;
    while (node->right) node = node->right;
    node->right = target->right;
    target = target->left;
    delete temp;
    return target;
}

TreeNode *deleteNode2(TreeNode *root, int key) {
    if (!root) return nullptr;
    TreeNode *curr = root, *pre = nullptr;
    while (curr) {
        if (curr->val == key) break;
        pre = curr;
        if (curr->val > key) curr = curr->left;
        else curr = curr->right;
    }
    if (!pre)
        return deleteTargetNode(curr);
    if (pre->left && pre->left->val == key)
        pre->left = deleteTargetNode(curr);
    else if (pre->right && pre->right->val == key)
        pre->right = deleteTargetNode(curr);
    return root;
}

TreeNode* deleteNode3(TreeNode* root, int key) {
    if (!root) return nullptr;
    if (root->val == key) {
        if (!root->left) {
            TreeNode *temp = root;
            root = root->right;
            delete temp;
            return root;
        }
        TreeNode *curr = root->left;
        while (curr->right) curr = curr->right;
        std::swap(root->val, curr->val);
    }
    root->left = deleteNode3(root->left, key);
    root->right = deleteNode3(root->right, key);
    return root;
}

/**
 * 669. Trim a Binary Search Tree
 * 
 * Constraints:
 * The number of nodes in the tree is in the range [1, 104].
 * 0 <= Node.val <= 104
 * The value of each node in the tree is unique.
 * root is guaranteed to be a valid binary search tree.
 * 0 <= low <= high <= 104
 */
TreeNode* trimBST(TreeNode* root, int low, int high) {
    if (!root) return nullptr;
    if (root->val < low) return trimBST(root->right, low, high);
    if (root->val > high) return trimBST(root->left, low, high);
    root->left = trimBST(root->left, low, high);
    root->right = trimBST(root->right, low, high);
    return root;
}

TreeNode* trimBST2(TreeNode* root, int low, int high) {
    while (root) {
        if (root->val < low) root = root->right;
        else if (root->val > high) root = root->left;
        else break;
    }
    if (!root) return nullptr;
    TreeNode *curr = root;
    while (curr) {
        while (curr->left && curr->left->val < low)
            curr->left = curr->left->right;
        curr = curr->left;
    }
    curr = root;
    while (curr) {
        while (curr->right && curr->right->val > high)
            curr->right = curr->right->left;
        curr = curr->right;
    }
    return root;
}

/**
 * 108. Convert Sorted Array to Binary Search Tree
 * 
 * Constraints:
 * 1 <= nums.length <= 104
 * -104 <= nums[i] <= 104
 * nums is sorted in a strictly increasing order.
 */
TreeNode* sortedArrayToBSTHelper(vector<int>& nums, int beg, int end) {
    if (beg == end) return nullptr;
    int mid = beg + ((end - beg) >> 1);
    TreeNode *node = new TreeNode(nums[mid]);
    node->left = sortedArrayToBSTHelper(nums, beg, mid);
    node->right = sortedArrayToBSTHelper(nums, mid + 1, end);
    return node;
}
TreeNode* sortedArrayToBST(vector<int>& nums) {
    return sortedArrayToBSTHelper(nums, 0, nums.size());
}

TreeNode* sortedArrayToBST2(vector<int>& nums) {
    queue<TreeNode*> nodeQue;
    queue<int> indexQue;
    TreeNode* root = new TreeNode(0);
    nodeQue.push(root);
    indexQue.push(0);
    indexQue.push(nums.size() - 1);
    while (!nodeQue.empty()) {
        TreeNode *node = nodeQue.front(); nodeQue.pop();
        int left = indexQue.front(); indexQue.pop();
        int right = indexQue.front(); indexQue.pop();
        int mid = left + ((right - left) >> 1);
        node->val = nums[mid];
        if (left <= mid - 1) {
            node->left = new TreeNode(0);
            nodeQue.push(node->left);
            indexQue.push(left);
            indexQue.push(mid - 1);
        }
        if (right >= mid + 1) {
            node->right = new TreeNode(0);
            nodeQue.push(node->right);
            indexQue.push(mid + 1);
            indexQue.push(right);
        }
    }
    return root;
}

/**
 * 538. Convert BST to Greater Tree
 * 
 * Constraints:
 * The number of nodes in the tree is in the range [0, 104].
 * -104 <= Node.val <= 104
 * All the values in the tree are unique.
 * root is guaranteed to be a valid binary search tree.
 */
TreeNode *convertBSTPre = nullptr;
void convertBSTTraversal(TreeNode* curr) {
    if (!curr) return;
    convertBSTTraversal(curr->right);
    if (convertBSTPre) curr->val += convertBSTPre->val;
    convertBSTPre = curr;
    convertBSTTraversal(curr->left);
}
TreeNode* convertBST(TreeNode* root) {
    convertBSTTraversal(root);
    return root;
}


TreeNode* convertBST2(TreeNode* root) {
    int pre = 0;
    stack<TreeNode*> stk;
    TreeNode *curr = root;
    while (curr || !stk.empty()) {
        if (curr) {
            stk.push(curr);
            curr = curr->right;
        } else {
            curr = stk.top();
            stk.pop();
            curr->val += pre;
            pre = curr->val;
            curr = curr->left;
        }
    }
    return root;
}

int main (int argc, char *argv[])
{
    TreeNode *root = new TreeNode(4, new TreeNode(2, new TreeNode(1), new TreeNode(3)), new TreeNode(7, new TreeNode(6), new TreeNode(9)));
    TreeNode *node = new TreeNode(3, new TreeNode(9), new TreeNode(20, new TreeNode(15), new TreeNode(7)));
    TreeNode *nodeForFindMode = new TreeNode(1, nullptr, new TreeNode(2, new TreeNode(2), nullptr));
    TreeNode *nodeForDeleteNode = new TreeNode (5, new TreeNode(3, new TreeNode(2), new TreeNode(4)), new TreeNode(6, nullptr, new TreeNode(7)));
    auto vec1 = preorderTraversal(nodeForDeleteNode);
    for (int i : vec1)
        cout << i << " ";
    cout << endl;
    deleteNode2(nodeForDeleteNode, 3);
    auto vec = preorderTraversal(nodeForDeleteNode);
    for (int i : vec)
        cout << i << " ";
    cout << endl;
    return 0;
}


