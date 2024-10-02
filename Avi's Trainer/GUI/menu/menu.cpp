#include "pch.h"
#include "menu.h"
#include <vendor/imgui/imgui.h>
// This page has the main menu elements the core you can say. 
//Here is where the Title, Option, and other UI methods are

namespace GUI {
    namespace menu {
        namespace colours {
            Colour optionText = { 255, 255, 255, 255 };
            Colour optionRect = { 0, 0, 0, 225 };
            Colour scrollerColor = { 255, 223, 0, 175 };
            Colour scrollerColorHover = { 255, 255, 255, 50 };
            Colour hoverColor = { 100, 100, 100, 190 };
            Colour toggleOff = { 255, 0, 0, 255 };
            Colour toggleOn = { 0, 255, 0, 255 };
            Colour footerRect = { 0, 0, 0, 255 };
            Colour headerRect = { 0, 0, 0, 255 };
        }

        int maxOptions = 10;
        int hoveredOption;

        Vector2 menuPosition = { 0.15f, 0.125f };
        Vector2 optionSize = { 0.17f, 0.025f };
        Vector2 optionOffset = { 0.0f, 0.010f };
        Vector2 headerSize = { optionSize.x, 0.047f };
        Vector2 headerTextOffset = { optionSize.x, 0.065f };
        Vector2 footerSize = { optionSize.x, 0.025f };

        Vector2 textOffset = { 0.08f, 0.0025f };
        Vector2 rightTextOffset = { 0.0f, 0.005f };
        Vector2 footerTextOffset = { 0.08f, 0.0025f };
        Vector2 spriteOffset = { 0.008, 0.0142 };

        float scrollerY = menuPosition.y + 0.125f;
        float scrollerSpeed = 0.10f;
        float textScale = 0.25f;
        float screenWidth = 1920.0f;
        float screenHeight = 1080.0f;

        std::string subTitle = "Avi";
        bool onLoad = true;

        // Debug variables
        Vector2 debugMouseCoords = { 0.0f, 0.0f };
        Vector2 debugMouseScreenCoords = { 0.0f, 0.0f };
        bool debugIsDragging;
        Vector2 debugDragOffset = { 0.0f, 0.0f };
        Vector2 debugMenuPosition = { 0.0f, 0.0f };
        bool debugMouseInOption;
        int debugHoveredOption = -1;
        float debugMouseDistanceFromOption = -1.0f;

        void EnableMouse()//Meh
        {
            if (controls::cursorVisible)
            {
                HUD::_SET_MOUSE_CURSOR_ACTIVE_THIS_FRAME();
                PAD::IS_USING_CURSOR(2);
                HUD::_SET_MOUSE_CURSOR_SPRITE(MOUSE_Normal);
            }
            else
                return;
        }

        Vector2 GetScreenCoords(float normalizedX, float normalizedY) {
            Vector2 screenCoords{ 0.f, 0.f };
            screenCoords.x = normalizedX * screenWidth;
            screenCoords.y = normalizedY * screenHeight;
            return screenCoords;
        }

        bool IsMouseInBounds(float x, float y, float width, float height) {
            float mouseX = PAD::GET_CONTROL_NORMAL(0, INPUT_CURSOR_X);
            float mouseY = PAD::GET_CONTROL_NORMAL(0, INPUT_CURSOR_Y);

            Vector2 mouseCoords = GetScreenCoords(mouseX, mouseY);

            x = x - width / 2;
            y = y - height / 2;

            Vector2 topLeft = GetScreenCoords(x, y);
            Vector2 bottomRight = GetScreenCoords(x + width, y + height);

            return mouseCoords.x >= topLeft.x && mouseCoords.x <= bottomRight.x && mouseCoords.y >= topLeft.y && mouseCoords.y <= bottomRight.y;
        }



        bool SetOption(const char* leftText, const char* centerText, const char* rightText)
        {
            controls::optionCount++;
            bool lClickOnMouse = false;
            int startOption = (controls::currentOption - 1) / maxOptions * maxOptions + 1;
            int endOption = startOption + maxOptions - 1;

            if (controls::optionCount >= startOption && controls::optionCount <= endOption) {
                float yPos = (optionSize.y * (controls::optionCount - startOption + 1) + optionOffset.y) + menuPosition.y;

                static float smoothScrollYPosition = yPos;//Had to create two or it does some odd stuff
                static float smoothScrollYPositionMouse = yPos;
                float scrollSpeed = 0.10f;

                Vector2 smoothTextPos = { menuPosition.x, smoothScrollYPosition };
                if (controls::cursorVisible)
                {
                    //bool isMouseInOption = (mouseX >= optionLeft && mouseX <= optionRight) && (mouseY >= optionTop && mouseY <= optionBottom);
                    bool isMouseInOption = IsMouseInBounds(menuPosition.x, yPos, optionSize.x, optionSize.y);

                    if (isMouseInOption) {
                        hoveredOption = controls::optionCount;
                        debugHoveredOption = hoveredOption;
                        HUD::_SET_MOUSE_CURSOR_SPRITE(MOUSE_MiddleFinger);

                        if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 237)) {
                            lClickOnMouse = true;
                            controls::currentOption = hoveredOption;
                        }

                        debugMouseDistanceFromOption = 0.0f;
                    }
                    else {
                        debugMouseDistanceFromOption = fabsf(PAD::GET_CONTROL_NORMAL(0, INPUT_CURSOR_Y) - yPos);
                    }

                    debugMouseInOption = isMouseInOption;

                }
                bool isCurrentOption = controls::currentOption == controls::optionCount;
                bool isHoveredOption = hoveredOption == controls::optionCount;



