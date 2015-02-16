#ifndef OPETREE_H_
#define OPETREE_H_

#include "tree/ScapegoatTree.h"
#include <limits>
#include <random>

typedef unsigned __int128 uint128_t;

static inline 
uint128_t random128(std::default_random_engine& engine)
{
    uint128_t x0 = engine();
    uint128_t x1 = engine();
    uint128_t x2 = engine();
    uint128_t x3 = engine();
    return x0 | (x1 << 32) | (x2 << 64) | (x3 << 96);
}

// TODO: Not exactly uniformed dist
static inline 
uint128_t random_bound(std::default_random_engine& engine, const uint128_t& low, const uint128_t& high)
{
    return (random128(engine) % (high - low + 1)) + low;
}

template <class Node, class EncType>
class OPETree : public ods::ScapegoatTree<Node, EncType> {
protected:
    using ods::BinaryTree<Node>::nil;
    using ods::BinaryTree<Node>::r;

    std::default_random_engine generator;

    uint128_t max_ciphertext_less_equal_than(const EncType& v) const;
    uint128_t min_ciphertext_greater_than(const EncType& v) const;

public:
    std::pair<uint128_t, uint128_t> ciphertext_range(const EncType& v) const;
    uint128_t generate_ciphertext(const EncType& v);
};

template<class EncType>
class OPETree1 : public OPETree<ods::BSTNode1<EncType>, EncType> { };

template <class Node, class EncType>
uint128_t
OPETree<Node, EncType>::generate_ciphertext(const EncType& v)
{
    uint128_t low = max_ciphertext_less_equal_than(v),
        high = min_ciphertext_greater_than(v);
    return random_bound(generator, low, high);
}

template <class Node, class EncType>
std::pair<uint128_t, uint128_t> 
OPETree<Node, EncType>::ciphertext_range(const EncType& v) const
{
    uint128_t low = max_ciphertext_less_equal_than(v),
        high = min_ciphertext_greater_than(v);
    return std::make_pair(low, high);
}

template <class Node, class EncType>
uint128_t 
OPETree<Node, EncType>::max_ciphertext_less_equal_than(const EncType& v) const
{
    uint128_t current_path = 0, path = 0;
    size_t current_path_length = 0, path_length = 0;
    Node *current = r, *max = nil;

    while (current != nil) {
        if (current->x <= v) {
            max = current;
            path = current_path;
            path_length = current_path_length;
            
            current = current->right;
            current_path = (current_path << 1) | 1;
            ++current_path_length;
        } else {
            current = current->left;
            current_path = current_path << 1;
            ++current_path_length;
        }
    }

    if (max == nil) {
        return std::numeric_limits<uint128_t>::min();
    } else {
        path = (path << 1) | 1;
        ++path_length;
        path <<= (128 - path_length);
        return path;
    }
}

template <class Node, class EncType>
uint128_t 
OPETree<Node, EncType>::min_ciphertext_greater_than(const EncType& v) const
{
    uint128_t current_path = 0, path = 0;
    size_t current_path_length = 0, path_length = 0;
    Node *current = r, *min = nil;

    while (current != nil) {
        if (current->x > v) {
            min = current;
            path = current_path;
            path_length = current_path_length;
            
            current = current->left;
            current_path = (current_path << 1);
            ++current_path_length;
        } else {
            current = current->right;
            current_path = (current_path << 1) | 1;
            ++current_path_length;
        }
    }

    if (min == nil) {
        return ~0;
    } else {
        path = (path << 1) | 1;
        ++path_length;
        path <<= (128 - path_length);
        return path;
    }
}

#endif
