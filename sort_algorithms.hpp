#pragma once
#ifndef SORT_ALGORITHMS_HPP
#define SORT_ALGORITHMS_HPP
#include <cstddef>
#include <vector>

template<typename T, typename Func>
void insertion_sort(std::vector<T>& array, Func&& fn) {
    for (size_t i = 1; i < array.size(); ++i) {
        for (size_t j = i; j > 0 && fn(array[j - 1], array[j]); j--) {
            std::swap(array[j], array[j - 1]);
        }
    }
}

template<typename T, typename Func>
void selection_sort(std::vector<T>& array, Func&& fn) {
    for (size_t i = 0; i < array.size() - 1; ++i) {
        size_t least = i; 
        for (size_t j = i + 1; j < array.size(); ++j) {
            if (fn(array[j], array[least])) {
                least = j;
            }
            if (i != least) {
                std::swap(array[least], array[i]);
            }
        }
    }
}

#endif //!SORT_ALGORITHMS_HPP
