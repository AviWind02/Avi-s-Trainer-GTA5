#include "pch.h"

namespace {
    template<typename Out>
    void split(const std::string& s, char delim, Out result) {
        std::stringstream ss(s);
        std::string item;
        while (std::getline(ss, item, delim)) {
            *(result++) = item;
        }
    }

    std::vector<std::string> split(const std::string& s, char delim) {
        std::vector<std::string> elems;
        ::split(s, delim, std::back_inserter(elems));
        return elems;
    }
}

namespace core::memory {
    namespace patterns {

        // Function pointers for native functions
        uintptr_t(*GetAddressOfEntity)(int entity) = nullptr;
        uintptr_t(*GetModelInfo)(unsigned int modelHash, int* index) = nullptr;

  

        uintptr_t FindPattern(const char* pattern, const char* mask) {
            MODULEINFO modInfo = { nullptr };
            GetModuleInformation(GetCurrentProcess(), GetModuleHandle(nullptr), &modInfo, sizeof(MODULEINFO));

            const char* start_offset = reinterpret_cast<const char*>(modInfo.lpBaseOfDll);
            const uintptr_t size = static_cast<uintptr_t>(modInfo.SizeOfImage);
            intptr_t pos = 0;
            const uintptr_t searchLen = static_cast<uintptr_t>(strlen(mask) - 1);

            for (const char* retAddress = start_offset; retAddress < start_offset + size; ++retAddress) {
                if (*retAddress == pattern[pos] || mask[pos] == '?') {
                    if (mask[pos + 1] == '\0') {
                        //LOG_TAG("DEBUG") << "Pattern found at address: " << std::hex << retAddress - searchLen;
                        return (reinterpret_cast<uintptr_t>(retAddress) - searchLen);
                    }
                    ++pos;
                }
                else {
                    pos = 0;
                }
            }
            LOG_TAG("DEBUG") << "Pattern not found.";
            return 0;
        }

        std::vector<uintptr_t> FindPatterns(const char* pattern, const char* mask) {
            std::vector<uintptr_t> addresses;
            MODULEINFO modInfo = { nullptr };
            GetModuleInformation(GetCurrentProcess(), GetModuleHandle(nullptr), &modInfo, sizeof(MODULEINFO));

            const char* start_offset = reinterpret_cast<const char*>(modInfo.lpBaseOfDll);
            const uintptr_t size = static_cast<uintptr_t>(modInfo.SizeOfImage);
            intptr_t pos = 0;
            const uintptr_t searchLen = static_cast<uintptr_t>(strlen(mask) - 1);

            for (const char* retAddress = start_offset; retAddress < start_offset + size; ++retAddress) {
                if (*retAddress == pattern[pos] || mask[pos] == '?') {
                    if (mask[pos + 1] == '\0') {
                        addresses.push_back(reinterpret_cast<uintptr_t>(retAddress) - searchLen);
                    }
                    ++pos;
                }
                else {
                    pos = 0;
                }
            }
            //LOG_TAG("DEBUG") << addresses.size() << " pattern(s) found.";
            return addresses;
        }

        uintptr_t FindPattern(const char* pattStr) {
            std::vector<std::string> bytesStr = split(pattStr, ' ');
            MODULEINFO modInfo{};
            GetModuleInformation(GetCurrentProcess(), GetModuleHandle(nullptr), &modInfo, sizeof(MODULEINFO));

            auto* start_offset = static_cast<uint8_t*>(modInfo.lpBaseOfDll);
            const auto size = static_cast<uintptr_t>(modInfo.SizeOfImage);
            uintptr_t pos = 0;
            const uintptr_t searchLen = bytesStr.size();

            for (auto* retAddress = start_offset; retAddress < start_offset + size; ++retAddress) {
                if (bytesStr[pos] == "??" || bytesStr[pos] == "?" ||
                    *retAddress == static_cast<uint8_t>(std::strtoul(bytesStr[pos].c_str(), nullptr, 16))) {
                    if (pos + 1 == bytesStr.size()) {
                        //LOG_TAG("DEBUG") << "Pattern string found at address: " << std::hex << reinterpret_cast<uintptr_t>(retAddress) - searchLen + 1;
                        return (reinterpret_cast<uintptr_t>(retAddress) - searchLen + 1);
                    }
                    ++pos;
                }
                else {
                    pos = 0;
                }
            }
            LOG_TAG("ERROR") << "Pattern string not found.";
            return 0;
        }
    }
}