                if (leftText != NULL) {
                    Vector2 leftTextPos = { (menuPosition.x - textOffset.x) + optionOffset.x, yPos - optionSize.y / 2.0f + textOffset.y };
                    draw::Text(leftText, colours::optionText, leftTextPos, { textScale, textScale }, false, false);
                }

                if (centerText != NULL) {
                    Vector2 centerTextPos = { menuPosition.x + optionOffset.x, yPos - optionSize.y / 2.0f + textOffset.y };
                    draw::Text(centerText, colours::optionText, centerTextPos, { textScale, textScale }, true, false);
                }

                if (rightText != NULL) {
                    Vector2 rightTextPos = { ((menuPosition.x + textOffset.x) + rightTextOffset.x) + optionOffset.x, yPos - optionSize.y / 2.0f + textOffset.y };
                    draw::Text(rightText, colours::optionText, rightTextPos, { textScale, textScale }, false, true);
                }

                if (isHoveredOption && controls::cursorVisible)
                {
                    smoothScrollYPositionMouse += (yPos - smoothScrollYPositionMouse) * scrollSpeed;
                    draw::Rect_Center(colours::scrollerColorHover, { menuPosition.x, smoothScrollYPositionMouse }, optionSize);
                }
                if (isCurrentOption) {
                    smoothScrollYPosition += (yPos - smoothScrollYPosition) * scrollSpeed;
                    draw::Rect_Center(colours::scrollerColor, { menuPosition.x, smoothScrollYPosition }, optionSize);


                    if (controls::selectPressed || lClickOnMouse) {
                        return true;
                    }
                }

            }

