#pragma once
namespace GUI {
    namespace buttons {

        bool Option(const char* option);
        bool Sub(const char* Opiton, pages::SubMenu menu);
        bool Int(const char* option, int* value, int min, int max, int step);
        bool Toggle(const char* option, bool* value);
        bool Float(const char* option, float* value, float min, float max, float step);
        bool StringArray(const char* option, int& currentIndex, const std::vector<std::string>& options);
    }
}