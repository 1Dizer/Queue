#include "queue.h"
#include <string>

template struct Node<int>;
template struct Node<double>;
template struct Node<std::string>;

template class Queue<int>;
template class Queue<double>;
template class Queue<std::string>;