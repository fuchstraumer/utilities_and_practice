#pragma once
#ifndef MULTIWAY_B_TREE_HPP
#define MULTIWAY_B_TREE_HPP
#include <array>
#include <memory>
#include <utility>
#include <type_traits>

template<typename T, size_t M>
struct multiway_b_tree;

namespace detail {

    template<typename T, size_t M>
    struct btree_node {
        constexpr btree_node() noexcept = default;
        constexpr btree_node(T&& val) noexcept;

        bool leaf{ true };
        size_t keyCount{ 0u };
        std::array<T, M - 1> keys;
        std::array<std::unique_ptr<btree_node>, M> children;
        friend class multiway_b_tree<T, M>;
    };

}

template<typename T, size_t M = 512>
struct multiway_b_tree {
private:
    std::unique_ptr<detail::btree_node<T, M>> root;
public:

    
};

#endif //!MULTIWAY_B_TREE_HPP
