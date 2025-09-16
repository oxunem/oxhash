# oxhash

**Universal constexpr & runtime string hashing for C++17+ (User Mode & Kernel Mode)**

---

## Overview

**oxhash** is a lightweight, zero-dependency, single-header C++ library that provides fast and reliable string hashing at both **compile-time** and **runtime**. It is specifically designed to work in both **User Mode** and **Kernel Mode** environments on Windows, making it ideal for performance-critical and security-sensitive applications like loaders, drivers, anti-cheat systems, and malware analysis tools.

The library supports both `char` and `wchar_t` strings and is suitable for use in places where traditional function names or strings must be hidden — such as custom implementations of `GetProcAddress`, syscall resolution, or API lookup by hashed names.

---

## Features

- **Compile-time hashing** using `constexpr` functions  
- **Fast runtime hashing** with minimal overhead  
- Works in both **User Mode** and **Kernel Mode**  
- No CRT, STL, or external dependencies  
- Supports both `char` and `wchar_t` strings  
- Single-header only, drop-in integration  
- Suitable for anti-debugging and anti-reversing  
- Compatible with both **x86** and **x64** architectures  

---

## How It Works

oxhash provides two hashing functions:

1. **Compile-time hash (`HashCompileTime`)**  
   Evaluates the hash entirely at compile-time using `constexpr` for string literals.

2. **Runtime hash (`HashRuntime`)**  
   Provides the same hashing logic as `HashCompileTime`, but can evaluate strings at runtime — ideal for user input or dynamic strings.

Both functions implement a custom 64-bit hashing algorithm inspired by high-entropy prime-based mixing (similar in spirit to xxHash64) to produce hard-to-reverse and low-collision hash values.

---

## Usage

### Integration

Just include the `oxhash.hpp` file in your project:

```cpp
#include "oxhash.hpp"
