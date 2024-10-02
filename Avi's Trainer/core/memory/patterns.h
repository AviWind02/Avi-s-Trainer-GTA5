#pragma once
namespace core::memory {
    namespace patterns {

        uintptr_t FindPattern(const char* pattern, const char* mask);
        std::vector<uintptr_t> FindPatterns(const char* pattern, const char* mask);
        uintptr_t FindPattern(const char* pattStr);
    }

}