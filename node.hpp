// ************************
// 326538022
// itay.alexandrov@gmail.com
// ************************
#ifndef NODE_HPP
#define NODE_HPP

#include <vector>

template <typename T>
class Node {
public:
    T value;
    std::vector<Node*> children;

    Node(T val) : value(val) {}
    T get_value() { return value; }
};

#endif // NODE_HPP
