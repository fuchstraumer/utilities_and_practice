#pragma once
#ifndef CIRCULAR_BUFFER_HPP
#define CIRCULAR_BUFFER_HPP
#include <cstddef>
#include <memory>
#include <cstdlib>
#include <utility>
#include <cstring>

// conserving circular buffer. doesn't overwrite data
struct circular_buffer {

    circular_buffer(size_t capacity) : data(std::make_unique<std::byte[]>(capacity)), capacity{ capacity } { std::memset(data.get(), 0, capacity); }
    ~circular_buffer() noexcept = default;

    size_t enqueue(void* bytes, const size_t len) {

        if (len == 0) {
            return 0;
        }

        size_t to_write = std::min(capacity - used, len);
        // simplest case, single step write
        if (to_write <= capacity - tail) {
            std::memcpy(data.get() + tail, bytes, to_write);
            increment_tail(to_write);
            return to_write;
        }
        else {
            // copy into available space at tail
            size_t first_copy = capacity - tail;
            std::memcpy(data.get() + tail, bytes, first_copy);
            increment_tail(first_copy);
            used += first_copy;
            size_t remaining_write = to_write -first_copy;
            if (used != capacity && remaining_write != 0) {
                // can now copy into head region
                size_t second_copy = std::min(head, remaining_write);
                std::memcpy(data.get(), bytes + first_copy, second_copy);
                used += second_copy;
                increment_tail(second_copy);
                return first_copy + second_copy;
            }
            else {
                return first_copy;
            }
        }


    }

    bool full() {
        return used == capacity;
    }

    bool empty() {
        return used == 0;
    }

    void reset() {
        head = 0;
        tail = 0;
        used = 0;
        std::memset(data.get(), 0, capacity);
    }

    size_t dequeue(std::byte* dest, size_t len) {
        if (len == 0) {
            return 0;
        }

        size_t to_read = std::min(len, used);

    }

private:

    size_t nonconserving_enqueue(void* bytes, const size_t len) {

    }

    inline void increment_head(size_t amt) {
        head = (head + amt) % capacity;
    }

    inline void increment_tail(size_t amt) {
        tail = (tail + amt) % capacity;
    }

    size_t used{ 0 };
    size_t head{ 0 };
    size_t tail{ 0 };
    size_t capacity{ 0 };
    std::unique_ptr<std::byte[]> data;

};

#endif //!CIRCULAR_BUFFER_HPP
