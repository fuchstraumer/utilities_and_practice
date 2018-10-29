#pragma once
#ifndef FUCHSTRAUMER_LINKED_LIST_HPP
#define FUCHSTRAUMER_LINKED_LIST_HPP
#include <cstddef>
#include <iterator>
#include <type_traits>

template<typename T>
struct linked_list {
    static_assert(std::is_default_constructible_v<T>, "Type stored in linked list must be default constructible!");
private:

    struct node {
        node() noexcept = default;
        node(T val, node* n, node* p) : value(std::move(val)), next(n),
            prev(p) {}

        T value{};
        node* next{ nullptr };
        node* prev{ nullptr };
    };

    node* head{ nullptr };
    node* tail{ nullptr };

    template<bool CONST>
    struct list_iterator {
    private:
        friend class linked_list<T>;
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = std::conditional_t<CONST, const T, T>;
        using reference = value_type&;
        using pointer = value_type*;

        list_iterator() noexcept = default;
        list_iterator(node<T>* n) : _node(n) {}

    public:

        list_iterator& operator++() noexcept {
            _node = _node->next;
            return *this;
        }

        list_iterator operator++(int) noexcept {
            auto orig = _node;
            ++(*this);
            return orig;
        }

        list_iterator& operator--() noexcept {
            _node = _node->prev;
            return *this;
        }

        list_iterator& operator--(int) noexcept {
            auto orig = _node;
            --(*this);
            return orig;
        }

        list_iterator& operator+=(size_t dist) {
            for (size_t i = 0; i < dist; ++i) {
                _node = _node->next;
            }
            return *this;
        }

        list_iterator& operator-=(size_t dist) {
            for (size_t i = 0; i < dist; ++i) {
                _node = _node->prev;
            }
            return *this;
        }

        reference operator*() {
            return _node->value;
        }

        pointer operator->() {
            return &_node->value;
        }

        bool operator==(const list_iterator& other) const noexcept {
            return other->_node == _node;
        }

        bool operator!=(const list_iterator& other) const noexcept {
            return other->_node != _node;
        }

    private:
        node<T>* _node{ nullptr };
    };

public:

    using size_type = std::size_t;
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using iterator = list_iterator<false>;
    using const_iterator = list_iterator<true>;

    linked_list() noexcept = default;
    linked_list(T init_val) noexcept : head(new node<T>(init_val, nullptr, nullptr)) { tail = head; }

    ~linked_list() {
        clear();
    }

    void clear() {
        node<T>* ptr = head;
        while (ptr != nullptr) {
            head = ptr->next;
            delete ptr;
            ptr = head;
        }
    }

    size_t size() const noexcept {
        node<T>* ptr = head;
        size_t count{ 0 };
        while (ptr != nullptr) {
            ++count;
            ptr = ptr->next;
        }
        return count;
    }

    void insert_front(T value) {
        if (head != nullptr) {
            node<T>* new_node = new node<T>(value, head, nullptr);
            head = new_node;
            head->next->prev = head;
        }
        else {
            head = new node<T>(init_val, nullptr, nullptr);
            tail = head;
        }
    }

    void insert_back(T value) {
        if (tail != nullptr) {
            node<T>* new_node = new node<T>(value, nullptr, tail);
            tail = new_node;
            tail->prev->next = tail;
        }
        else {
            head = new node<T>(init_val, nullptr, nullptr);
            tail = head;
        }
    }

    void insert_after(iterator iter, T value) {
        node<T>* next = iter._node->next;
        node<T>* prev = iter._node;
        node<T>* new_node = new node<T>(value, next, prev);
        next->prev = new_node;
        prev->next = new_node;
    }

    void insert_before(iterator iter, T value) {
        node<T>* prev = iter._node->prev;
        node<T>* next = iter._node;
        node<T>* new_node = new node<T>(value, next, prev);
        // keeps iterators valid afaik?
        prev->next = new_node;
        next->prev = new_node;
    }

    void erase_back() {
        if (tail != head) {
            node<T>* new_tail = tail->prev;
            new_tail->next = nullptr;
            delete tail;
            tail = new_tail;
        }
        else {
            delete tail;
            tail = nullptr;
            head = nullptr;
        }
    }

    void erase_front() {
        if (tail != head) {
            node<T>* new_head = head->next;
            new_head->prev = nullptr;
            delete head;
            head = new_head;
        }
        else {
            delete head;
            head = nullptr;
            tail = nullptr;
        }
    }

    // have to do decent amounts of correction work, to avoid invalidating iterators
    void erase_after(iterator iter) {
        // don't want to access completely null data
        node<T>* iter_next = iter._node->next;
        if (iter_next == tail) {
            throw std::out_of_range("Can't erase beyond end of list!");
        }

        iter._node->next = iter_next->next;
        delete iter_next;

        // update prev pointer for next after iter
        if (iter._node->next != nullptr) {
            iter._node->next->prev = iter._node;
        }

    }

    void erase_before(iterator iter) {
        node<T>* iter_prev = iter._node->prev;
        if (iter_prev == head) {
            throw std::out_of_range("Can't erase before beginning of list!");
        }

        iter._node->prev = iter_prev->prev;
        delete iter_prev;

        if (iter._node->prev != nullptr) {
            iter._node->prev->next = iter._node;
        }
        
    }

    T& front() {
        return head->value;
    }

    const T& front() const noexcept {
        return head->value;
    }

    T& back() {
        return tail->value;
    }

    const T& back() const noexcept {
        return tail->value;
    }

    const_iterator cbegin() const noexcept {
        return const_iterator{ head };
    }
    
    const_iterator cend() const noexcept {
        return const_iterator{ node{ T(), nullptr, tail } };
    }

    const_iterator begin() const noexcept {
        return const_iterator{ head };
    }

    const_iterator end() const noexcept {
        return const_iterator{ node{ T(), nullptr, tail } };
    }

    iterator begin() noexcept {
        return iterator{ head };
    }

    iterator end() noexcept {
        return iterator{ node{ T(), nullptr, tail } };
    }

};

#endif //!FUCHSTRAUMER_LINKED_LIST_HPP