            return false;
        }

        void SetSpriteOnOption(const std::string& textureDict, const std::string& textureName, Vector2 size, float rotation, Colour color)
        {
            int startOption = (controls::currentOption - 1) / maxOptions * maxOptions + 1;
            int endOption = startOption + maxOptions - 1;

            if (controls::optionCount >= startOption && controls::optionCount <= endOption)
            {
                float yPos = (optionSize.y * (controls::optionCount - startOption + 1) + optionOffset.y) + menuPosition.y;

                Vector2 spritePos = { ((menuPosition.x + textOffset.x) + optionOffset.x) - spriteOffset.x,  yPos - optionSize.y / 2.0f + spriteOffset.y };

                draw::Sprite(textureDict, textureName, spritePos, size, rotation, color);
            }
        }

        void DragMenuWithMouse() {

            EnableMouse();

            float mouseX = PAD::GET_CONTROL_NORMAL(0, INPUT_CURSOR_X);
            float mouseY = PAD::GET_CONTROL_NORMAL(0, INPUT_CURSOR_Y);

            debugMouseCoords = { mouseX, mouseY };

            Vector2 mouseCoords = GetScreenCoords(mouseX, mouseY);

            debugMouseScreenCoords = mouseCoords;


            bool isLeftClickHeld = PAD::IS_DISABLED_CONTROL_PRESSED(0, 237);

            static bool isDragging = false;
            static Vector2 dragOffset = { 0.0f, 0.0f };

            bool isMouseWithinHeader = IsMouseInBounds(menuPosition.x, menuPosition.y, headerSize.x, headerSize.y);

            if (isMouseWithinHeader)
                HUD::_SET_MOUSE_CURSOR_SPRITE(MOUSE_PreGrab);

            if (isMouseWithinHeader && isLeftClickHeld && !isDragging) {


                isDragging = true;
                dragOffset = { mouseX - menuPosition.x, mouseY - menuPosition.y };
            }

            if (isDragging && isLeftClickHeld) {

                HUD::_SET_MOUSE_CURSOR_SPRITE(MOUSE_Grab);

                menuPosition.x = mouseX - dragOffset.x;
                menuPosition.y = mouseY - dragOffset.y;
            }

            if (!isLeftClickHeld) {
                isDragging = false;
            }

            debugIsDragging = isDragging;
            debugDragOffset = dragOffset;
            debugMenuPosition = menuPosition;
        }

        void SetSubTitle(std::string title)
        {
            subTitle = title;
        }

        void Title()
        {

            DragMenuWithMouse();//You can drag the menu to any Pos on the screen
            const char* titleText = "Avi";

            Vector2 titlePos = { menuPosition.x, menuPosition.y };
            draw::Rect_Center(colours::headerRect, titlePos, headerSize);

            Vector2 textPos = { (menuPosition.x + (headerSize.x - headerTextOffset.x)), (menuPosition.y + (headerSize.y - headerTextOffset.y)) };
            draw::Text(titleText, colours::optionText, textPos, { 0.65f, 0.65f }, true, false);

            int startOption = (controls::currentOption - 1) / maxOptions * maxOptions + 1;
            int displayedOptions = controls::optionCount - startOption + 1;
            displayedOptions = (displayedOptions > maxOptions) ? maxOptions : displayedOptions;

            float rectHeight = (optionSize.y * displayedOptions) - (optionOffset.y / 2) + 0.04f;
            float rectYPos = menuPosition.y + 0.02f + rectHeight / 2 - optionSize.y / 2;

            Vector2 rectPos = { menuPosition.x, rectYPos };
            Vector2 rectSize = { optionSize.x, rectHeight };

            draw::Rect_Center(colours::optionRect, rectPos, rectSize);
        }

        void End()
        {
            int currentPage = (controls::currentOption - 1) / maxOptions + 1;
            int startOption = (currentPage - 1) * maxOptions + 1;
            int displayedOptions = controls::optionCount - startOption + 1;
            displayedOptions = (displayedOptions > maxOptions) ? maxOptions : displayedOptions;

            float targetYPosition = (optionSize.y * displayedOptions + optionSize.y + optionOffset.y) + menuPosition.y;

            static float currentYPosition = targetYPosition;
            float speed = 0.1f;
            currentYPosition += (targetYPosition - currentYPosition) * speed;

            Vector2 endPos = { menuPosition.x, currentYPosition };

            draw::Rect_Center(colours::footerRect, endPos, footerSize);

            int totalPages = (controls::optionCount + maxOptions - 1) / maxOptions;
            char footerText[32];
            snprintf(footerText, sizeof(footerText), "Page %d/%d | #%d", currentPage, totalPages, controls::currentOption);
            Vector2 leftTextPos = { menuPosition.x - footerTextOffset.x, endPos.y - optionSize.y / 2.0f + footerTextOffset.y };
            draw::Text(("v2.0 | " + subTitle).c_str(), colours::optionText, leftTextPos, { textScale, textScale }, false, false);

            Vector2 rightTextPos = { menuPosition.x + footerTextOffset.x, endPos.y - optionSize.y / 2.0f + footerTextOffset.y };
            draw::Text(footerText, colours::optionText, rightTextPos, { textScale, textScale }, false, true);
        }





        void SaveSettings()
        {
            using namespace colours;
            using namespace core::inihandler;
            const std::string iniFile = "Avi\\Avi.ini";

            // Save float settings
            WriteFloatToIni(menuPosition.x, iniFile, "Menu", "MenuPositionX");
            WriteFloatToIni(menuPosition.y, iniFile, "Menu", "MenuPositionY");
            WriteFloatToIni(optionSize.x, iniFile, "Menu", "OptionSizeX");
            WriteFloatToIni(optionSize.y, iniFile, "Menu", "OptionSizeY");
            WriteFloatToIni(optionOffset.x, iniFile, "Menu", "OptionOffsetX");
            WriteFloatToIni(optionOffset.y, iniFile, "Menu", "OptionOffsetY");
            WriteFloatToIni(headerSize.x, iniFile, "Menu", "HeaderSizeX");
            WriteFloatToIni(headerSize.y, iniFile, "Menu", "HeaderSizeY");
            WriteFloatToIni(headerTextOffset.x, iniFile, "Menu", "HeaderTextOffsetX");
            WriteFloatToIni(headerTextOffset.y, iniFile, "Menu", "HeaderTextOffsetY");
            WriteFloatToIni(footerSize.x, iniFile, "Menu", "FooterSizeX");
            WriteFloatToIni(footerSize.y, iniFile, "Menu", "FooterSizeY");
            WriteFloatToIni(textOffset.x, iniFile, "Menu", "TextOffsetX");
            WriteFloatToIni(textOffset.y, iniFile, "Menu", "TextOffsetY");
            WriteFloatToIni(rightTextOffset.x, iniFile, "Menu", "RightTextOffsetX");
            WriteFloatToIni(rightTextOffset.y, iniFile, "Menu", "RightTextOffsetY");
            WriteFloatToIni(footerTextOffset.x, iniFile, "Menu", "FooterTextOffsetX");
            WriteFloatToIni(footerTextOffset.y, iniFile, "Menu", "FooterTextOffsetY");
            WriteFloatToIni(spriteOffset.x, iniFile, "Menu", "SpriteOffsetX");
            WriteFloatToIni(spriteOffset.y, iniFile, "Menu", "SpriteOffsetY");
            WriteFloatToIni(scrollerY, iniFile, "Menu", "ScrollerY");
            WriteFloatToIni(scrollerSpeed, iniFile, "Menu", "ScrollerSpeed");
            WriteFloatToIni(textScale, iniFile, "Menu", "TextScale");

            // Save color settings (convert color components to int and save)
            WriteIntToIni(optionText.r, iniFile, "Color", "OptionTextR");
            WriteIntToIni(optionText.g, iniFile, "Color", "OptionTextG");
            WriteIntToIni(optionText.b, iniFile, "Color", "OptionTextB");
            WriteIntToIni(optionText.a, iniFile, "Color", "OptionTextA");

            WriteIntToIni(optionRect.r, iniFile, "Color", "OptionRectR");
            WriteIntToIni(optionRect.g, iniFile, "Color", "OptionRectG");
            WriteIntToIni(optionRect.b, iniFile, "Color", "OptionRectB");
            WriteIntToIni(optionRect.a, iniFile, "Color", "OptionRectA");

            WriteIntToIni(scrollerColor.r, iniFile, "Color", "ScrollerColorR");
            WriteIntToIni(scrollerColor.g, iniFile, "Color", "ScrollerColorG");
            WriteIntToIni(scrollerColor.b, iniFile, "Color", "ScrollerColorB");
            WriteIntToIni(scrollerColor.a, iniFile, "Color", "ScrollerColorA");

            WriteIntToIni(scrollerColorHover.r, iniFile, "Color", "ScrollerColorHoverR");
            WriteIntToIni(scrollerColorHover.g, iniFile, "Color", "ScrollerColorHoverG");
            WriteIntToIni(scrollerColorHover.b, iniFile, "Color", "ScrollerColorHoverB");
            WriteIntToIni(scrollerColorHover.a, iniFile, "Color", "ScrollerColorHoverA");

            WriteIntToIni(hoverColor.r, iniFile, "Color", "HoverColorR");
            WriteIntToIni(hoverColor.g, iniFile, "Color", "HoverColorG");
            WriteIntToIni(hoverColor.b, iniFile, "Color", "HoverColorB");
            WriteIntToIni(hoverColor.a, iniFile, "Color", "HoverColorA");

            WriteIntToIni(toggleOff.r, iniFile, "Color", "ToggleOffR");
            WriteIntToIni(toggleOff.g, iniFile, "Color", "ToggleOffG");
            WriteIntToIni(toggleOff.b, iniFile, "Color", "ToggleOffB");
            WriteIntToIni(toggleOff.a, iniFile, "Color", "ToggleOffA");

            WriteIntToIni(toggleOn.r, iniFile, "Color", "ToggleOnR");
            WriteIntToIni(toggleOn.g, iniFile, "Color", "ToggleOnG");
            WriteIntToIni(toggleOn.b, iniFile, "Color", "ToggleOnB");
            WriteIntToIni(toggleOn.a, iniFile, "Color", "ToggleOnA");

            WriteIntToIni(footerRect.r, iniFile, "Color", "FooterRectR");
            WriteIntToIni(footerRect.g, iniFile, "Color", "FooterRectG");
            WriteIntToIni(footerRect.b, iniFile, "Color", "FooterRectB");
            WriteIntToIni(footerRect.a, iniFile, "Color", "FooterRectA");

            WriteIntToIni(headerRect.r, iniFile, "Color", "HeaderRectR");
            WriteIntToIni(headerRect.g, iniFile, "Color", "HeaderRectG");
            WriteIntToIni(headerRect.b, iniFile, "Color", "HeaderRectB");
            WriteIntToIni(headerRect.a, iniFile, "Color", "HeaderRectA");
        }


        void LoadSettings()
        {

            if (!onLoad) return;

            using namespace colours;
            using namespace core::inihandler;
            namespace fs = std::filesystem;


            const std::string iniFile = "Avi\\Avi.ini";
            if (fs::exists(iniFile) && fs::is_regular_file(iniFile))
            {
                // Load float settings
                menuPosition.x = ReadFloatFromIni(iniFile, "Menu", "MenuPositionX");
                menuPosition.y = ReadFloatFromIni(iniFile, "Menu", "MenuPositionY");
                optionSize.x = ReadFloatFromIni(iniFile, "Menu", "OptionSizeX");
                optionSize.y = ReadFloatFromIni(iniFile, "Menu", "OptionSizeY");
                optionOffset.x = ReadFloatFromIni(iniFile, "Menu", "OptionOffsetX");
                optionOffset.y = ReadFloatFromIni(iniFile, "Menu", "OptionOffsetY");
                headerSize.x = ReadFloatFromIni(iniFile, "Menu", "HeaderSizeX");
                headerSize.y = ReadFloatFromIni(iniFile, "Menu", "HeaderSizeY");
                headerTextOffset.x = ReadFloatFromIni(iniFile, "Menu", "HeaderTextOffsetX");
                headerTextOffset.y = ReadFloatFromIni(iniFile, "Menu", "HeaderTextOffsetY");
                footerSize.x = ReadFloatFromIni(iniFile, "Menu", "FooterSizeX");
                footerSize.y = ReadFloatFromIni(iniFile, "Menu", "FooterSizeY");
                textOffset.x = ReadFloatFromIni(iniFile, "Menu", "TextOffsetX");
                textOffset.y = ReadFloatFromIni(iniFile, "Menu", "TextOffsetY");
                rightTextOffset.x = ReadFloatFromIni(iniFile, "Menu", "RightTextOffsetX");
                rightTextOffset.y = ReadFloatFromIni(iniFile, "Menu", "RightTextOffsetY");
                footerTextOffset.x = ReadFloatFromIni(iniFile, "Menu", "FooterTextOffsetX");
                footerTextOffset.y = ReadFloatFromIni(iniFile, "Menu", "FooterTextOffsetY");
                spriteOffset.x = ReadFloatFromIni(iniFile, "Menu", "SpriteOffsetX");
                spriteOffset.y = ReadFloatFromIni(iniFile, "Menu", "SpriteOffsetY");
                scrollerY = ReadFloatFromIni(iniFile, "Menu", "ScrollerY");
                scrollerSpeed = ReadFloatFromIni(iniFile, "Menu", "ScrollerSpeed");
                textScale = ReadFloatFromIni(iniFile, "Menu", "TextScale");

                // Load color settings
                optionText = {
                    ReadIntFromIni(iniFile, "Color", "OptionTextR"),
                    ReadIntFromIni(iniFile, "Color", "OptionTextG"),
                    ReadIntFromIni(iniFile, "Color", "OptionTextB"),
                    ReadIntFromIni(iniFile, "Color", "OptionTextA")
                };

                optionRect = {
                    ReadIntFromIni(iniFile, "Color", "OptionRectR"),
                    ReadIntFromIni(iniFile, "Color", "OptionRectG"),
                    ReadIntFromIni(iniFile, "Color", "OptionRectB"),
                    ReadIntFromIni(iniFile, "Color", "OptionRectA")
                };

                scrollerColor = {
                    ReadIntFromIni(iniFile, "Color", "ScrollerColorR"),
                    ReadIntFromIni(iniFile, "Color", "ScrollerColorG"),
                    ReadIntFromIni(iniFile, "Color", "ScrollerColorB"),
                    ReadIntFromIni(iniFile, "Color", "ScrollerColorA")
                };

                scrollerColorHover = {
                    ReadIntFromIni(iniFile, "Color", "ScrollerColorHoverR"),
                    ReadIntFromIni(iniFile, "Color", "ScrollerColorHoverG"),
                    ReadIntFromIni(iniFile, "Color", "ScrollerColorHoverB"),
                    ReadIntFromIni(iniFile, "Color", "ScrollerColorHoverA")
                };

                hoverColor = {
                    ReadIntFromIni(iniFile, "Color", "HoverColorR"),
                    ReadIntFromIni(iniFile, "Color", "HoverColorG"),
                    ReadIntFromIni(iniFile, "Color", "HoverColorB"),
                    ReadIntFromIni(iniFile, "Color", "HoverColorA")
                };

                toggleOff = {
                    ReadIntFromIni(iniFile, "Color", "ToggleOffR"),
                    ReadIntFromIni(iniFile, "Color", "ToggleOffG"),
                    ReadIntFromIni(iniFile, "Color", "ToggleOffB"),
                    ReadIntFromIni(iniFile, "Color", "ToggleOffA")
                };

                toggleOn = {
                    ReadIntFromIni(iniFile, "Color", "ToggleOnR"),
                    ReadIntFromIni(iniFile, "Color", "ToggleOnG"),
                    ReadIntFromIni(iniFile, "Color", "ToggleOnB"),
                    ReadIntFromIni(iniFile, "Color", "ToggleOnA")
                };

                footerRect = {
                    ReadIntFromIni(iniFile, "Color", "FooterRectR"),
                    ReadIntFromIni(iniFile, "Color", "FooterRectG"),
                    ReadIntFromIni(iniFile, "Color", "FooterRectB"),
                    ReadIntFromIni(iniFile, "Color", "FooterRectA")
                };

                headerRect = {
                    ReadIntFromIni(iniFile, "Color", "HeaderRectR"),
                    ReadIntFromIni(iniFile, "Color", "HeaderRectG"),
                    ReadIntFromIni(iniFile, "Color", "HeaderRectB"),
                    ReadIntFromIni(iniFile, "Color", "HeaderRectA")
                };
                LOG << "Loaded Settings config";
                onLoad = false;
            }
        }




        void DebugMenuView()
        {
            if(buttons::Option("Save Settings"))
                SaveSettings();

            // Menu Position
            buttons::Float("Menu Position X", &menuPosition.x, 0.0f, 2.5f, .05f);
            buttons::Float("Menu Position Y", &menuPosition.y, 0.0f, 2.5f, .05f);
            buttons::Float("Option Size X", &optionSize.x, 0.0f, 2.5f, .05f);
            buttons::Float("Option Size Y", &optionSize.y, 0.0f, 2.5f, .05f);
            buttons::Float("Option Offset X", &optionOffset.x, 0.0f, 2.5f, .05f);
            buttons::Float("Option Offset Y", &optionOffset.y, 0.0f, 2.5f, .05f);
            buttons::Float("Header Size X", &headerSize.x, 0.0f, 2.5f, .05f);
            buttons::Float("Header Size Y", &headerSize.y, 0.0f, 2.5f, .05f);
            buttons::Float("Header Text Offset X", &headerTextOffset.x, 0.0f, 2.5f, .05f);
            buttons::Float("Header Text Offset Y", &headerTextOffset.y, 0.0f, 2.5f, .05f);
            buttons::Float("Footer Size X", &footerSize.x, 0.0f, 2.5f, .05f);
            buttons::Float("Footer Size Y", &footerSize.y, 0.0f, 2.5f, .05f);
            buttons::Float("Text Offset X", &textOffset.x, 0.0f, 2.5f, .05f);
            buttons::Float("Text Offset Y", &textOffset.y, 0.0f, 2.5f, .05f);
            buttons::Float("Right Text Offset X", &rightTextOffset.x, 0.0f, 2.5f, .05f);
            buttons::Float("Right Text Offset Y", &rightTextOffset.y, 0.0f, 2.5f, .05f);
            buttons::Float("Footer Text Offset X", &footerTextOffset.x, 0.0f, 2.5f, .05f);
            buttons::Float("Footer Text Offset Y", &footerTextOffset.y, 0.0f, 2.5f, .05f);
            buttons::Float("Sprite Offset X", &spriteOffset.x, 0.0f, 2.5f, .05f);
            GUI::menu::SetSpriteOnOption("commonmenu", "common_medal", { 0.015f, 0.025f }, 1.f, Colour(255, 255, 255, 255));
            buttons::Float("Sprite Offset Y", &spriteOffset.y, 0.0f, 2.5f, .05f);
            GUI::menu::SetSpriteOnOption("commonmenu", "arrowright", { 0.015f, 0.025f }, 1.f, Colour(255, 255, 255, 255));
            // Scroller
            buttons::Float("Scroller Y", &scrollerY, 0.0f, 2.5f, .05f);
            buttons::Float("Scroller Speed", &scrollerSpeed, 0.0f, 2.5f, .05f);
            buttons::Float("Text Scale", &textScale, 0.0f, 2.5f, .05f);

            
        }

        void DebugMenu()
        {
            ImGui::Begin("Adjustment Debug Menu");

            // Menu Position
            ImGui::DragFloat("Menu Position X", &menuPosition.x, 0.0001f, 0.0f, 1.0f, "%.4f");
            ImGui::DragFloat("Menu Position Y", &menuPosition.y, 0.0001f, 0.0f, 1.0f, "%.4f");
            ImGui::DragFloat("Option Size X", &optionSize.x, 0.0001f, 0.0f, 1.0f, "%.4f");
            ImGui::DragFloat("Option Size Y", &optionSize.y, 0.0001f, 0.0f, 1.0f, "%.4f");
            ImGui::DragFloat("Option Offset X", &optionOffset.x, 0.0001f, 0.0f, 1.0f, "%.4f");
            ImGui::DragFloat("Option Offset Y", &optionOffset.y, 0.0001f, 0.0f, 1.0f, "%.4f");
            ImGui::DragFloat("Header Size X", &headerSize.x, 0.0001f, 0.0f, 1.0f, "%.4f");
            ImGui::DragFloat("Header Size Y", &headerSize.y, 0.0001f, 0.0f, 1.0f, "%.4f");
            ImGui::DragFloat("Header Text Offset X", &headerTextOffset.x, 0.0001f, 0.0f, 1.0f, "%.4f");
            ImGui::DragFloat("Header Text Offset Y", &headerTextOffset.y, 0.0001f, 0.0f, 1.0f, "%.4f");
            ImGui::DragFloat("Footer Size X", &footerSize.x, 0.0001f, 0.0f, 1.0f, "%.4f");
            ImGui::DragFloat("Footer Size Y", &footerSize.y, 0.0001f, 0.0f, 1.0f, "%.4f");
            ImGui::DragFloat("Text Offset X", &textOffset.x, 0.0001f, 0.0f, 1.0f, "%.4f");
            ImGui::DragFloat("Text Offset Y", &textOffset.y, 0.0001f, 0.0f, 1.0f, "%.4f");
            ImGui::DragFloat("Right Text Offset X", &rightTextOffset.x, 0.0001f, 0.0f, 1.0f, "%.4f");
            ImGui::DragFloat("Right Text Offset Y", &rightTextOffset.y, 0.0001f, 0.0f, 1.0f, "%.4f");
            ImGui::DragFloat("Footer Text Offset X", &footerTextOffset.x, 0.0001f, 0.0f, 1.0f, "%.4f");
            ImGui::DragFloat("Footer Text Offset Y", &footerTextOffset.y, 0.0001f, 0.0f, 1.0f, "%.4f");
            ImGui::DragFloat("Sprite Offset X", &spriteOffset.x, 0.0001f, -1.0f, 1.0f, "%.4f");
            ImGui::DragFloat("Sprite Offset Y", &spriteOffset.y, 0.0001f, -1.0f, 1.0f, "%.4f");

            // Scroller
            ImGui::DragFloat("Scroller Y", &scrollerY, 0.0001f, 0.0f, 1.0f, "%.4f");
            ImGui::DragFloat("Scroller Speed", &scrollerSpeed, 0.0001f, 0.0f, 1.0f, "%.4f");
            ImGui::DragFloat("Text Scale", &textScale, 0.0001f, 0.0f, 1.0f, "%.4f");

            ImGui::End();

            // Start the ImGui window
            ImGui::Begin("Mouse Coordinates Debug");

            ImGui::Text("Mouse Position (Normalized):");
            ImGui::Text("X: %.4f, Y: %.4f", debugMouseCoords.x, debugMouseCoords.y);

            ImGui::Text("Mouse Position (Screen):");
            ImGui::Text("X: %.2f, Y: %.2f", debugMouseScreenCoords.x, debugMouseScreenCoords.y);

            ImGui::Text("Is Dragging: %s", debugIsDragging ? "True" : "False");

            ImGui::Text("Drag Offset:");
            ImGui::Text("X: %.2f, Y: %.2f", debugDragOffset.x, debugDragOffset.y);

            ImGui::Text("Menu Position:");
            ImGui::Text("X: %.2f, Y: %.2f", debugMenuPosition.x, debugMenuPosition.y);
            ImGui::Separator();
            ImGui::Text("Mouse Option Debug:");
            ImGui::Text("Mouse in Option: %s", debugMouseInOption ? "Yes" : "No");
            ImGui::Text("Hovered Option: %d", debugHoveredOption);
            ImGui::Text("Mouse Distance from Option: %.4f", debugMouseDistanceFromOption);

            // End the ImGui window
            ImGui::End();
        }
    }//Menu
}//GUI


            //ImGui::Separator();
            //ImGui::Text("Tool Box Debug");
            //ImGui::DragFloat("Square Position X", &squarePosition.x, 0.0001f, 0.0f, 1.0f, "%.4f");
            //ImGui::DragFloat("Square Position Y", &squarePosition.y, 0.0001f, 0.0f, 1.0f, "%.4f");
            //ImGui::DragFloat("Square Size X", &squareSize.x, 0.0001f, 0.0f, 1.0f, "%.4f");
            //ImGui::DragFloat("Square Size Y", &squareSize.y, 0.0001f, 0.0f, 1.0f, "%.4f");
            //ImGui::DragFloat("Square Growth", &squareGrowth, 0.0001f, 0.0f, 1.0f, "%.4f");
            //ImGui::DragFloat("Square Offset X", &squareoffset.x, 0.0001f, 0.0f, 1.0f, "%.4f");
            //ImGui::DragFloat("Square Offset Y", &squareoffset.y, 0.0001f, 0.0f, 3.0f, "%.4f");
            //ImGui::DragFloat("Sprite Size X", &spriteSize.x, 0.0001f, 0.0f, 1.0f, "%.4f");
            //ImGui::DragFloat("Sprite Size Y", &spriteSize.y, 0.0001f, 0.0f, 3.0f, "%.4f");
            //ImGui::DragFloat("Info Rect Position X", &infoRectOffset.x, 0.0001f, 0.0f, 1.0f, "%.4f");
            //ImGui::DragFloat("Info Rect Position Y", &infoRectOffset.y, 0.0001f, 0.0f, 3.0f, "%.4f");
            //
            //ImGui::DragFloat("Text Info Position X", &squareTextPosition.x, 0.0001f, 0.0f, 1.0f, "%.4f");
            //ImGui::DragFloat("Text Info Position Y", &squareTextPosition.y, 0.0001f, 0.0f, 3.0f, "%.4f");
            //ImGui::DragFloat("Text Offset Info Position X", &textOffsetInfo.x, 0.0001f, 0.0f, 1.0f, "%.4f");
            //ImGui::DragFloat("Text Offset Inf Position Y", &textOffsetInfo.y, 0.0001f, 0.0f, 3.0f, "%.4f");
            //ImGui::DragFloat("Spacing From Top Info", &ySpacingFromTopInfo, 0.0001f, 0.0f, 1.0f, "%.4f");

