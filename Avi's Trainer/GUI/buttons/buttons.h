#pragma once
namespace GUI {
    namespace buttons {

        bool Option(const char* option, std::string holder = "");
        bool OptionInput(const char* option, char* userInput, int maxLength, bool* enterpressed);
        bool Option(const char* Opiton, bool* value, std::string holder = "");
        bool Sub(const char* Opiton, pages::SubMenu menu, std::string holder = "");
        bool Int(const char* option, int* value, int min, int max, int step = 1, std::string holder = "");
        bool Toggle(const char* option, bool* value, std::string holder = "");
        bool Float(const char* option, float* value, float min, float max, float step = 1.f, std::string holder = "");
        bool StringArray(const char* option, int& currentIndex, const std::vector<std::string>& options, std::string holder ="");
    }
}
//since this file is in PCH just gonna toss this here.
namespace GUI {
    namespace menu {
        void SetSubTitle(std::string title);
    }
}