#pragma once

#include <memory>
#include <Windows.h>

enum class InputEventType {
    KeyDown = 0,
    KeyUp = 1
};

class Framework
{
public:
	explicit Framework(HMODULE moduleHandle);
	auto unload() -> void;
};


inline std::unique_ptr<Framework> framework;
