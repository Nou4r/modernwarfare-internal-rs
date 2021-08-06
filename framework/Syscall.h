#include <cstdlib>
#include <type_traits>
#include <cstdint>
#include <map>

#include "Debug.h"

namespace detail
{
	extern "C" void* _syscaller_stub();

	template <typename... Args>
	static inline auto syscall_stub_helper(
		Args... args
	) -> void*
	{
		auto fn = reinterpret_cast<void*(*)(Args...)>(&_syscaller_stub);
		return fn(args...);
	}

	template <std::size_t argc, typename>
	struct argument_remapper
	{
		// At least 5 params
		template<
			typename First,
			typename Second,
			typename Third,
			typename Fourth,
			typename... Pack
		>
			static auto do_call(
				std::uint32_t idx,
				First first,
				Second second,
				Third third,
				Fourth fourth,
				Pack... pack
		) -> void*
		{
			return syscall_stub_helper(first, second, third, fourth, idx, nullptr, pack...);
		}
	};

	template <std::size_t Argc>
	struct argument_remapper<Argc, std::enable_if_t<Argc <= 4>>
	{
		// 4 or less params
		template<
			typename First = void*,
			typename Second = void*,
			typename Third = void*,
			typename Fourth = void*
		>
		static auto do_call(
			std::uint32_t idx,
			First first = First{},
			Second second = Second{},
			Third third = Third{},
			Fourth fourth = Fourth{}
		) -> void*
		{
			return syscall_stub_helper(first, second, third, fourth, idx, nullptr);
		}
	};
}

template<typename Return, typename... Args>
static inline auto runSyscall(
	std::uint32_t idx,
	Args... args
) -> Return
{
	using mapper = detail::argument_remapper<sizeof...(Args), void>;
	return (Return)mapper::do_call(idx, args...);
}

inline HCURSOR __stdcall Syscall_SetCursor(HCURSOR hCursor)
{
  //return _NtUserSetCursor(hCursor);
	//return SetCursor(hCursor);
	//return runSyscall<HCURSOR>(0x101A, hCursor);
	return runSyscall<HCURSOR>(0x1018, hCursor);
	/*
	static FARPROC pNtUserSetCursor;
	if (!pNtUserSetCursor)
		pNtUserSetCursor = GetProcAddress(GetModuleHandleA("win32u.dll"), "NtUserSetCursor");
	return reinterpret_cast<HCURSOR(NTAPI *)(HCURSOR)>(pNtUserSetCursor)(hCursor);
	*/
}

inline BOOL __stdcall Syscall_GetCursorPos(LPPOINT lpPoint)
{
	//return _NtUserCallTwoParam(lpPoint, 1, 127);
	//return GetCursorPos(lpPoint);
	//return runSyscall<BOOL>(0x102a, lpPoint, 1, 127);
	return runSyscall<BOOL>(0x141D, lpPoint, 1, 127);
	/*
	static FARPROC pNtUserCallTwoParam;
	if (!pNtUserCallTwoParam) {
		pNtUserCallTwoParam = GetProcAddress(GetModuleHandleA("win32u.dll"), "NtUserCallTwoParam");
		if(!pNtUserCallTwoParam)
		{
			DEBUG_ERROR("Could not find NtUserCallTwoParam");
		}
	}
	return reinterpret_cast<BOOL(NTAPI *)(DWORD_PTR, DWORD_PTR, DWORD)>(pNtUserCallTwoParam)(reinterpret_cast<DWORD_PTR>(lpPoint), 1, 127);
	*/
}
