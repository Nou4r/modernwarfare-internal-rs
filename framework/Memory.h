#pragma once
#include <memory>

class Memory
{
public:
	Memory()
	{
		this->imageBase = reinterpret_cast<uint64_t>(GetModuleHandle(nullptr));
		this->peb = __readgsqword(0x60);
	}

	uint64_t imageBase;
	uint64_t peb;
};

inline std::unique_ptr<Memory> memory;
