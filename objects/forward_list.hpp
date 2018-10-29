#pragma once
#ifndef FORWARD_LIST_HPP
#define FORWARD_LIST_HPP
#include <type_traits>
#include <utility>

template<typename T>
struct forward_list {
private:
    struct node {
        node() = default;
        node(T val, node* _N) : value(std::move(val)), next(_N) {}
        T value{};
        node* next{ nullptr };
    };

    node* head{ nullptr };
    node* tail{ nullptr };

public:

    static_assert(std::is_default_constructible_v<T>, "Type used in forward list must be default constructible.");
    static_assert(std::is_copy_constructible_v<T>, "Type used in forward list must be copy constructible");

    struct iterator {

    };

    forward_list() = default;

    ~forward_list() {
        for(node* ptr = nullptr; !empty();) {
            ptr = head->next;
            delete head;
            head = ptr;
        }
    }

    bool empty() const noexcept {
        return head == nullptr;
    }

    void insert_front(T val) {
        node* new_node = new node(std::move(val), head);
        head = new_node;
        if (tail == nullptr) {
            tail = head;
        }
    }

    void insert_back(T val) {
        node* new_node = new node(std::move(val), nullptr);
        tail->next = new_node;
        tail = new_node;
    }


};

#endif //!FORWARD_LIST_HPP
