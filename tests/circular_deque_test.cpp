#include "doctest.h"
#include "objects/circular_deque.hpp"

TEST_CASE("circular_deque_test") {
    circular_deque<int> deque(3);
    CHECK(deque.insert_back(1));
    CHECK(deque.insert_back(2));
    CHECK(deque.insert_front(3));
    CHECK(!deque.insert_front(4));
    CHECK(deque.delete_back());
    CHECK(deque.insert_front(4));
    CHECK(deque.get_front() == 4);
}
