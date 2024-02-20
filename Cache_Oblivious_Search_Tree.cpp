#include <iostream>
#include <vector>
#include <algorithm>
const int BLOCK_SIZE = 4;
template <typename T>
class CacheObliviousSearchTree {
private:
    struct Node {
        T key;
        Node* left;
        Node* right;
        Node(const T& k) : key(k), left(nullptr), right(nullptr) {}
    };
    Node* root;
    Node* insert(Node* node, const T& key) {
        if (node == nullptr) {
            return new Node(key);
        }
        if (key < node->key) {
            node->left = insert(node->left, key);
        } else if (key > node->key) {
            node->right = insert(node->right, key);
        }
        return node;
    }
    void inorderTraversal(Node* node, std::vector<T>& result) const {
        if (node != nullptr) {
            inorderTraversal(node->left, result);
            result.push_back(node->key);
            inorderTraversal(node->right, result);
        }
    }
    void preorderTraversal(Node* node, std::vector<T>& result) const {
        if (node != nullptr) {
            result.push_back(node->key);
            preorderTraversal(node->left, result);
            preorderTraversal(node->right, result);
        }
    }
    void postorderTraversal(Node* node, std::vector<T>& result) const {
        if (node != nullptr) {
            postorderTraversal(node->left, result);
            postorderTraversal(node->right, result);
            result.push_back(node->key);
        }
    }
    Node* findMin(Node* node) const {
        while (node != nullptr && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
    Node* remove(Node* node, const T& key) {
        if (node == nullptr) {
            return nullptr;
        }
        if (key < node->key) {
            node->left = remove(node->left, key);
        } else if (key > node->key) {
            node->right = remove(node->right, key);
        } else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            Node* temp = findMin(node->right);
            node->key = temp->key;
            node->right = remove(node->right, temp->key);
        }
        return node;
    }
    bool search(Node* node, const T& key) const {
        while (node != nullptr) {
            if (key == node->key) {
                return true;
            } else if (key < node->key) {
                node = node->left;
            } else {
                node = node->right;
            }
        }
        return false;
    }
public:
    CacheObliviousSearchTree() : root(nullptr) {}
    void insert(const T& key) {
        root = insert(root, key);
    }
    std::vector<T> inorderTraversal() const {
        std::vector<T> result;
        inorderTraversal(root, result);
        return result;
    }
    std::vector<T> preorderTraversal() const {
        std::vector<T> result;
        preorderTraversal(root, result);
        return result;
    }
    std::vector<T> postorderTraversal() const {
        std::vector<T> result;
        postorderTraversal(root, result);
        return result;
    }
    T findMin() const {
        if (root == nullptr) {
            throw std::runtime_error("Tree is empty");
        }
        Node* minNode = findMin(root);
        return minNode->key;
    }
    void remove(const T& key) {
        root = remove(root, key);
    }
    bool search(const T& key) const {
        return search(root, key);
    }
};

int main() {
    CacheObliviousSearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);
    std::cout << "Inorder Traversal: ";
    for (const auto& key : tree.inorderTraversal()) {
        std::cout << key << " ";
    }
    std::cout << std::endl;
    std::cout << "Preorder Traversal: ";
    for (const auto& key : tree.preorderTraversal()) {
        std::cout << key << " ";
    }
    std::cout << std::endl;
    std::cout << "Postorder Traversal: ";
    for (const auto& key : tree.postorderTraversal()) {
        std::cout << key << " ";
    }
    std::cout << std::endl;
    std::cout << "Minimum Key: " << tree.findMin() << std::endl;
    int keyToRemove = 3;
    std::cout << "Removing key " << keyToRemove << std::endl;
    tree.remove(keyToRemove);
    int keyToSearch = 6;
    if (tree.search(keyToSearch)) {
        std::cout << keyToSearch << " found in the tree." << std::endl;
    } else {
        std::cout << keyToSearch << " not found in the tree." << std::endl;
    }
    return 0;
}
