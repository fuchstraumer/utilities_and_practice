#include "doctest.h"
#include "objects/lru_cache.hpp"
#include <string>

TEST_SUITE_BEGIN("lru_cache");

TEST_CASE("functionality test") {
    lru_cache<int, std::string> cache(4);
    static const std::string test_strs[4] {
        "foo",
        "bar",
        "foobar",
        "foo_bar"
    };

    int i = 0;
    for (const auto& str : test_strs) {
        cache.put(i, str);
        ++i;
    }

    auto invalid_value = cache.get(10);
    CHECK(!invalid_value.has_value());
    auto valid_value = cache.get(0);
    CHECK(valid_value.has_value());

    // evict value
    cache.put(4, "evict_str");
    auto evicted_value = cache.get(1);
    CHECK(!evicted_value.has_value());
    
}

TEST_SUITE_END();