#pragma once
#ifndef SORT_ALGORITHMS_HPP
#define SORT_ALGORITHMS_HPP
#include <cstddef>
#include <vector>
#include <functional>
#include <limits>
#include <queue>

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

template<typename T, typename Iter, typename Comp = std::less<T>>
void quick_sort(Iter begin, Iter end, Comp cmp) {

    auto partition = [&Cmp](Iter lhs, Iter rhs)->Iter {
        Iter i = lhs - 1;
        Iter curr = lhs;

        while (curr < rhs) {
            if (Cmp(*curr, *rhs)) {
                std::iter_swap(curr, rhs);
                std::advance(i, 1);
            }
            std::advance(i, 1);
        }

        std::iter_swap((i + 1), rhs);
        std::advance(i, 1);
        return i;
    };

    if (std::distance(begin, end) >= 2) {
        Iter pivot = partition(begin, end);
        quick_sort(left, pivot - 1);
        quick_sort(pivot + 1, right);
    }

}

template<typename T, typename Iter, typename Comp = std::less<T>>
void radix_sort(Iter begin, Iter end, Comp cmp) {
    static_assert(std::is_integral_v<T>, "Value type for radix_sort must be an integral type!");
    constexpr static size_t DIGITS = std::numeric_limits<T>::digits;
    constexpr static size_t RADIX = 10u;
    std::array<std::queue<T>, RADIX> queues;

    for (size_t i = 0, size_t factor = 1u; i < DIGITS; factor *= RADIX, ++i) {
        for (Iter iter = begin; iter != end; ++iter) {
            const size_t idx = static_cast<size_t>((*iter / factor) % RADIX);
            queues[idx].push(*iter);
        }

        for (size_t j = 0u, Iter iter = begin; j < radix; ++j) {
            while (!queues[j].empty()) {
                
            }
            ++iter;
        }
    }
}

#endif //!SORT_ALGORITHMS_HPP
