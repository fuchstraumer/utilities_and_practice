#pragma once
#ifndef TYPED_CIRCULAR_BUFFER_HPP
#define TYPED_CIRCULAR_BUFFER_HPP
#include <cstddef>
#include <memory>
#include <cstdlib>
#include <type_traits>

template<typename T>
struct typed_circular_buffer {

    // required, or compiliation will fail as constructor will be invalid.
    // pop() would also break, in cases where the container is empty
    static_assert(std::is_default_constructible_v<T>, "Type in circular buffer must be default constructible!");

    typed_circular_buffer(size_t _capacity) : capacity(std::move(_capacity)), data(std::make_unique<T[]>(capacity)) {}

    void push(T elem) {
        if (used != capacity) {
            data[tail] = elem;
            tail = ++tail % capacity;
            ++used;
        }
    }

    template<typename...Args>
    void emplace(Args&&...args) {
        // perfect forward construction in-place
    }

    T pop() {
        if (used == 0) {
            return T();
        }

        T result = data[head];
        head = ++head % capacity;
        --used;
        return result;
    }

private:


    size_t head{ 0 };
    size_t tail{ 0 };
    size_t used{ 0 };
    size_t capacity{ 0 };
    std::unique_ptr<T[]> data;
};

#endif //!TYPED_CIRCULAR_BUFFER_HPP
