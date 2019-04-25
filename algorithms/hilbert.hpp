#pragma once
#ifndef HILBERT_CURVE_UTILITIES_HPP
#define HILBERT_CURVE_UTILITIES_HPP
#include <limits>
#include <type_traits>
#include <cstdint>
#include <cstddef>

namespace detail {

    template<typename T>
    constexpr static T ones(T k) {
        return (T(2) << (k - 1)) - 1;
    }

    template<typename T>
    constexpr static T read_bit(T w, T k) {
        return (w >> k) & 1;
    }

    template<typename T>
    constexpr static T rotate_right(T arg, T n_rots, T n_dims) {
        return ((arg >> n_rots) | (arg << (n_dims - n_rots))) & ones<T>(n_dims);
    }

    template<typename T>
    constexpr static T rotate_left(T arg, T n_rots, T n_dims) {
        return ((arg << n_rots) | (arg >> (n_dims - n_rots))) & ones<T>(n_dims);
    }

    template<typename T>
    constexpr static void adjust_rotation(T rotation, T nDims, T bits) {
        static_assert(std::is_integral_v<T>, "non-integral type used in adjust_rotation");
        
    }

}

// N_BITS: bits per dimension
template<typename T, size_t DIMS, size_t N_BITS = std::numeric_limits<T>::digits / DIMS>
void hilbert_index_to_coords(T index, T coords[DIMS]) {
    constexpr auto NB_ONES = detail::ones<T>(N_BITS);

}



#endif //!HILBERT_CURVE_UTILITIES_HPP
