#pragma once
#ifndef MULTIWAY_B_TREE_HPP
#define MULTIWAY_B_TREE_HPP
#include <array>
#include <memory>
#include <limits>
#include <iostream>
#include <fstream>

template<typename Key, typename Value, size_t M>
struct DiskResidentBTree;

namespace detail {

    /*
        Based on: https://codereview.stackexchange.com/questions/197844/b-tree-implementation-in-secondary-memory-disk-memory

    */

    template<typename Key, typename Value>
    struct btElem {
        Key key;
        Value value;
    };

    template<typename Key, typename Value, size_t M>
    struct btNode {
        bool leaf{ true };
        static_assert((M < std::numeric_limits<uint16_t>::max()), "Max order M has to be less than the max of uint16_t");
        uint16_t numKeys;
        size_t fileLoc;
        std::array<btNode, M> data;
        // entries are indices of children (used to get file offset)
        std::array<size_t, M> children;
    private:
        constexpr btNode() noexcept {
            children.fill(std::numeric_limits<size_t>::max());
        }
        friend class DiskResidentBTree<Key,Value,M>;
    };

    template<typename Key, typename Value, size_t M>
    constexpr static size_t BT_NODE_SIZE = sizeof(btNode<Key,Value,M>);

    template<typename Key, typename Value, size_t M>
    btNode<Key,Value,M> btReadNodeFromDisk(size_t idx, std::fstream& file) {

        const size_t file_offset = BT_NODE_SIZE<Key,Value,M> * idx;
        file.seekg(file_offset);

        btNode result;
        file.read((char*)&result.leaf, sizeof(btNode::leaf));
        file.read((char*)&result.numKeys, sizeof(btNode::numKeys));
        file.read((char*)&result.fileLoc, sizeof(btNode::fileLoc));
        file.read((char*)&result.data, sizeof(btNode::data));
        file.read((char*)&result.children, sizeof(btNode::children));

        return result;
    }

    template<typename Key, typename Value, size_t M>
    void btWriteNodeToDisk(btNode<Key,Value,M>& node, std::fstream& file) {

        const size_t offset = BT_NODE_SIZE<Key,Value,M> * node.fileLoc;
        file.seekg(offset);

        file.write((char*)&node.leaf, sizeof(decltype(node)::leaf));
        file.write((char*)&node.numKeys, sizeof(decltype(node)::numKeys));
        file.write((char*)&node.fileLoc, sizeof(decltype(node)::fileLoc));
        file.write((char*)&node.data, sizeof(decltype(node)::data));
        file.write((char*)&node.children, sizeof(decltype(node)::children));

    }

}

template<typename Key, typename Value, size_t M = 256>
struct DiskResidentBTree {
private:
    detail::btNode<Key, Value, M> root;
    size_t totalNodeCount{ 0u };

    btNode createNewNode() {
        ++totalNodeCount;
        return btNode();
    }

    void btSplitChild(decltype(root)& node, size_t pos, std::fstream& file) {

        // child for current pos
        btNode<Key, Value, M> child0 = detail::btReadNodeFromDisk(node.children[pos], file);
        // splitting root
        if (&node == &root) {
            ++totalNodeCount;
            child.fileLoc = totalNodeCount;
        }

        // child for pos + 1
        auto child1 = createNewNode();
        child1.fileLoc = totalNodeCount;
        
        constexpr static auto MIN_DEGREE = M / 2;
        child1.numKeys = MIN_DEGREE;

        for (size_t i = 0; i <= MIN_DEGREE && (i + MIN_DEGREE + 1) <= child0.numKeys - 1; ++i) {
            child1.data[i] = std::move(child0.data[i + MIN_DEGREE + 1]);
        }

        if (!child0.leaf) {
            for (size_t i = 0; i <= MIN_DEGREE; ++i) {
                // child0 will have an invalid value at the given position now
                std::swap(child1.children[i], child0.children[i + MIN_DEGREE + 1]);
            }
        }

        child0.numKeys = MIN_DEGREE;

        if (&node == &root) {
            node.children[pos] =  child0.fileLoc;
            node.children[pos + 1] = child1.fileLoc;
        }
        else {

            size_t r{0u};
            for (size_t j = 0u; j < M; ++j) {
                if (node.children[j] == child0.fileLoc) {
                    for (size_t i = j + 1u; i < M; i += 2u) {
                        if (i + 1u < M) {
                            node.children[i + 1] = node.children[i];
                        } 
                    }
                    r = j;
                }
            }

            node.children[r + 1] = child1.fileLoc;
        }

        for (size_t j = pos; j < MIN_DEGREE - 2u; j += 2u) {
            node.data[j + 1] = node.data[j];
        }

        node.data[pos] = child0.data[MIN_DEGREE];
        child0.data[MIN_DEGREE].key = Key(-1);
        node.numKeys++;

        detail::btWriteNodeToDisk(node, file);
        detail::btWriteNodeToDisk(child0, file);
        detail::btWriteNodeToDisk(child1, file);
        
    }

public:

    
};

#endif //!MULTIWAY_B_TREE_HPP
