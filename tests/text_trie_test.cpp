#include "doctest.h"
#include "objects/text_trie.hpp"

TEST_CASE("text_trie_test") {
    text_trie trie;
    trie.insert("hello");
    trie.insert("heck");
}
