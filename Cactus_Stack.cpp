#include <iostream>
#include <vector>
class CactusStack {
private:
    std::vector<int> elements;
public:
    void push(int value) {
        elements.push_back(value);
    }
    int pop() {
        if (elements.empty()) {
            std::cerr << "Error: Stack is empty\n";
            return -1; 
        }
        int topElement = elements.back();
        elements.pop_back();
        return topElement;
    }
    int peek() const {
        if (elements.empty()) {
            std::cerr << "Error: Stack is empty\n";
            return -1; 
        }
        return elements.back();
    }
    void insertAtIndex(int index, int value) {
        if (index < 0 || index > elements.size()) {
            std::cerr << "Error: Invalid index\n";
            return; 
        }
        elements.insert(elements.begin() + index, value);
    }
    void deleteAtIndex(int index) {
        if (index < 0 || index >= elements.size()) {
            std::cerr << "Error: Invalid index\n";
            return; 
        }
        elements.erase(elements.begin() + index);
    }
    int getAtIndex(int index) const {
        if (index < 0 || index >= elements.size()) {
            std::cerr << "Error: Invalid index\n";
            return -1; 
        }
        return elements[index];
    }
    int getSize() const {
        return elements.size();
    }
    bool isEmpty() const {
        return elements.empty();
    }
    void clear() {
        elements.clear();
    }
    void display() const {
        std::cout << "Cactus Stack: ";
        for (int value : elements) {
            std::cout << value << " ";
        }
        std::cout << "\n";
    }
};
int main() {
    CactusStack cactusStack;
    cactusStack.push(10);
    cactusStack.push(20);
    cactusStack.push(30);
    cactusStack.display();
    cactusStack.insertAtIndex(1, 15);
    cactusStack.display();
    std::cout << "Element at index 2: " << cactusStack.getAtIndex(2) << "\n";
    cactusStack.deleteAtIndex(2);
    cactusStack.display();
    std::cout << "Stack size: " << cactusStack.getSize() << "\n";
    cactusStack.pop();
    cactusStack.display();
    cactusStack.clear();
    return 0;
}
