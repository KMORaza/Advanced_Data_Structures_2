#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Node {
    int key;
    vector<int> values;
    Node *left, *right;
    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};
class BurstsortTree {
private:
    Node *root;
    Node* insert(Node* node, int key, int value) {
        if (node == nullptr) {
            node = new Node(key);
            node->values.push_back(value);
        } else if (key < node->key) {
            node->left = insert(node->left, key, value);
        } else if (key > node->key) {
            node->right = insert(node->right, key, value);
        } else {
            node->values.push_back(value);
        }
        return node;
    }
    vector<int> search(Node* node, int key) {
        if (node == nullptr) {
            return vector<int>();
        } else if (key < node->key) {
            return search(node->left, key);
        } else if (key > node->key) {
            return search(node->right, key);
        } else {
            return node->values;
        }
    }
    Node* findMinValueNode(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
    Node* deleteNode(Node* node, int key, int value) {
        if (node == nullptr) {
            return nullptr;
        }
        if (key < node->key) {
            node->left = deleteNode(node->left, key, value);
        } else if (key > node->key) {
            node->right = deleteNode(node->right, key, value);
        } else {
            auto it = find(node->values.begin(), node->values.end(), value);
            if (it != node->values.end()) {
                node->values.erase(it);
            }
            if (node->values.empty()) {
                if (node->left == nullptr) {
                    Node* temp = node->right;
                    delete node;
                    return temp;
                } else if (node->right == nullptr) {
                    Node* temp = node->left;
                    delete node;
                    return temp;
                }
                Node* minValueNode = findMinValueNode(node->right);
                node->key = minValueNode->key;
                node->values = minValueNode->values;
                node->right = deleteNode(node->right, minValueNode->key, minValueNode->values[0]);
            }
        }
        return node;
    }
    void inOrderTraversal(Node* node) {
        if (node != nullptr) {
            inOrderTraversal(node->left);
            cout << "Key: " << node->key << ", Values: ";
            for (int value : node->values) {
                cout << value << " ";
            }
            cout << endl;
            inOrderTraversal(node->right);
        }
    }
    void preOrderTraversal(Node* node) {
        if (node != nullptr) {
            cout << "Key: " << node->key << ", Values: ";
            for (int value : node->values) {
                cout << value << " ";
            }
            cout << endl;
            preOrderTraversal(node->left);
            preOrderTraversal(node->right);
        }
    }
    void postOrderTraversal(Node* node) {
        if (node != nullptr) {
            postOrderTraversal(node->left);
            postOrderTraversal(node->right);
            cout << "Key: " << node->key << ", Values: ";
            for (int value : node->values) {
                cout << value << " ";
            }
            cout << endl;
        }
    }
public:
    BurstsortTree() : root(nullptr) {}
    void insert(int key, int value) {
        root = insert(root, key, value);
    }
    vector<int> search(int key) {
        return search(root, key);
    }
    void deleteNode(int key, int value) {
        root = deleteNode(root, key, value);
    }
    void inOrderTraversal() {
        inOrderTraversal(root);
    }
    void preOrderTraversal() {
        preOrderTraversal(root);
    }
    void postOrderTraversal() {
        postOrderTraversal(root);
    }
};
int main() {
    BurstsortTree bst;
    bst.insert(50, 5);
    bst.insert(30, 3);
    bst.insert(70, 7);
    bst.insert(20, 2);
    bst.insert(40, 4);
    bst.insert(60, 6);
    bst.insert(80, 8);
    cout << "In-order Traversal:\n";
    bst.inOrderTraversal();
    cout << "\nPre-order Traversal:\n";
    bst.preOrderTraversal();
    cout << "\nPost-order Traversal:\n";
    bst.postOrderTraversal();
    int searchKey = 40;
    vector<int> result = bst.search(searchKey);
    if (!result.empty()) {
        cout << "\nValues associated with key " << searchKey << ": ";
        for (int value : result) {
            cout << value << " ";
        }
        cout << endl;
    } else {
        cout << "\nKey " << searchKey << " not found.\n";
    }
    int deleteKey = 30, deleteValue = 3;
    cout << "\nDeleting key " << deleteKey << ", value " << deleteValue << ":\n";
    bst.deleteNode(deleteKey, deleteValue);
    cout << "\nIn-order Traversal after deletion:\n";
    bst.inOrderTraversal();
    cout << "\nPre-order Traversal after deletion:\n";
    bst.preOrderTraversal();
    cout << "\nPost-order Traversal after deletion:\n";
    bst.postOrderTraversal();
    return 0;
}
