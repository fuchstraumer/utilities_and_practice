#pragma once
#ifndef FORWARD_LIST_HPP
#define FORWARD_LIST_HPP
#include <type_traits>
#include <utility>
#include <iterator>

template<typename T>
struct forward_list {
private:

    struct node {
        node() = default;
        node(T&& val, node* _N) : value(std::forward<T>(val)), next(_N) {}
        T value{};
        node* next{ nullptr };
    };

    node* head{ nullptr };
    node* tail{ nullptr };

    template<bool CONST>
    struct _iterator {
        friend class forward_list<T>;

        _iterator() noexcept = default;
        _iterator(const _iterator&) = default;
        _iterator& operator=(const _iterator&) = default;
        _iterator(node* p) : ptr(p) {}

        using value_type = std::conditional_t<CONST, const T, T>;
        using pointer = value_type*;
        using reference = value_type&;
        using iterator_category = std::forward_iterator_tag;

        _iterator& operator++() noexcept {
            ptr = ptr->next;
            return *this;
        }

        _iterator operator++(int) noexcept {
            _iterator orig = *this;
            ++(*this);
            return orig;
        }

        bool operator==(const _iterator& other) const noexcept {
            return other.ptr == ptr;
        }

        bool operator!=(const _iterator& other) const noexcept {
            return other.ptr != ptr;
        }

        pointer operator->() const noexcept {
            return &ptr->value;
        }

        reference operator*() const noexcept {
            return ptr->value;
        }

    private:
        node* ptr{ nullptr };
    };

public:

    static_assert(std::is_default_constructible_v<T>, "Type used in forward list must be default constructible.");
    static_assert(std::is_copy_constructible_v<T>, "Type used in forward list must be copy constructible");

    using iterator = _iterator<false>;
    using const_iterator = _iterator<true>;

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

    void insert_front(T&& val) {
        node* new_node = new node(std::forward<T>(val), head);
        head = new_node;
        if (tail == nullptr) {
            tail = head;
        }
    }

    void insert_back(T&& val) {
        if (tail == nullptr) {
            head = new node(std::forward<T>(val), nullptr);
            tail = head;
            return;
        }
        node* new_node = new node(std::forward<T>(val), nullptr);
        tail->next = new_node;
        tail = new_node;
    }

    T erase_front() {
        node* tmp = head;
        if (head == tail) {
            head = nullptr;
            tail = nullptr;
        }
        else {
            head = head->next;
        }
        T result = tmp->value;
        delete tmp;
        return result;
    }

    T erase_back() {
        T result = tail->value;
        if (head == tail) {
            delete head;
            tail = nullptr;
            head = nullptr;
        }
        else {
            node* tmp{ nullptr };
            for (tmp = head; tmp->next != tail; tmp = tmp->next);
            delete tail;
            tail = tmp;
            tail->next = nullptr;
        }
        return result;
    }

    void erase_entry(const T& val) {
        node* ptr{ head };
        while (ptr != tail) {

            if (ptr->value == val) {

            }

            
        }
    }

    const_iterator cbegin() const noexcept {
        return const_iterator{ head };
    }

    const_iterator cend() const noexcept {
        return const_iterator{ nullptr };
    }

    const_iterator begin() const noexcept {
        return const_iterator{ head };
    }

    const_iterator end() const noexcept {
        return const_iterator{ nullptr };
    }

    iterator begin() noexcept {
        return iterator{ head };
    }

    iterator end() noexcept {
        return iterator{ nullptr };
    }

};

#endif //!FORWARD_LIST_HPP
