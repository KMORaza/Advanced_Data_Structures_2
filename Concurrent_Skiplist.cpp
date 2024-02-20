#include <iostream>
#include <vector>
#include <random>
#include <thread>
#include <mutex>
#include <atomic>
const int MAX_LEVEL = 6;  
template <typename T>
struct Node {
    T key;
    std::vector<Node<T>*> next;
    std::mutex nodeMutex;
    Node(T k, int level) : key(k), next(level + 1) {}
};
template <typename T>
class ConcurrentSkipList {
public:
    ConcurrentSkipList() : head(new Node<T>(std::numeric_limits<T>::min(), MAX_LEVEL)) {}
    void insert(T key) {
        std::vector<Node<T>*> update(MAX_LEVEL + 1);
        Node<T>* current = head.load();
        for (int i = MAX_LEVEL; i >= 0; --i) {
            while (current->next[i] != nullptr && current->next[i]->key < key) {
                current = current->next[i];
            }
            update[i] = current;
        }
        int newLevel = randomLevel();
        Node<T>* newNode = new Node<T>(key, newLevel);
        for (int i = 0; i <= newLevel; ++i) {
            newNode->next[i] = update[i]->next[i];
            update[i]->next[i] = newNode;
        }
    }
    bool contains(T key) {
        Node<T>* current = head.load();
        for (int i = MAX_LEVEL; i >= 0; --i) {
            while (current->next[i] != nullptr && current->next[i]->key < key) {
                current = current->next[i];
            }
        }
        current = current->next[0];
        return current != nullptr && current->key == key;
    }
private:
    std::atomic<Node<T>*> head;
    int randomLevel() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_real_distribution<> dis(0, 1);
        int level = 0;
        while (dis(gen) < 0.5 && level < MAX_LEVEL) {
            ++level;
        }
        return level;
    }
};
int main() {
    ConcurrentSkipList<int> skipList;
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back([&skipList, i]() {
            skipList.insert(i);
        });
    }
    for (auto& thread : threads) {
        thread.join();
    }
    threads.clear();
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back([&skipList, i]() {
            bool found = skipList.contains(i);
            std::cout << "Element " << i << (found ? " found" : " not found") << std::endl;
        });
    }
    for (auto& thread : threads) {
        thread.join();
    }
    return 0;
}
