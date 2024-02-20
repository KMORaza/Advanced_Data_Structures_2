#include <iostream>
#include <vector>
class MortonOrderTree {
private:
    struct Node {
        int key;
        Node(int k) : key(k) {}
    };
    std::vector<Node> tree;
    int getParentIndex(int index) {
        return (index - 1) / 2;
    }
    int getLeftChildIndex(int index) {
        return 2 * index + 1;
    }
    int getRightChildIndex(int index) {
        return 2 * index + 2;
    }
    void heapifyUp(int index) {
        while (index > 0) {
            int parentIndex = getParentIndex(index);
            if (tree[index].key < tree[parentIndex].key) {
                std::swap(tree[index], tree[parentIndex]);
                index = parentIndex;
            } else {
                break;
            }
        }
    }
    void heapifyDown(int index) {
        int minIndex = index;
        int leftChildIndex = getLeftChildIndex(index);
        int rightChildIndex = getRightChildIndex(index);
        if (leftChildIndex < tree.size() && tree[leftChildIndex].key < tree[minIndex].key) {
            minIndex = leftChildIndex;
        }
        if (rightChildIndex < tree.size() && tree[rightChildIndex].key < tree[minIndex].key) {
            minIndex = rightChildIndex;
        }
        if (index != minIndex) {
            std::swap(tree[index], tree[minIndex]);
            heapifyDown(minIndex);
        }
    }
public:
    MortonOrderTree() {}
    void insert(int key) {
        Node node(key);
        tree.push_back(node);
        heapifyUp(tree.size() - 1);
    }
    bool search(int key) {
        for (const auto& node : tree) {
            if (node.key == key) {
                return true;
            }
        }
        return false;
    }
    bool remove(int key) {
        for (size_t i = 0; i < tree.size(); ++i) {
            if (tree[i].key == key) {
                std::swap(tree[i], tree.back());
                tree.pop_back();
                heapifyDown(i);
                return true;
            }
        }
        return false;
    }
    void printTree() {
        for (const auto& node : tree) {
            std::cout << node.key << " ";
        }
        std::cout << std::endl;
    }
};
int main() {
    MortonOrderTree tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(8);
    tree.insert(1);
    tree.insert(7);
    std::cout << "Original Tree: ";
    tree.printTree();
    int searchKey = 3;
    if (tree.search(searchKey)) {
        std::cout << "Key " << searchKey << " found in the tree." << std::endl;
    } else {
        std::cout << "Key " << searchKey << " not found in the tree." << std::endl;
    }
    int removeKey = 8;
    if (tree.remove(removeKey)) {
        std::cout << "Key " << removeKey << " removed from the tree." << std::endl;
    } else {
        std::cout << "Key " << removeKey << " not found in the tree." << std::endl;
    }
    std::cout << "Updated Tree: ";
    tree.printTree();
    return 0;
}
