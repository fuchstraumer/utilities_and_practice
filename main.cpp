#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

#include "problems/stack_exercises.hpp"

int main(int argc, char* argv[]) {

    reverse_stack_test(5);
    reverse_stack_recursive(5);

    doctest::Context ctxt;
    ctxt.setOption("abort-after", 1);
    ctxt.applyCommandLine(argc, argv);
    int result = ctxt.run();
    return result;
}
