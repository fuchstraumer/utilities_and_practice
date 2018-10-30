#pragma once
#ifndef STACK_PRACTICE_EXERCISES_HPP
#define STACK_PRACTICE_EXERCISES_HPP
#include <stack>
#include <queue>
#include <random>
#include <algorithm>


std::stack<int> generate_stack(const size_t num_elems) {

    std::stack<int> result;

    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<int> dis(1, 6);
    for (size_t i = 0; i < num_elems; ++i) {
        result.push(dis(gen));
    }
    
    return result;
}

void reverse_stack_test(const size_t num_elems) {
    auto starting_stack = generate_stack(num_elems);
    auto stack_copy = starting_stack;
    std::stack<int> reversed_stack;
    while (!starting_stack.empty()) {
        reversed_stack.push(starting_stack.top());
        starting_stack.pop();
    }
}

inline void reverse_step(std::stack<int>& st) {
    if (!st.empty()) {
        int elem = st.top();
        st.pop();
        reverse_step(st);
        st.push(elem);
    }
    else {
        return;
    }
}

void reverse_stack_recursive(const size_t num_elems) {
    auto stack = generate_stack(num_elems);
    auto orig = stack;

    int target = stack.top();
    stack.pop();
    reverse_step(stack);
    stack.push(target);
    
}

#endif //!STACK_PRACTICE_EXERCISES_HPP
