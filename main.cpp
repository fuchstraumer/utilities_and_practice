#include "sort_algorithms.hpp"
#include "binary_search_tree.hpp"
#include "lfu_cache.hpp"
#include <iostream>
#include <string>
#include <cassert>
#include <array>
#include <string>

const static std::vector<int> sort_array{ 4, 3, 2, 10, 12, 1, 5, 6 };

template struct std::unique_ptr<bst_node<int>>;

int main(int argc, char* argv[]) {
    std::cerr << "Begin test.\n";

    auto array_copy = sort_array;

    //selection_sort(array_copy, std::less());

    binary_search_tree<int> tree;

    for (auto val : sort_array) {
        tree.insert(val);
    }

    tree.breadth_first_apply([](bst_node<int>* val){ 
        std::cerr << val->value << " ";
    });

    lfu_cache<int, std::string, 4> cache;
    auto retrieved = cache.get(1);

    return 0;
}
