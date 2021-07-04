//
// Created by draven on 6/6/2021.
//

#pragma once

#include <Windows.h>
#include <memory>
#include <chrono>

enum class InputEventType {
    KeyDown = 0,
    KeyUp = 1
};

class Cheat
{
public:
    explicit Cheat(HMODULE moduleHandle) noexcept;

    void tick() noexcept;
    void handleInputEvent(InputEventType type, std::uint32_t key) noexcept;
    void unload() noexcept;

    HMODULE moduleHandle;
    std::chrono::duration<double> tickTime;
};

inline std::unique_ptr<Cheat> cheat;