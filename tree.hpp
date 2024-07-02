// ************************
// 326538022
// itay.alexandrov@gmail.com
// ************************
#ifndef TREE_HPP
#define TREE_HPP

#include "node.hpp"
#include <vector>
#include <queue>
#include <stack>
#include <iostream>
#include <algorithm>

template <typename T, size_t K = 2>
class Tree {
private:
    Node<T>* root;

    void pre_order_helper(Node<T>* node, std::vector<Node<T>*>& nodes) {
        if (node) {
            nodes.push_back(node);
            for (auto child : node->children) {
                pre_order_helper(child, nodes);
            }
        }
    }

    void post_order_helper(Node<T>* node, std::vector<Node<T>*>& nodes) {
        if (node) {
            for (auto child : node->children) {
                post_order_helper(child, nodes);
            }
            nodes.push_back(node);
        }
    }

    void in_order_helper(Node<T>* node, std::vector<Node<T>*>& nodes) {
        if (node) {
            if (!node->children.empty()) {
                in_order_helper(node->children[0], nodes);
            }
            nodes.push_back(node);
            for (size_t i = 1; i < node->children.size(); ++i) {
                in_order_helper(node->children[i], nodes);
            }
        }
    }

    void bfs_helper(Node<T>* node, std::vector<Node<T>*>& nodes) {
        if (node) {
            std::queue<Node<T>*> q;
            q.push(node);
            while (!q.empty()) {
                Node<T>* current = q.front();
                q.pop();
                nodes.push_back(current);
                for (auto child : current->children) {
                    q.push(child);
                }
            }
        }
    }

    void dfs_helper(Node<T>* node, std::vector<Node<T>*>& nodes) {
        if (node) {
            std::stack<Node<T>*> s;
            s.push(node);
            while (!s.empty()) {
                Node<T>* current = s.top();
                s.pop();
                nodes.push_back(current);
                for (auto it = current->children.rbegin(); it != current->children.rend(); ++it) {
                    s.push(*it);
                }
            }
        }
    }

    void delete_subtree(Node<T>* node) {
        if (node) {
            for (auto child : node->children) {
                delete_subtree(child);
            }
            delete node;
        }
    }

public:
    Tree() : root(nullptr) {}
    ~Tree() {
        delete_subtree(root);
    }

    void add_root(Node<T>& node) {
        root = &node;
    }

    void add_sub_node(Node<T>& parent, Node<T>& child) {
        if (parent.children.size() < K) {
            parent.children.push_back(&child);
        } else {
            throw std::out_of_range("Maximum children reached for this node");
        }
    }

    Node<T>* get_root() const {
        return root;
    }

    typename std::vector<Node<T>*>::iterator begin_pre_order() {
        std::vector<Node<T>*> nodes;
        pre_order_helper(root, nodes);
        return nodes.begin();
    }

    typename std::vector<Node<T>*>::iterator end_pre_order() {
        std::vector<Node<T>*> nodes;
        pre_order_helper(root, nodes);
        return nodes.end();
    }

    typename std::vector<Node<T>*>::iterator begin_post_order() {
        std::vector<Node<T>*> nodes;
        post_order_helper(root, nodes);
        return nodes.begin();
    }

    typename std::vector<Node<T>*>::iterator end_post_order() {
        std::vector<Node<T>*> nodes;
        post_order_helper(root, nodes);
        return nodes.end();
    }

    typename std::vector<Node<T>*>::iterator begin_in_order() {
        std::vector<Node<T>*> nodes;
        in_order_helper(root, nodes);
        return nodes.begin();
    }

    typename std::vector<Node<T>*>::iterator end_in_order() {
        std::vector<Node<T>*> nodes;
        in_order_helper(root, nodes);
        return nodes.end();
    }

    typename std::vector<Node<T>*>::iterator begin_bfs_scan() {
        std::vector<Node<T>*> nodes;
        bfs_helper(root, nodes);
        return nodes.begin();
    }

    typename std::vector<Node<T>*>::iterator end_bfs_scan() {
        std::vector<Node<T>*> nodes;
        bfs_helper(root, nodes);
        return nodes.end();
    }

    typename std::vector<Node<T>*>::iterator begin_dfs_scan() {
        std::vector<Node<T>*> nodes;
        dfs_helper(root, nodes);
        return nodes.begin();
    }

    typename std::vector<Node<T>*>::iterator end_dfs_scan() {
        std::vector<Node<T>*> nodes;
        dfs_helper(root, nodes);
        return nodes.end();
    }

    void myHeap() {
        if (!root) return;

        std::vector<Node<T>*> nodes;
        bfs_helper(root, nodes);

        auto cmp = [](Node<T>* left, Node<T>* right) {
            return left->value > right->value;
        };

        std::make_heap(nodes.begin(), nodes.end(), cmp);
        std::sort_heap(nodes.begin(), nodes.end(), cmp);

        root = nodes.front();
        std::queue<Node<T>*> q;
        q.push(root);

        size_t index = 1;
        while (!q.empty() && index < nodes.size()) {
            Node<T>* current = q.front();
            q.pop();
            current->children.clear();
            for (size_t i = 0; i < K && index < nodes.size(); ++i, ++index) {
                current->children.push_back(nodes[index]);
                q.push(nodes[index]);
            }
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Tree& tree) {
        if (!tree.root) return os;

        std::vector<Node<T>*> nodes;
        tree.bfs_helper(tree.root, nodes);

        for (const auto& node : nodes) {
            os << node->get_value() << " ";
        }
        return os;
    }
};

#endif // TREE_HPP
