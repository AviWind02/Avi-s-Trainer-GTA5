#pragma once
namespace GUI {
    namespace buttons {

        bool Option(const char* option, std::string holder = "");
        bool OptionEX(const char* Opiton, const char* cOpiton = NULL, const char* rOpiton = NULL, std::string holder = "");
        bool OptionInput(const char* option, char* userInput, int maxLength, bool* enterpressed);
        bool Option(const char* Opiton, bool* value, std::string holder = "");
        bool Break(const char* Opiton = NULL, const char* cOpiton = NULL, const char* rOpiton = NULL);
        bool Sub(const char* Opiton, pages::SubMenu menu, std::string holder = "");
        bool Int(const char* option, int* value, int min, int max, int step = 1, std::string holder = "");
        bool Toggle(const char* option, bool* value, std::string holder = "");
        bool Float(const char* option, float* value, float min, float max, float step = 1.f, std::string holder = "");
        bool StringArray(const char* option, int& currentIndex, const std::vector<std::string>& options, std::string holder ="");

        //Trying lambda never done it tho
        bool Option(const char* option, const std::function<void()>& action);
        bool Sub(const char* Opiton, pages::SubMenu menu, const std::function<void()>& action);
        bool Toggle(const char* option, bool* value, const std::function<void()>& action);
        bool Int(const char* option, int* value, int min, int max, int step, const std::function<void()>& action);
        bool Float(const char* option, float* value, float min, float max, float step, const std::function<void()>& action);

    }
}
//since this file is in PCH just gonna toss this here.
namespace GUI {
    namespace menu {
        void SetSubTitle(std::string title);
        void SetSpriteOnOption(const std::string& textureDict, const std::string& textureName, Vector2 size = { 0.015f, 0.025f }, float rotation = 1.f, Colour color = { 255, 255, 255, 255 });
    }
}