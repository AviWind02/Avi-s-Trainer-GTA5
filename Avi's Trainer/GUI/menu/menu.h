#pragma once
#include "../draw/draw.h"

namespace GUI {
    namespace menu {
        namespace colours
        {
            extern Colour optionText;
            extern Colour optionRect;
            extern Colour scrollerColor;
            extern Colour hoverColor;
            extern Colour toggleOff;
            extern Colour toggleOn;
            extern Colour footerRect;
            extern Colour headerRect;
        }

        extern int maxOption;
        extern Vector2 menuPos;
        extern Vector2 optionSize;
        extern Vector2 optionOffsets;
        extern Vector2 headerSize;
        extern Vector2 headerTextOffset;
        extern Vector2 footerSize;
        extern Vector2 textOffset;
        extern Vector2 rightTextOffset;
        extern Vector2 FootertextOffset;
        extern Vector2 spriteOffset;
        extern float scrollerY;
        extern float scrollerSpeed;
        extern float textScale;
        extern int hoveredOption;

        bool SetOption(const char* leftText, const char* centerText, const char* rightText);
        void SetSpriteOnOption(const std::string& textureDict, const std::string& textureName, Vector2 size, float rotation, Colour color);
        //void SetTextOptionInfoBox(int count, const char* LText, int line);
        //void DrawSquareWithSprite(const std::string& textureDict, const std::string& textureName, float rotation, Colour color, int count);
        void Title();
        void End();

        void SetSubTitle(std::string title);

        void DebugMenu();
        void DebugMenuView();

        void SaveSettings();
        void LoadSettings();
    }
}