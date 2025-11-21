#include <vector>
#include <string>

struct TrieNode {
    bool is_leaf;
    std::vector<TrieNode*> children;

    TrieNode() : is_leaf(false), children(std::vector<TrieNode*>(26, nullptr)) {};
};

class Trie {
    private:
        TrieNode* root;
        void cleanup(TrieNode* node);
        bool remove_helper(std::string &s, TrieNode* node, int index);
        bool search_helper(std::string &s, TrieNode* node, int index);
        bool prefix_helper(std::string &s, TrieNode* node, int index);

    public:
        Trie();
        ~Trie();

        void insert(std::string s);
        void remove(std::string s);
        bool search(std::string s);
        bool prefix_search(std::string s);
};

Trie::Trie() {
    root = new TrieNode();
}

Trie::~Trie() {
    cleanup(root);
}

void Trie::cleanup(TrieNode* node) {
    for (int i = 0; i < 26; i++) {
        if (node->children[i] != nullptr) cleanup(node->children[i]);
    }
    delete node;
}

void Trie::insert(std::string s) {
    TrieNode* curr = root;
    for (int i = 0; i < s.size(); i++) {
        if (curr->children[s[i] - 'a'] == nullptr) {
            curr->children[s[i] - 'a'] = new TrieNode();
        }
        curr = curr->children[s[i] - 'a'];
    }
    curr->is_leaf = true;
}

void Trie::remove(std::string s) {
    remove_helper(s, root, 0);
}

bool Trie::remove_helper(std::string &s, TrieNode* node, int index) {
    if (index == s.size()) {
        return node->is_leaf;
    }
    TrieNode* child = node->children[s[index] - 'a'];
    if (child == nullptr) return false;

    bool d = remove_helper(s, child, index + 1);
    if (d) {
        delete child;
        if (!node->is_leaf) {
            for (auto *c : node->children) {
                if (c != nullptr) return false;
            }
        }
    }
    return d;
}

bool Trie::search(std::string s) {
    return search_helper(s, root, 0);
}

bool Trie::search_helper(std::string &s, TrieNode* node, int index) {
    if (index == s.size()) return node->is_leaf;
    TrieNode* child = node->children[s[index] - 'a'];
    if (child) return search_helper(s, child, index + 1);
    else return false;
}

bool Trie::prefix_search(std::string s) {
   return prefix_helper(s, root, 0);
}

bool Trie::prefix_helper(std::string &s, TrieNode* node, int index) {
    if (index == s.size()) return true;
    TrieNode* child = node->children[s[index] - 'a'];
    if (child) return prefix_helper(s, child, index + 1);
    else return false;
}