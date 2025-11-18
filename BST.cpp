struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int v, TreeNode* l, TreeNode *r) : val(v), left(l), right(r) {};
};

class Tree {
private:
    TreeNode* root;
    void insert_helper(int val, TreeNode* node);  
    TreeNode* get_successor(TreeNode* node);
    TreeNode* remove_helper(int val, TreeNode* node);
    void cleanup(TreeNode* node);
public:
    Tree(): root(nullptr) {};
    ~Tree() { cleanup(root); };
    TreeNode* find(int val);
    void insert(int val);
    void remove(int val);
};

TreeNode* Tree::find(int val) {
    TreeNode* curr = root;
    while (curr) {
        if (curr->val == val) return curr;
        if (curr->val > val) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    return nullptr;
}

void Tree::insert_helper(int val, TreeNode* node) {
    if (node->val == val) return;
    if (node->val > val) {
        if (node->left == nullptr) node->left = new TreeNode(val, nullptr, nullptr);
        else insert_helper(val, node->left);
    } else {
        if (node->right == nullptr) node->right = new TreeNode(val, nullptr, nullptr);
        else insert_helper(val, node->right);
    }
}

void Tree::insert(int val) {
    if (root == nullptr) {
        root = new TreeNode(val, nullptr, nullptr);
    } else {
        insert_helper(val, root);
    }
}

TreeNode* Tree::get_successor(TreeNode* node) {
    if (node->left == nullptr) return node;
    return get_successor(node->left);
}

TreeNode* Tree::remove_helper(int val, TreeNode* node) {
    if (node->val == val) {
        /* one or zero children */
        if (node->left == nullptr) {
            TreeNode* temp = node->right;
            delete node;
            return temp;
        }
        if (node->right == nullptr) {
            TreeNode* temp = node->left;
            delete node;
            return temp;
        }

        /* two children */
        TreeNode* s = get_successor(node->right);
        node->val = s->val;
        node->right = remove_helper(s->val, node->right);
    }
    else if (node->val > val) {
        if (node->left == nullptr) return  node;
        else node->left = remove_helper(val, node->left);
    } else {
        if (node->right == nullptr) return node;
        else node->right = remove_helper(val, node->right);
    }

    return node;
}

void Tree::remove(int val) {
    if (root == nullptr) {
        return;
    } else {
        root = remove_helper(val, root);
    }
}

void Tree::cleanup(TreeNode* node) {
    if (node == nullptr) return;
    cleanup(node->left);
    cleanup(node->right);
    delete node;
}