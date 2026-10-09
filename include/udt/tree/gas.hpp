// gas: generalized abstract syntax tree

#include "binary.hpp"
#include "etl/token.hpp"
#include "cfrost/types.h"

#pragma once
#ifndef OPENUDT___TREE___GAS_HPP
#define OPENUDT___TREE___GAS_HPP

namespace udt
{
    namespace tree
    {
        class gas
        {
        private:
            binary<ocf::str, false> tree;
            etl::hash_enum hash_order;

        public:
            gas() = default;
            ~gas() = default;

            gas(const std::initializer_list<ocf::str> &list) noexcept : hash_order(list)
            {
                for (ocf::str element : list)
                {
                    tree.add(true, element);
                }
            }

            gas(const gas &other) noexcept : tree(other.tree), hash_order(other.hash_order) {}

            inline auto begin() noexcept
            {
                return tree.begin();
            }

            inline auto end() noexcept
            {
                return tree.end();
            }

            constexpr inline size_t size() noexcept
            {
                return tree.size();
            }

            inline void operator=(const gas &other) noexcept
            {
                tree = other.tree;
                hash_order = other.hash_order;
            }
        }
    }
}

#endif // OPENUDT___TREE___GAS_HPP