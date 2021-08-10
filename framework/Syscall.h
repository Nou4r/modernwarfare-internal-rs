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


// HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\DisplayVersion
static std::string getVersion()
{
    DWORD dwType = REG_SZ;
    HKEY hKey = 0;
    char value[1024];
    DWORD value_length = 1024;
    const char* subkey = "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion";
    RegOpenKey(HKEY_LOCAL_MACHINE, subkey, &hKey);
    const auto status = RegQueryValueEx(hKey, "DisplayVersion", NULL, &dwType, (LPBYTE) &value, &value_length);
	RegCloseKey(hKey);
    return std::string(value);
}

inline HCURSOR __stdcall Syscall_SetCursor(HCURSOR hCursor)
{

	static auto version = getVersion();
	int id = 4122;

	/*
      "1507": 4125,
      "1511": 4125,
      "1607": 4125,
      "1703": 4125,
      "1709": 4125,
      "1803": 4125,
      "1809": 4125,
      "1903": 4125,
      "1909": 4125,
      "2004": 4122,
      "20H2": 4122,
      "21H2": 4120,
	 */

	  if (version == "1507"){ id = 4125; }
      else if(version == "1511"){ id = 4125; }
      else if(version == "1607"){ id = 4125; }
      else if(version == "1703"){ id = 4125; }
      else if(version == "1709"){ id = 4125; }
      else if(version == "1803"){ id = 4125; }
      else if(version == "1809"){ id = 4125; }
      else if(version == "1903"){ id = 4125; }
      else if(version == "1909"){ id = 4125; }
      else if(version == "2004"){ id = 4122; }
      else if(version == "20H2"){ id = 4122; }
      else if(version == "21H2"){ id = 4120; }

	return runSyscall<HCURSOR>(id, hCursor);
	//return runSyscall<HCURSOR>(0x1018, hCursor);
	/*
	static FARPROC pNtUserSetCursor;
	if (!pNtUserSetCursor)
		pNtUserSetCursor = GetProcAddress(GetModuleHandleA("win32u.dll"), "NtUserSetCursor");
	return reinterpret_cast<HCURSOR(NTAPI *)(HCURSOR)>(pNtUserSetCursor)(hCursor);
	*/
}

inline BOOL __stdcall Syscall_GetCursorPos(LPPOINT lpPoint)
{
	//NtUserCallTwoParam
	static auto version = getVersion();
	int id = 4138;

	/*
      "1507": 4141,
      "1511": 4141,
      "1607": 4141,
      "1703": 4141,
      "1709": 4141,
      "1803": 4141,
      "1809": 4141,
      "1903": 4141,
      "1909": 4141,
      "2004": 4138,
      "20H2": 4138,
	  "21H2": 5149,
	  */
	if (version == "1507") { id = 4141; }
      else if(version == "1511") { id = 4141; }
	  else if(version == "1607") { id = 4141; }
      else if(version == "1703") { id = 4141; }
      else if(version == "1709") { id = 4141; }
      else if(version == "1803") { id = 4141; }
      else if(version == "1809") { id = 4141; }
      else if(version == "1903") { id = 4141; }
      else if(version == "1909") { id = 4141; }
      else if(version == "2004") { id = 4138; }
      else if(version == "20H2") { id = 4138; }
	  else if(version == "21H2") { id = 5149; }


	return runSyscall<BOOL>(id, lpPoint, 1, 127);
	// win11
	//return runSyscall<BOOL>(0x141D, lpPoint, 1, 127);
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

inline ULONG __stdcall Syscall_SendInput(INPUT input)
{
    // NtUserSendInput
    //      "1507": 4228,
    //      "1511": 4228,
    //      "1607": 4228,
    //      "1703": 4226,
    //      "1709": 4226,
    //      "1803": 4226,
    //      "1809": 4226,
    //      "1903": 4226,
    //      "1909": 4226,
    //      "2004": 4223,
    //      "20H2": 4223
    static auto version = getVersion();
    int id = 4223;
    if (version == "1507") {
        id = 4228;
    } else if (version == "1511") {
        id = 4228;
    } else if (version == "1607") {
        id = 4228;
    } else if (version == "1703") {
        id = 4226;
    } else if (version == "1709") {
        id = 4226;
    } else if (version == "1803") {
        id = 4226;
    } else if (version == "1809") {
        id = 4226;
    } else if (version == "1903") {
        id = 4226;
    } else if (version == "1909") {
        id = 4226;
    } else if (version == "2004") {
        id = 4223;
    } else if (version == "20H2") {
        id = 4223;
    }

    return runSyscall<ULONG>(id, 1, &input, sizeof(INPUT));
}
