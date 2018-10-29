#pragma once
#ifndef CIRCULAR_DEQUE_HPP
#define CIRCULAR_DEQUE_HPP
#include <cstddef>
#include <memory>
#include <type_traits>

template<typename T>
struct circular_deque {

    static_assert(std::is_default_constructible_v<T>, "Elements of circular_deque must be default constructible.");

    circular_deque(size_t capacity) : data(std::make_unique<T[]>(capacity)), capacity(capacity), head(capacity - 1) {}

    bool insert_front(T elem) {
        if (used != capacity) {
            data[head] = elem;
            head = (--head + capacity) % capacity;
            ++used;
            return true;
        }
        else {
            return false;
        }
    }

    bool insert_back(T elem) {
        if (used != capacity) {
            data[tail] = elem;
            tail = ++tail % capacity;
            ++used;
            return true;
        }
        else {
            return false;
        }
    }

    bool delete_front() {
        if (used == 0) {
            return false;
        }
        head = ++head % capacity;
        --used;
        return true;
    }

    bool delete_back() {
        if (used == 0) {
            return false;
        }
        tail = (--tail + capacity) % capacity;
        --used;
        return true;
    }

    int get_front() {
        if (used == 0) {
            return -1;
        }
        return data[(head + 1) % capacity];
    }

    int get_back() {
        if (used == 0) {
            return -1;
        }
        return data[(tail - 1 + capacity) % capacity];
    }

private:
    int head{ 0 };
    int tail{ 0 };
    int used{ 0 };
    int capacity{ 0 };
    std::unique_ptr<T[]> data{ nullptr };
};

#endif //!CIRCULAR_DEQUE_HPP
