#pragma once
#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP
#include <utility>
#include <memory>
#include <optional>
#include <queue>
#include <stack>

template<typename T>
struct bst_node {
    bst_node(T val, bst_node* p) : value{ std::move(val) }, parent{ p } {}
    ~bst_node() = default;
    T value;
    bool leaf() const noexcept {
        return (left.get() == nullptr) && (right.get() == nullptr);
    }
    std::unique_ptr<bst_node<T>> left{ nullptr };
    std::unique_ptr<bst_node<T>> right{ nullptr };
    const bst_node* parent{ nullptr };
};

template<typename T>
struct binary_search_tree {

    using value_return_type = std::conditional_t<std::is_pointer_v<T>, T, std::optional<T>>;

    binary_search_tree() : root{ nullptr } {}
    binary_search_tree(T val) : root{ std::make_unique<bst_node<T>>(std::move(val)) } {}

    bst_node<T>* insert(T val) {
        bst_node<T>* ptr = root.get();
        bst_node<T>* prev{ nullptr };

        while (ptr != nullptr) {
            prev = ptr;
            if (val < ptr->value) {
                ptr = ptr->left.get();
            }
            else {
                ptr = ptr->right.get();
            }
        }

        if (root.get() == nullptr) {
            root = std::make_unique<bst_node<T>>(std::move(val), nullptr);
            return root.get();
        }
        else if (val < prev->value) {
            prev->left = std::make_unique<bst_node<T>>(std::move(val), prev);
            return prev->left.get();
        }
        else {
            prev->right = std::make_unique<bst_node<T>>(std::move(val), prev);
            return prev->right.get();
        }
    }

    bool erase(const T& val) {
        // want a mutable pointer so we 
        bst_node<T>* ptr = root.get();
        auto found = search(ptr, val);
            // need to find a value to erase it
        if (found.has_value()) {

            if (ptr->leaf()) {
                // no children, erase it and move on
                delete_node(ptr);
                return true;
            }

            // release ownership of children, so they don't get erased
            // when parent node is erased
            bst_node<T>* deleted_left = ptr->left.release();
            bst_node<T>* deleted_right = ptr->right.release();
            const bst_node<T>* erased_parent = ptr->parent;

            delete_node(ptr);
            // now handle correcting the tree
            if ((deleted_left != nullptr) && (deleted_right != nullptr)) {
                // worst case
            }
            else if (deleted_left != nullptr) {
                assert(erased_parent->left.get() == nullptr);
                erased_parent->left = std::unique_ptr<bst_node<T>>{ deleted_left };
            }
            else if (deleted_right != nullptr) {
                assert(erased_parent->right.get() == nullptr);
                erased_parent->right = std::unique_ptr<bst_node<T>>{ deleted_right };
            }

            return true;

        }
        else {
            return false;
        }
    }

    value_return_type search(const T& val) {
        bst_node<T>* ptr = root.get();
        return search_impl(ptr, val);
    }    

    template<typename Func>
    void breadth_first_apply(Func&& fn) {
        std::queue<bst_node<T>*> queue;
        bst_node<T>* curr = root.get();

        if (curr != nullptr) {
            
            queue.push(curr);
            while (!queue.empty()) {
                curr = queue.front();
                queue.pop();
                fn(curr);
                if (curr->left != nullptr) {
                    queue.push(curr->left.get());
                }
                if (curr->right != nullptr) {
                    queue.push(curr->right.get());
                }
            }
        }
    }

    template<typename Func>
    void traverse_preorder(bst_node<T>* node, Func&& fn) {
        // Visit - Left - Right
        if (node != nullptr) {
            fn(node->value);
            traverse_preorder(node->left.get(), fn);
            traverse_preorder(node->right.get(), fn);
        }
    }

    template<typename Func>
    void traverse_inorder(bst_node<T>* node, Func&& fn) {
        // Left - Visit - Right
        if (node != nullptr) {
            traverse_inorder(node->left.get(), fn);
            fn(node->value);
            traverse_inorder(node->right.get(), fn);
        }
    }

    template<typename Func>
    void traverse_postorder(bst_node<T>* node, Func&& fn) {
        // Left - Right - Visit
        if (node != nullptr) {
            traverse_postorder(node->left.get(), fn);
            traverse_postorder(node->left.get(), fn);
            fn(node->value);
        }
    }

private:

    // node will eventually be the pointer for the entry nearest the value we want to find
    std::optional<T> search_impl(bst_node<T>* node, const T& val) const {
        while (node != nullptr) {
            if (val == node->value) {
                return node->value;
            }
            else if (val < node->value) {
                node = node->left.get();
            }
            else {
                node = node->right.get();
            }
        }

        if constexpr (std::is_pointer_v<T>) {
            return nullptr;
        }
        else {
            return std::optional<T>{};
        }
    }

    void delete_node(bst_node<T>* node) {
        const bst_node<T>* parent = node->parent;
        if (node == parent->left.get()) {
            parent->left.reset();
        }
        else {
            // double check addresses are correct, but only when already debugging
            assert(node == parent->right.get());
            parent->right.reset();
        }
    }

    std::unique_ptr<bst_node<T>> root{ nullptr };
};

#endif //!BINARY_SEARCH_TREE_HPP