// Was trying to create those lil boxes Rampage has in their trainer 
/*
   Vector2 squarePosition = { 0.99f, 0.f };
        Vector2 squareTextPosition = { squarePosition.x, squarePosition.y };
        Vector2 squareSize = { 0.022f, 0.034f };
        Vector2 spriteSize = { 0.014f, 0.025f };
        Vector2 squareoffset = { 0.f, 1.2f };
        Vector2 infoRectOffset = { 0.1245f, 0.1027f };  // X and Y offset for the rectangle

        Vector2 textOffsetInfo = { 0.02f, 0.015f };  // X and Y offsets for positioning the text
        float ySpacingFromTopInfo = 0.025f;           // Y spacing from the top of the rectangle
        float ySpacingPerLineInfo = 0.03f;            // Y spacing between each line
        float gapLeftToCenterInfo;  // Horizontal gap between left and center text
        float gapRightToCenterInfo; // Horizontal gap between right and center text


        float squareGrowth = 0.001f;

        // Variables to track click and growth
        int activeSquare = -1;          // Track the active square (currently growing)
        float growthAmount = 0.0f;      // Amount the rectangle has grown
        float maxGrowthSize = 0.2f;     // Maximum size the rectangle can grow to
        float growthSpeed = 0.005f;     // Speed at which the rectangle grows
        bool isClosing = false;         // Whether the rectangle is closing

        bool debugMouseInSquare = false;


        void DrawSquareWithSprite(const std::string& textureDict, const std::string& textureName, float rotation, Colour color, int count) {
            // Get the current mouse position (normalized)
            float mouseX = PAD::GET_CONTROL_NORMAL(0, INPUT_CURSOR_X);
            float mouseY = PAD::GET_CONTROL_NORMAL(0, INPUT_CURSOR_Y);

            // Variables to store the modified size if the mouse is within bounds
            Vector2 modifiedSquareSize = squareSize;

            // Adjust the Y-position based on the count to space each square vertically
            float adjustedYPosition = squarePosition.y + (count * squareSize.y * squareoffset.y);

            // Check if the mouse is within the square's bounds
            bool isMouseInSquare = IsMouseInBounds(squarePosition.x, adjustedYPosition, squareSize.x, squareSize.y);

            if (isMouseInSquare) {
                // Increase the width and height slightly when the mouse is inside
                modifiedSquareSize.x += squareGrowth;
                modifiedSquareSize.y += squareGrowth;
                debugMouseInSquare = true;

                // Handle click behavior for toggling open/close
                if (PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, 237)) {
                    if (activeSquare == count) {
                        // If the clicked square is already open, start closing it
                        isClosing = true;
                        INFO("Clicked to close");
                    }
                    else {
                        // If a different square is clicked, reset and open the new one
                        activeSquare = count;
                        isClosing = false;  // Don't set closing since we are opening a new square
                        growthAmount = 0.0f;  // Reset growth for the new square
                        INFO("Clicked to open");
                    }
                }
            }
            else {
                debugMouseInSquare = false;
            }

            // Calculate the top-left corner of the square based on the position and size
            Vector2 topLeftPos = { squarePosition.x - modifiedSquareSize.x / 2, adjustedYPosition - modifiedSquareSize.y / 2 };

            // Draw the square (using a rectangle to represent the square)
            draw::Rect({ 0, 0, 0, 150 }, topLeftPos, modifiedSquareSize);

            // Draw the sprite in the center of the square
            Vector2 spritePos = { squarePosition.x, adjustedYPosition };  // Center the sprite within the square
            draw::Sprite(textureDict, textureName, spritePos, spriteSize, rotation, color);

            // Handle the rectangle growth and closing logic
            if (activeSquare == count) {
                if (isClosing) {
                    // Close the rectangle
                    if (growthAmount > 0) {
                        growthAmount -= growthSpeed;  // Decrease the size gradually
                    }
                    else {
                        isClosing = false;  // Fully closed, stop closing
                        activeSquare = -1;  // Reset activeSquare to indicate no square is open
                    }
                }
                else {
                    // Open the new rectangle
                    if (growthAmount < maxGrowthSize) {
                        growthAmount += growthSpeed;  // Increase the size gradually
                    }
                }

                // Calculate the position and size of the growing rectangle
                Vector2 growthPos = { squarePosition.x - (squareSize.x / 2) - growthAmount / 2 - infoRectOffset.x,
                                     adjustedYPosition - (squareSize.y / 2) - growthAmount / 2 + infoRectOffset.y };
                Vector2 growthSize = { squareSize.x + growthAmount, squareSize.y + growthAmount };

                // Draw the expanding rectangle
                draw::Rect({ 0, 0, 0, 255 }, growthPos, growthSize);  // Example color and transparency
            }
        }

        void SetTextOptionInfoBox(int count, const char* LText, int line) {
            // Get the top-left Y-position from the opened rectangle of DrawSquareWithSprite
            float adjustedYPosition = squarePosition.y + (count * squareSize.y * squareoffset.y) + ySpacingFromTopInfo;

            // Adjust the Y-position based on the line number and spacing for each line
            float lineYPosition = (adjustedYPosition + (line * ySpacingPerLineInfo)) + textOffsetInfo.y;

            // Calculate positions for left, center, and right text based on the offsets
            Vector2 leftTextPos = { (squareTextPosition.x - textOffsetInfo.x), lineYPosition };

            // Draw left, center, and right text
            if (LText) {
                draw::Text(LText, { 255, 255, 255, 255 }, leftTextPos, { textScale, textScale }, false, false);
            }
        }

*/