#pragma once
#ifndef LRU_CACHE_HPP
#define LRU_CACHE_HPP
#include <cstddef>
#include <functional>
#include <optional>
#include <list>
#include <unordered_map>
#include <type_traits>

template<typename Key, typename Value, typename Hasher = std::hash<Key>, typename Equals = std::equal_to<Key>>
struct lru_cache {
private:
    using value_type = std::pair<Key, Value>;
    std::list<value_type> values;
    std::unordered_map<Key, typename decltype(values)::iterator, Hasher, Equals> lookup;
    size_t capacity;
    size_t numEntries;
    static_assert(std::is_trivially_constructible_v<Key>, "Key must be trivially constructible!");
public:

    lru_cache(size_t _capacity) : capacity{ _capacity }, numEntries{ 0 } { lookup.reserve(capacity); }

    using get_return_type = std::conditional_t<std::is_pointer_v<Value>, Value, std::optional<Value>>;

    get_return_type get(const Key& k) noexcept {
        if (auto iter = lookup.find(k); iter != std::end(lookup)) {
            touch(iter->second);
            return iter->second->second;
        }
        else {
            if constexpr (std::is_pointer_v<Value>) {
                return nullptr;
            }
            else {
                // return empty value
                return std::optional<Value>{};
            }
        }
    }

    void put(Key k, Value val) {
        values.emplace_front(k, std::move(val));
        lookup.emplace(k, values.begin());
        ++numEntries;

        if (numEntries > capacity) {
            lookup.erase(values.back().first);
            values.pop_back();
            --numEntries;
        }
    }

private:

    void touch(const typename decltype(values)::iterator k) {
        // iterator k is now up front.
        values.splice(values.begin(), values, k);
    }

};

#endif //!LRU_CACHE_HPP
