#pragma once
#ifndef BYTE_CIRCULAR_BUFFER_HPP
#define BYTE_CIRCULAR_BUFFER_HPP
#include <cstddef>
#include <memory>
#include <cstdlib>
#include <utility>
#include <cstring>

// conserving circular buffer. doesn't overwrite data
struct byte_circular_buffer {

    byte_circular_buffer(size_t capacity) : data(std::make_unique<std::byte[]>(capacity)), capacity(capacity) { 
        // could get rid of this. not necessary.
        std::memset(data.get(), 0, capacity); 
    }

    byte_circular_buffer(byte_circular_buffer&& other) noexcept : data(std::move(other.data)), capacity(std::move(other.capacity)), head(std::move(other.head)),
        tail(std::move(other.tail)), used(std::move(other.used)) {}

    byte_circular_buffer& operator=(byte_circular_buffer&& other) noexcept {
        data = std::move(other.data);
        capacity = std::move(other.capacity);
        head = std::move(other.head);
        tail = std::move(other.tail);
        used = std::move(other.used);
        return *this;
    }

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
    }

    size_t dequeue(std::byte* dest, size_t len) {
        // early exit for empty buffer to reduce complexity later
        if (len == 0 || used == 0) {
            return 0;
        }

        size_t to_read = std::min(len, used);
        // since we check for used earlier, we can only
        // satisfy == when buffer has content
        if (to_read <= capacity - head) {
            // single read 
            std::memcpy(dest, data.get() + head, to_read);
            used -= to_read;
            return to_read;
        } 
        else {
            // two-step read: gotta handle wraparound
            size_t first_read = capacity - head;
            std::memcpy(dest, data.get() + head, first_read);
            used -= first_read;
            size_t second_read = to_read - first_read;
            std::memcpy(dest + first_read, data.get(), second_read);
            used -= second_read; 
        }

        increment_head(to_read);
        return to_read;
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

#endif //!BYTE_CIRCULAR_BUFFER_HPP
