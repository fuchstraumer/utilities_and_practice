#pragma once
#ifndef LFU_CACHE_HPP
#define LFU_CACHE_HPP
#include <cstddef>
#include <optional>
#include <type_traits>
#include <unordered_map>
#include <list>

// should be O(1) for both operations: but has high data overhead. depends on complexity of hash function for Key too (e.g, strings "bad"), 
// along with complexity of equality function for put(), as well. best we can do is create good infrastructure around this and make user aware.
template<typename Key, typename Value, size_t Capacity, typename Hasher = std::hash<Key>, typename Equality = std::equal_to<Key>>
struct lfu_cache {

    // Use std::optional, unless value is a pointer type. We can already check for nullability on 
    // pointers, and this way we can keep nullability checks for using get without implementing things
    // like error codes, fixed "invalid" return values, or doing things like throwing when we don't have 
    // a value for a key
    using return_type = std::conditional_t<std::is_pointer_v<Value>, Value, std::optional<Value>>;

    return_type get(const Key& k) noexcept {
        if (data.count(k) == 0) {
            if constexpr (std::is_pointer_v<Value>) {
                return nullptr;
            }
            else {
                return std::optional<Value>{};
            }
        }

        auto&[val, freq] = data.at(k);

        freqToKeyListMap[freq].erase()
    }

    void put(Key k, Value v);

private:

    // despite the name, the entries of this list are keys - just keys who have the same frequency
    // of access
    using frequency_list_type = std::list<size_t>;

    // value store - second element of tuple is use frequency
    std::unordered_map<Key, std::tuple<Value, size_t>, Hasher, Equality> data;
    // Iterator is entry in list in freqToKeyListMap that is for given key
    std::unordered_map<Key, frequency_list_type::iterator> keyToFreqListMap;
    // Key is frequency, list is all key/values that have that frequency too
    std::unordered_map<size_t, frequency_list_type> freqToKeyListMap;

    size_t size{ 0 };
    size_t minFrequency{ 0 };
};

#endif //!LFU_CACHE_HPP
