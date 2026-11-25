#include <cstddef>
#include <stdexcept>
#include <utility>

template <class T>
struct Node {
    T val;
    Node<T>* next;

    Node() : val(T()), next(nullptr) {}
    Node(const T& val) : val(val), next(nullptr) {}
};

template <class T>
class Queue {
public:
    Node<T>* head;
    Node<T>* tail;
    std::size_t count;

    Queue() : head(nullptr), tail(nullptr), count(0) {}

    Queue(const Queue<T>& other) : head(nullptr), tail(nullptr), count(0) {
        for (Node<T>* p = other.head; p; p = p->next)
            push(p->val);
    }

    Queue(Queue<T>&& other) noexcept
        : head(other.head), tail(other.tail), count(other.count) {
        other.head = other.tail = nullptr;
        other.count = 0;
    }

    Queue& operator=(const Queue<T>& other) {
        if (this != &other) {
            Queue<T> tmp(other);
            swap(tmp);
        }
        return *this;
    }

    Queue& operator=(Queue<T>&& other) noexcept {
        if (this != &other) {
            clear();
            head = other.head;
            tail = other.tail;
            count = other.count;
            other.head = other.tail = nullptr;
            other.count = 0;
        }
        return *this;
    }

    ~Queue() { clear(); }

    void push(const T& val) {
        Node<T>* n = new Node<T>(val);
        if (tail) 
            tail->next = n;
        else      
            head = n;
        tail = n;
        ++count;
    }

    void pop() {
        if (isEmpty()) throw std::out_of_range("Queue::pop: empty queue");
        Node<T>* tmp = head;
        head = head->next;
        if (!head) tail = nullptr;
        delete tmp;
        --count;
    }

    T& front() {
        if (isEmpty()) throw std::out_of_range("Queue::front: empty queue");
        return head->val;
    }
    const T& front() const {
        if (isEmpty()) throw std::out_of_range("Queue::front: empty queue");
        return head->val;
    }

    T& back() {
        if (isEmpty()) throw std::out_of_range("Queue::back: empty queue");
        return tail->val;
    }
    const T& back() const {
        if (isEmpty()) throw std::out_of_range("Queue::back: empty queue");
        return tail->val;
    }

    bool isEmpty() const { return head == nullptr; }
    std::size_t size() const { return count; }

private:
    void clear() {
        while (head) {
            Node<T>* tmp = head;
            head = head->next;
            delete tmp;
        }
        tail = nullptr;
        count = 0;
    }

    void swap(Queue<T>& other) noexcept {
        std::swap(head, other.head);
        std::swap(tail, other.tail);
        std::swap(count, other.count);
    }
};
