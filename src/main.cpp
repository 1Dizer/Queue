#include "queue.h"
#include <iostream>
#include <string>

int main() {
    Queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);

    std::cout << "front=" << q.front() << " back=" << q.back()
        << " size=" << q.size() << "\n";

    q.pop();
    std::cout << "pop: front=" << q.front()
        << " size=" << q.size() << "\n";

    Queue<std::string> s;
    s.push("one");
    s.push("two");
    s.push("three");
    std::cout << s.front() << " " << s.back() << "\n";

    return 0;
}