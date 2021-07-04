//
// Created by draven on 6/6/2021.
//

#pragma once

#include <cstdint>
#include <memory>
#include <Windows.h>
#include "Utils.h"
#include "Debug.h"

class Memory
{
public:
    Memory() noexcept;

    std::uint64_t imageBase;
    std::uint64_t peb;
};

auto get_process_window() noexcept -> HWND;

//#define readMemory(ptr) __readMemory<T>(ptr, __FILE__, __LINE__)

template<typename T>
auto readMemory(uintptr_t ptr) noexcept -> T {
//    dbg::trace("Reading 0x{:X}", ptr);
    if(utils::is_bad_ptr(ptr)) {
        dbg::error("Attempted to read invalid memory at 0x{:X}", ptr);
        return {};
    }
    return *reinterpret_cast<T*>(ptr);
}

template<typename T>
void write_memory(uintptr_t ptr, T value) noexcept {
    *reinterpret_cast<T*>(ptr) = value;
}

inline std::unique_ptr<Memory> memory;