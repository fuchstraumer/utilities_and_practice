#pragma once
#ifndef BST_CODEC_HPP
#define BST_CODEC_HPP
#include <cstddef>
#include "binary_search_tree.hpp"
#include <string>

struct bst_codec_node {
    int value{ -1 };
    size_t left_node_offset{ 0 };
    size_t right_node_offset{ 0 };
    bool operator==(const bst_codec_node& node) const noexcept {
        return (value == node.value) && (left_node_offset == node.left_node_offset) &&
            (right_node_offset == node.right_node_offset);
    }
};

struct bst_encoder {

    static std::string encode_bst(const binary_search_tree<int>& tree) {
        std::string result;

        auto encode_fn = [&result](bst_node<int>* ptr) {
            
        };
    }
};

#endif //!BST_CODEC_HPP
