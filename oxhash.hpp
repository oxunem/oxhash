// Universal compile-time & runtime string hashing (C++17+)
// Author: oxunem (https://github.com/oxunem)
// License: MIT

#pragma once

// ------------------------------------------------------------
// oxhash is a lightweight string hashing library supporting
// both compile-time (constexpr) and runtime hashing.
//
// Features:
//   - Supports both `char` and `wchar_t`
//   - Works on x86/x64, user-mode and kernel-mode
//   - Zero dependencies, header-only
//   - Ideal for anti-reversing (e.g., replacing GetProcAddress)
// ------------------------------------------------------------

// Hash constants (based on a variant of xxHash64 primes)
constexpr unsigned long long PRIME1 = 11400714785074694791ull;
constexpr unsigned long long PRIME2 = 14029467366897019727ull;
constexpr unsigned long long PRIME3 = 1609587929392839161ull;
constexpr unsigned long long SEED = 0xBADC0FFEE0DDF00Dull;

// Compile-time string hashing
template<typename CharT>
static constexpr unsigned long long hash_compiletime(const CharT* str)
{
    unsigned long long hash = SEED;
    int i = 0;

    while (str[i] != 0)
    {
        hash ^= static_cast<unsigned long long>(
            static_cast<unsigned char>(str[i])
            ) * PRIME1;

        hash = (hash << 13) | (hash >> (64 - 13));
        hash *= PRIME2;
        ++i;
    }

    hash ^= hash >> 33;
    hash *= PRIME3;
    hash ^= hash >> 29;
    return hash;
}

// Runtime string hashing
template<typename CharT>
static __forceinline unsigned long long hash_runtime(const CharT* str)
{
    unsigned long long hash = SEED;

    while (*str)
    {
        hash ^= static_cast<unsigned long long>(
            static_cast<unsigned char>(*str)
            ) * PRIME1;
        hash = (hash << 13) | (hash >> (64 - 13));
        hash *= PRIME2;
        ++str;
    }

    hash ^= hash >> 33;
    hash *= PRIME3;
    hash ^= hash >> 29;
    return hash;
}


// ------------------------------------------------------------
// Macros for convenience
// Usage:
//   constexpr auto h1 = OXHASH_CTIME("SomeCompileTimeString");
//   auto h2 = OXHASH_RUNTIME("SomeRuntimeString");
// ------------------------------------------------------------
#define OXHASH_CTIME(str) hash_compiletime(str)
#define OXHASH_RUNTIME(str) hash_runtime(str)

/*
MIT License

Copyright (c) 2025 oxunem

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
