#pragma once
#ifndef FUCHSTRAUMER_STACK_HPP
#define FUCHSTRAUMER_STACK_HPP
#include "linked_list.hpp"

template<typename T>
class stack {
public:

    stack() noexcept = default;

    void push(T val) {
        data.push_front(val);
    }

    void pop() {
        data.pop_front();
    }

    T& top() {
        return data.front();
    }

    const T& top() const {
        return data.front();
    }

    void clear() {
        data.clear();
    }

    bool empty() const noexcept {
        return data.empty();
    }

    size_t size() const noexcept {
        return data.size();
    }

private:
    linked_list<T> data;
};

#endif //!FUCHSTRAUMER_STACK_HPP
