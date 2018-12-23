#pragma once
#ifndef FUCHS_TEXT_TRIE_OBJECT_HPP
#define FUCHS_TEXT_TRIE_OBJECT_HPP
#include <array>
#include <memory>
#include <string_view>
#include <unordered_map>

struct text_trie {
private:

    struct trie_node {
        trie_node() noexcept;
        ~trie_node();
        bool end_of_word() const noexcept {
            return children.empty();
        }
        std::unordered_map<char, std::unique_ptr<trie_node>> children;
    };

public:

    text_trie() noexcept;

    template<typename Iter>
    text_trie(Iter begin, Iter end);

    void insert(const std::string& str) {
        std::string_view str_view{ str };

        trie_node* node = &root;

        while (!str_view.empty()) {
            if (node->children.count(str_view.front()) == 0) {
                auto iter = node->children.emplace(str_view.front(), std::make_unique<trie_node>());
                node = (iter.first->second).get();
            }
            else {
                node = node->children.at(str.front()).get();
            }
            str_view.remove_prefix(1u);
        }

    }

private:

    trie_node root;

};

text_trie::trie_node::trie_node() noexcept {}

text_trie::trie_node::~trie_node() noexcept {}

text_trie::text_trie() noexcept {}

#endif //!FUCHS_TEXT_TRIE_OBJECT_HPP
