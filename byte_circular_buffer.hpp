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

    size_t enqueue(void* bytes, size_t len) {

        if (len == 0) {
            return 0;
        }

        size_t to_write = std::min(capacity - used, len);
        // simplest case, single step write
        if (to_write <= capacity - tail) {
            std::memcpy(data.get() + tail, bytes, to_write);
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

    size_t dequeue(std::byte* dest, size_t len) {
        // wraparound occurs when tail < head
        if (tail < head) {
            size_t avail_copy = capacity - head;
            size_t to_copy = avail_copy <= len ? avail_copy : len;
            std::memcpy(static_cast<std::byte*>(dest), data.get() + head, to_copy);
            increment_head(avail_copy);
            used -= to_copy;

            if (tail != head ) {


            }
        }
        else {
            if (used < len) {
                std::memcpy(static_cast<std::byte*>(dest), data.get() + head, used);
                used = 0;
                increment_head(used);
                return used;
            }
            else {
                std::memcpy(static_cast<std::byte*>(dest), data.get() + head, len);
                increment_head(len);
                used -= len;
                return len;
            }
        }
    }

private:

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
