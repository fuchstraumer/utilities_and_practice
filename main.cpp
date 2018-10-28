#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

int main(int argc, char* argv[]) {
    doctest::Context ctxt;
    ctxt.setOption("abort-after", 1);
    ctxt.applyCommandLine(argc, argv);
    int result = ctxt.run();
    return result;
}
