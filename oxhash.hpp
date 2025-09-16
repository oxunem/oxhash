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

// Build-unique seed: derived from compile-time macros.
// This value will typically change between builds (when __TIME__ / __DATE__ change),
// but within a single build it expands to the same numeric value in all translation units.
// It intentionally does NOT use __COUNTER__ or __LINE__ here, so you can safely reuse
// the same seed for both compile-time and runtime hashing within the same build.
#define OXHASH_UNIQUE_SEED ( (__TIME__[0]<<24 | __TIME__[1]<<16 | __TIME__[2]<<8 | __TIME__[3]) ^ \
                            (__DATE__[0]<<24 | __DATE__[1]<<16 | __DATE__[2]<<8 | __DATE__[3]) ^ \
                            0xCAFEBABE12345678ull )

// Compile-time string hashing
template<typename CharT, unsigned __int64 N>
static constexpr unsigned long long HashCompileTime(const CharT(&str)[N])
{
    unsigned long long hash = OXHASH_UNIQUE_SEED;

    for (unsigned __int64 i = 0; i < N - 1; ++i)
    {
        hash = (hash * 31) ^ static_cast<uint64_t>(str[i]);
    }

    hash ^= hash >> 16;
    hash *= 0x27d4eb2d;
    hash ^= hash >> 16;
    return hash;
}

// Wrapper to force constexpr evaluation & prevent string literal emission
template<unsigned long long V>
struct CompileTimeHashWrapper
{
    static constexpr unsigned long long value = V;
};

// Runtime string hashing
template<typename CharT>
static __forceinline unsigned long long HashRuntime(const CharT* str)
{
    unsigned long long hash = OXHASH_UNIQUE_SEED;

    while (*str)
    {
        hash = (hash * 31) ^ static_cast<uint64_t>(*str);
        ++str;
    }

    hash ^= hash >> 16;
    hash *= 0x27d4eb2d;
    hash ^= hash >> 16;
    return hash;
}

// ------------------------------------------------------------
// Macros for convenience
// Usage:
//   constexpr auto h1 = OXHASH_CTIME("SomeCompileTimeString");
//   auto h2 = OXHASH_RUNTIME("SomeRuntimeString");
// ------------------------------------------------------------
#define OXHASH_CTIME(str) \
    CompileTimeHashWrapper<HashCompileTime(str)>::value

#define OXHASH_RUNTIME(str) \
    HashRuntime(str)

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
