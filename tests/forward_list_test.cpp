#include "doctest.h"
#include "objects/forward_list.hpp"

TEST_CASE("forward_list_test") {
    forward_list<int> flist;
    flist.insert_front(1);
    flist.insert_front(3);
    flist.insert_back(4);
}
