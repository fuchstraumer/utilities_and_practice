#pragma once
#ifndef MULTIWAY_B_TREE_HPP
#define MULTIWAY_B_TREE_HPP
#include <array>
#include <memory>
#include <utility>
#include <type_traits>

template<typename T, size_t M = 512>
struct multiway_b_tree {
private:

    struct btree_node {
        constexpr btree_node() noexcept = default;
        constexpr btree_node(T&& val) noexcept;

        bool leaf{ true };
        size_t keyCount{ 0u };
        std::array<T, M - 1> keys;
        std::array<std::unique_ptr<btree_node>, M> children;
    };

public:

};

#endif //!MULTIWAY_B_TREE_HPP
