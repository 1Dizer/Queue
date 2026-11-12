#include <iostream>

template<typename T>
class Node {
public:
    T data;
    Node* next;

    Node(const T& val) : data(val), next(nullptr) {}
};

template<typename T>
class Queue {
private:
    Node<T>* front; 
    Node<T>* rear; 

public:
    Queue() : front(nullptr), rear(nullptr) {}

    
    void enqueue(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (isEmpty()) {
            front = rear = newNode;
        }
        else {
            rear->next = newNode;
            rear = newNode;
        }
        size++;
    }

    
    void dequeue() {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty");
        }
        Node<T>* temp = front;
        value = front->data;
        front = front->next;
        if (front == nullptr) { 
            rear = nullptr;
        }
        delete temp;
        size--;
    }

    
    T frontElement() const {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty");
        }
        return front->data;
    }

    
    size_t size() const {
        return size;
    }

    
    bool isEmpty() const {
        return size == 0;
    }
};