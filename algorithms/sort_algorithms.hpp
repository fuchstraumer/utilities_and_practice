#pragma once
#ifndef SORT_ALGORITHMS_HPP
#define SORT_ALGORITHMS_HPP
#include <cstddef>
#include <vector>
#include <functional>

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

template<typename T, typename Comp = std::less<T>>
void bubble_sort(T* data, const size_t len, Comp cmp) {
    bool cont = true;
    for (size_t i = 0; i < len - 1 && cont; ++i) {
        for (size_t j = len - 1, cont = false; j > i; --j) {
            if (cmp(data[j], data[j - 1])) {
                std::swap(data[j], data[j - 1]);
                cont = true;
            }
        }
    }
}



#endif //!SORT_ALGORITHMS_HPP
