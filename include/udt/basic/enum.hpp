#pragma once
#include "cfrost/types.h"
#include "meta/adva/function.hpp"
#include "meta/lite/io.hpp"

namespace udt
{
    class enum_decimal
    {
    private:
        ocf::vec<size_t> hash_numbers;

    protected:
        void allocate_numbers()
        {
            for (char c = '0'; c <= '9'; c++)
                hash_numbers.push_back(0);
        }

    public:
        enum_decimal() { allocate_numbers(); }
        ~enum_decimal() = default;

        constexpr void operator<<(const char &c) noexcept
        {
            if (meta::adva::is_digit(c))
                hash_numbers[c - '0']++;
            else
                meta::lite::io::println_error("the char is not a support digit or char");
        }

        inline void operator<<(const ocf::str &s) noexcept
        {
            for (const char &c : s)
                *this << c;
        }

        constexpr size_t operator[](const char &c) noexcept
        {
            return hash_numbers[c - '0'];
        }

        constexpr bool contains(const char &c) noexcept
        {
            return (c >= ' ' && c <= '~') ? hash_numbers[c - ' '] > 0 : false;
        }
    };

    class enum_ascii
    {
    private:
        ocf::vec<size_t> count;

    protected:
        inline void allocate_ascii() noexcept
        {
            for (char start = ' '; start < '~'; start++)
                count.push_back(0);
        }

    public:
        enum_ascii() { allocate_ascii(); }
        ~enum_ascii() = default;

        constexpr void operator<<(const char &c) noexcept
        {
            if (c >= ' ' && c <= '~')
                count[c - ' ']++;
        }

        inline void operator<<(const ocf::str &s) noexcept
        {
            for (const char &c : s)
                *this << c;
        }

        constexpr size_t operator[](const char &c) noexcept
        {
            return (c >= ' ' && c <= '~') ? count[c - ' '] : 0;
        }

        inline bool operator==(const enum_ascii &other) noexcept
        {
            for (size_t i = 0; i < count.size(); i++)
            {
                if (count[i] != other.count[i])
                    return false;
            }
            return true;
        }

        inline bool operator!=(const enum_ascii &other) { return !(*this == other); }

        constexpr bool contains(const char &c) noexcept
        {
            return (c >= ' ' && c <= '~') ? count[c - ' '] > 0 : false;
        }
    };
}