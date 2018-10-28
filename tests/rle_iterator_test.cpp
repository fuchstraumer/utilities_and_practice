#include "doctest.h"
#include "problems/rle_iterator.hpp"
#include <cassert>
#include <random>

TEST_CASE("rle_iterator_test") {

    static const std::vector<int> rle_test{ 5, 6, 7, 1, 3, 4, 5, 2, 1, 9, 3, 0, 2, 4 };
    assert(!(rle_test.size() & 1));
    static const int num_to_advance = 5 + 7 + 3 + 5 + 1 + 3 + 2;

    rle_iterator iter(rle_test);
    
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<int> dis(1, 6);

    int retrieved = 0;
    int counter = 0;
    while (retrieved != -1) {
        int this_advance = dis(gen);
        retrieved = iter.next(this_advance);
        if (retrieved != -1) {
            counter += this_advance;
        }
    }

    int remainder = counter % num_to_advance;
    CHECK((remainder < 6 && remainder >= 0));
    CHECK(iter.next(1) == -1);

}