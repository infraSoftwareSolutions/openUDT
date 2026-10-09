
#include "ptr_8.hpp"
#include "ptr_16.hpp"
#include "ptr_32.hpp"
#include "ptr_64.hpp"
#include <vector>
#include <string>
#include <unordered_map>
#include "cfrost/types.h"

#pragma once
#ifndef OPENUDT___VIRTUAL___MACHINE_HPP
#define OPENUDT___VIRTUAL___MACHINE_HPP

namespace udt
{
    namespace Virtual
    {
        using data = std::vector<uint8_t>;
        using segments = ocf::hash_map<ocf::str, std::pair<size_t, data>>;

        class machine_8
        {
            ocf::hash_map<ocf::str, uint8_t> registers;
            ocf::hash_map<ocf::str, std::pair<size_t, data>> segments;
            ocf::hash_map<ocf::str, ptr_8> segments_indexs;
        };

        class machine_16
        {
            ocf::hash_map<ocf::str, uint16_t> registers;
            ocf::hash_map<ocf::str, std::pair<size_t, data>> segments;
            ocf::hash_map<ocf::str, ptr_16> segments_indexs;
        };

        class machine_32
        {
            ocf::hash_map<ocf::str, uint32_t> registers;
            ocf::hash_map<ocf::str, std::pair<size_t, data>> segments;
            ocf::hash_map<ocf::str, ptr_32> segments_indexs;
        };

        class machine_64
        {
            ocf::hash_map<ocf::str, uint64_t> registers;
            ocf::hash_map<ocf::str, std::pair<size_t, data>> segments;
            ocf::hash_map<ocf::str, ptr_64> segments_indexs;
        };
    }
}

#endif // OPENUDT___VIRTUAL___MACHINE_HPP