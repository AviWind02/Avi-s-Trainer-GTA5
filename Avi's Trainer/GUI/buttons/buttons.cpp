#include "pch.h"
#include "GUI/menu/menu.h"
#include "GUI/controls/controls.h"

namespace GUI {
    namespace buttons {

        bool Option(const char* Opiton, std::string holder)
        {
            return GUI::menu::SetOption(Opiton, NULL, NULL);
        }

        bool OptionInput(const char* option, char* userInput, int maxLength, bool* enterpressed)
        {
            controls::GetUserInput(option, userInput, maxLength, enterpressed);

            return false;
        }

        //Sets the bool value to true on click
        bool Option(const char* Opiton, bool* value, std::string holder)
        {
            if (GUI::menu::SetOption(Opiton, NULL, NULL))
            {
                *value = true;
                return true;
            }
            return false;
        }

        bool Sub(const char* Opiton, pages::SubMenu menu, std::string holder)
        {
            bool clicked = Option(Opiton);
            GUI::menu::SetSpriteOnOption("commonmenu", "arrowright", { 0.015f, 0.025f }, 1.f, { 255, 255, 255, 255 });
            if (clicked) {
                controls::NextSubmenu(menu);
            }
            return clicked;
        }

        bool Int(const char* option, int* value, int min, int max, int step, std::string holder) {

            bool clicked = false;
            char valueTextBuffer[128];
            snprintf(valueTextBuffer, sizeof(valueTextBuffer), "[%d/%d]", *value, max);

            clicked = GUI::menu::SetOption(option, NULL, valueTextBuffer);;



            if (controls::currentOption == controls::optionCount) {

                if (controls::rightPressed) {
                    *value += step;
                    if (*value > max) *value = min;
                    return true;
                }
                else if (controls::leftPressed) {
                    *value -= step;
                    if (*value < min) *value = max;
                    return true;
                }
            }

            return clicked;
        }

        bool Toggle(const char* option, bool* value, std::string holder) {

            bool clicked = Option(option);
            GUI::menu::SetSpriteOnOption("commonmenu", "common_medal", { 0.015f, 0.025f }, 1.f, (*value ? Colour(0, 255, 0, 255) : Colour(255, 255, 255, 255)));

            if (clicked) {
                *value = !*value;
                return true;
            }

            return false;
        }

        bool Float(const char* option, float* value, float min, float max, float step, std::string holder) {
            bool clicked = false;
            char valueTextBuffer[128];


            if (step >= 1.0f) {
                snprintf(valueTextBuffer, sizeof(valueTextBuffer), "[%.0f/%.0f]", *value, max);
            }
            else if (step >= 0.1f) {
                snprintf(valueTextBuffer, sizeof(valueTextBuffer), "[%.1f/%.1f]", *value, max);
            }
            else if (step >= 0.01f) {
                snprintf(valueTextBuffer, sizeof(valueTextBuffer), "[%.2f/%.2f]", *value, max);
            }
            else {
                snprintf(valueTextBuffer, sizeof(valueTextBuffer), "[%.3f/%.3f]", *value, max);
            }

            clicked = GUI::menu::SetOption(option, NULL, valueTextBuffer);

            if (controls::currentOption == controls::optionCount) {

                if (controls::rightPressed) {
                    *value += step;
                    if (*value > max) *value = min;
                    return true;
                }
                else if (controls::leftPressed) {
                    *value -= step;
                    if (*value < min) *value = max;
                    return true;
                }
            }

            return clicked;
        }

        bool StringArray(const char* option, int& currentIndex, const std::vector<std::string>& options, std::string holder)
        {
            if (options.empty())
                return false;

            char valueTextBuffer[128];
            snprintf(valueTextBuffer, sizeof(valueTextBuffer), "[%s]", options[currentIndex]);
            bool cliked = GUI::menu::SetOption(option, NULL, valueTextBuffer);

            if (controls::currentOption == controls::optionCount)
            {
                if (controls::rightPressed)
                {
                    currentIndex = (currentIndex + 1) % options.size();
                    return true;
                }
                else if (controls::leftPressed)
                {
                    currentIndex = (currentIndex - 1 + options.size()) % options.size();
                    return true;
                }
                return cliked;
            }
            return false;
        }


    }
}