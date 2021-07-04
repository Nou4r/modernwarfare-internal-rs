#include "Utils.h"
#include "lazy_importer.h"
#include <random>
#include <sstream>
#include <vector>
#include <Windows.h>
#include "imgui.h"
#include "xorstr.h"

uint8_t* utils::find_pattern(const char* signature, const char* module_name) {
	static auto pattern_to_byte = [](const char* pattern) {
		auto bytes = std::vector<int>{ };
		auto* const start = const_cast<char*>(pattern);
		auto* const end = const_cast<char*>(pattern) + strlen(pattern);

		for (auto* current = start; current < end; ++current) {
			if (*current == '?') {
				++current;
				if (*current == '?')
					++current;
				bytes.push_back(-1);
			}
			else {
				bytes.push_back(strtoul(current, &current, 16));
			}
		}
		return bytes;
	};

	auto* const module = LI_FN(GetModuleHandleA).cached()(module_name);
	auto* const dos_headers = reinterpret_cast<PIMAGE_DOS_HEADER>(module);
	if (!dos_headers)
		return nullptr;

	auto* const nt_headers = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<std::uint8_t*>(module) + dos_headers->e_lfanew);

	auto pattern_bytes = pattern_to_byte(signature);
	auto* const scan_bytes = reinterpret_cast<std::uint8_t*>(module);

	const auto s = pattern_bytes.size();
	auto* const d = pattern_bytes.data();

	for (auto i = 0ul; i < nt_headers->OptionalHeader.SizeOfImage - s; ++i) {
		auto found = true;
		for (auto j = 0ul; j < s; ++j) {
			if (scan_bytes[i + j] != d[j] && d[j] != -1) {
				found = false;
				break;
			}
		}
		if (found) {
			return &scan_bytes[i];
		}
	}
	return nullptr;
}




int utils::random_int(const int min, const int max) {
	std::random_device rd;
	std::mt19937 rng(rd());
	const std::uniform_int_distribution<int> uni(min, max);

	return static_cast<int>(uni(rng));
}

template <typename charT>
struct my_equal {
	explicit my_equal(const std::locale& loc) : loc_(loc) {
	}

	bool operator()(charT ch1, charT ch2) {
		return std::toupper(ch1) == std::toupper(ch2);
	}

private:
	const std::locale& loc_;
};

int utils::find_string(const std::string& str1, const std::string&& str2) {
	const auto loc = std::locale();

	if (const auto it = std::ranges::search(str1, str2, my_equal<std::string::value_type>(loc)).begin(); it != str1.end())
		return it - str1.begin();

	return -1;
}

std::string utils::base64_decode(const std::string& encoded_string) {
	const std::string base64_chars =
		_("ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz"
			"0123456789+/");

	std::string out;
	std::vector<int> T(256, -1);
	for (auto i = 0u; i < 64; i++) T[base64_chars[i]] = i;

	auto valb = -8;
	for (auto val = 0; unsigned char c : encoded_string) {
		if (T[c] == -1) break;
		val = (val << 6) + T[c];
		valb += 6;
		if (valb >= 0) {
			out.push_back(static_cast<char>(val >> valb & 0xFF));
			valb -= 8;
		}
	}

	return out;
}

std::string utils::base64_encode(const std::string& decoded_string) {
	std::string out;

	auto val = 0, valb = -6;
	for (auto c : decoded_string) {
		val = (val << 8) + c;
		valb += 8;
		while (valb >= 0) {
			out.push_back(_("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/")[val >> valb & 0x3F]);
			valb -= 6;
		}
	}
	if (valb > -6) out.push_back(_("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/")[val << 8 >> valb + 8 & 0x3F]);
	while (out.size() % 4) out.push_back('=');

	return out;
}