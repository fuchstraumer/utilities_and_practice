#pragma once
#ifndef FREQUENCY_STACK_HPP
#define FREQUENCY_STACK_HPP
#include <unordered_map>
#include <stack>
#include <algorithm>

struct frequency_stack {

    frequency_stack() {}

    void push(int x) {
        maxFreq = std::max(++data[x], maxFreq);
        freqMap[data[x]].push(x);
    }

    int pop() {
        int result = freqMap[maxFreq].top();
        freqMap[maxFreq].pop();
        
        return result;
    }

private:
    std::unordered_map<int, size_t> data;
    std::unordered_map<size_t, std::stack<int>> freqMap;
    size_t maxFreq{0};
};

#endif //!FREQUENCY_STACK_HPP
