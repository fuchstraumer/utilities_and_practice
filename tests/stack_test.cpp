#include <doctest.h>
#include "objects/stack.hpp"
#include <string>
#include <string_view>
#include <unordered_map>

TEST_SUITE_BEGIN("Stack Testing");

TEST_CASE("Stack Baseline Tests") {
    stack<int> test_stack;
    CHECK(test_stack.empty());
    for (int i = 0; i < 5; ++i) {
        test_stack.push(i);
    }

    for(int i = 4; i >= 0; --i) {
        CHECK(test_stack.top() == i);
        test_stack.pop();
    }

    CHECK(test_stack.empty());

}

TEST_CASE("Stack Delimiter Matching Test") {
    static const std::string test_str{
        "if (y == 5 || (x % 2 == 0)) { v = (y + (x + 2); }"
    };
    std::string_view test_str_view(test_str);
    stack<char> char_stack;
    static const std::unordered_map<char, char> delim_inverse{
        { ')', '(' },
        { '}', '{' },
        { ']', '[' }
    };

    while (!test_str_view.empty()) {
        char current_ch = test_str_view[0];
        if (current_ch == '(' || current_ch == '{' || current_ch == '[') {
            char_stack.push(current_ch);
        }
        else if (current_ch == ')' || current_ch == '}' || current_ch == ']') {
            if (delim_inverse.at(current_ch) != char_stack.top()) {
                // should fail at this point
                CHECK(current_ch == '}');
            }
            else {
                char_stack.pop();
            }
        }

        test_str_view = test_str_view.substr(1, test_str_view.size());
    }
}

TEST_SUITE_END();
