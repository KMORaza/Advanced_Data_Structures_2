#include <iostream>
struct Node {
    int x, y;
    Node* left;
    Node* right;
    Node(int x, int y) : x(x), y(y), left(nullptr), right(nullptr) {}
};
Node* insert(Node* root, int x, int y) {
    if (root == nullptr) {
        return new Node(x, y);
    }
    if (x < root->x) {
        root->left = insert(root->left, x, y);
    } else {
        root->right = insert(root->right, x, y);
    }
    return root;
}
bool query(Node* root, int x, int y) {
    if (root == nullptr) {
        return false; 
    }
    if (x == root->x && y == root->y) {
        return true;
    } else if (x < root->x) {
        return query(root->left, x, y);
    } else {
        return query(root->right, x, y);
    }
}
int main() {
    Node* root = nullptr;
    root = insert(root, 1, 1);
    root = insert(root, 2, 2);
    root = insert(root, 3, 3);
    std::cout << "Point (2,2) exists: " << (query(root, 2, 2) ? "Exist" : "Doesn't Exist") << std::endl;
    std::cout << "Point (4,4) exists: " << (query(root, 4, 4) ? "Exist" : "Doesn't Exist") << std::endl;
    return 0;
}
