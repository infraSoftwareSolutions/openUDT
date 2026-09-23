#include <string>
#include "cfrost/structure.h"

#pragma once
#ifndef OPENUDT___BASIC___STRING_STR_F_HPP
#define OPENUDT___BASIC___STRING_STR_F_HPP

namespace udt
{
    template <size_t fixSize>
    class str_f
    {
    private:
        char string[fixSize];
        size_t length, maxSize = fixSize;

    public:
        str_f() noexcept : string(""), length(0) {}

        str_f(const char *s) : length(0)
        {
            size_t len = strlen(s);
            if (len >= fixSize)
                len = fixSize - 1;
            memcpy(string, s, len);
            string[len] = '\0';
            length = len;
        }

        str_f(const ocf::str &s) : length(0)
        {
            size_t len = s.length();
            if (len >= fixSize)
                len = fixSize - 1;
            memcpy(string, s.c_str(), len);
            string[len] = '\0';
            length = len;
        }

        str_f(const str_f &other) : length(other.length)
        {
            memcpy(string, other.string, length);
            string[length] = '\0';
        }

        str_f &operator=(const str_f &other)
        {
            if (this != &other)
            {
                length = other.length;
                memcpy(string, other.string, length);
                string[length] = '\0';
            }
            return *this;
        }

        const char *c_str() const noexcept { return string; }

        ocf::str cxx_str() const { return ocf::str(string); }

        size_t size() const noexcept { return length; }

        size_t capacity() const noexcept { return maxSize; }

        procedure(clear) noexcept
        {
            string[0] = '\0';
            length = 0;
        }

        procedure(upper) noexcept
        {
            for (size_t i = 0; i < length; ++i)
                string[i] = toupper(string[i]);
        }

        procedure(lower) noexcept
        {
            for (size_t i = 0; i < length; ++i)
                string[i] = tolower(string[i]);
        }

        bool is_number(char number_system = 'd') noexcept
        {
            for (size_t i = 0; i < length; ++i)
            {
                if (string[i] < '0')
                    return false;
                else if (number_system == 'd' && string[i] > '9')
                    return false;
                else if (number_system == 'b' && string[i] > '1')
                    return false;
                else if (number_system == 'o' && string[i] > '7')
                    return false;
                else if (number_system == 't' && string[i] > '2')
                    return false;
            }
        }

        bool has_number(char number_system = 'd') noexcept
        {
            for (size_t i = 0; i < length; ++i)
            {
                if (number_system == 'd' && string[i] <= '9' && string[i] >= '0')
                    return true;
                else if (number_system == 'b' && string[i] <= '1' && string[i] >= '0')
                    return true;
                else if (number_system == 'o' && string[i] <= '7' && string[i] >= '0')
                    return false;
                else if (number_system == 't' && string[i] <= '2' && string[i] >= '0')
                    return false;
            }
        }

        void xchg(str_f &other) noexcept
        {
            char temp[fixSize];
            size_t tempLength = length;

            memcpy(temp, string, length);
            memcpy(string, other.string, other.length);
            memcpy(other.string, temp, tempLength);

            length = other.length;
            other.length = tempLength;
        }

        void xchg(ocf::str &other) noexcept
        {
            char temp[fixSize];
            size_t tempLength = length;

            memcpy(temp, string, length);
            memcpy(string, other.c_str(), other.length());
            memcpy(other.data(), temp, tempLength);

            length = other.length();
            other.resize(tempLength);
        }

        void xchg(char *other, size_t otherLength) noexcept
        {
            char temp[fixSize];
            size_t tempLength = length;

            memcpy(temp, string, length);
            memcpy(string, other, otherLength);
            memcpy(other, temp, tempLength);

            length = otherLength;
        }

        void xchg(size_t pos1, size_t pos2) noexcept
        {
            if (pos1 >= length || pos2 >= length)
                return;

            char temp = string[pos1];
            string[pos1] = string[pos2];
            string[pos2] = temp;
        }
    };
}

#endif // OPENUDT___BASIC___STRING_STR_F_HPP