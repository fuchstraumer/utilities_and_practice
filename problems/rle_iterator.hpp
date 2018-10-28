#pragma once
#ifndef RLE_ITERATOR_HPP
#define RLE_ITERATOR_HPP
#include <vector>
#include <queue>
#include <tuple>

/*
    https://leetcode.com/problems/rle-iterator/
*/

struct rle_iterator {

    rle_iterator(std::vector<int> _data) {

        for (size_t i = 0; i < _data.size(); i += 2) {
            if (_data[i] == 0) {
                continue;
            }
            data.emplace(_data[i], _data[i + 1]);
        }

    }

    int next(int n) {
        if (data.empty()) {
            return -1;
        }
        
        auto& tuple = data.front();
        auto& count = std::get<0>(tuple);
        auto& value = std::get<1>(tuple);
        int remainder = n - count;
        count -= n;
        
        if (count < 0) {
            data.pop();
            return next(remainder);
        }
        else {
            return value;
        }
    }

private:
    std::queue<std::tuple<int, int>> data;
};

#endif //!RLE_ITERATOR_HPP
