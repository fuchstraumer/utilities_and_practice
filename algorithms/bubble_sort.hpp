#pragma once
#ifndef BUBBLE_SORT_HPP
#define BUBBLE_SORT_HPP
#include <functional>

template<typename T, typename Comp = std::less<T>>
void bubble_sort(T* data, const size_t len, Comp cmp) {
    
    for (size_t i = 0; i < len; ++i) {
        for (size_t j = len - 1; j > i; --j) {
            if (cmp(data[j], data[j - 1])) {
                std::swap(data[j], data[j - 1]);
            }
        }
    }

}

#endif //!BUBBLE_SORT_HPP
