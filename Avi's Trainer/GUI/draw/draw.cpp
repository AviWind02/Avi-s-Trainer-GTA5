#include "pch.h"
#include "draw.h"

#define M_PI 3.14159265358979323846 

//This is the draw file
//These methods are used for drawing in game natively 

namespace GUI {
    namespace draw {


        void Text(const char* text, Colour color, Vector2 position, Vector2 size, bool center, bool rightAlign) {
            if (center) {
                HUD::SET_TEXT_CENTRE(true);
            }
            if (rightAlign) {
                HUD::SET_TEXT_RIGHT_JUSTIFY(true);
                HUD::SET_TEXT_WRAP(0.0f, position.x);
            }

            HUD::SET_TEXT_COLOUR(color.r, color.g, color.b, color.a);
            HUD::SET_TEXT_FONT(0);
            HUD::SET_TEXT_SCALE(size.x, size.y);
            HUD::SET_TEXT_DROPSHADOW(1, 0, 0, 0, 0);
            HUD::SET_TEXT_EDGE(1, 0, 0, 0, 0);
            HUD::SET_TEXT_OUTLINE();
            HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
            HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME((char*)text);
            HUD::END_TEXT_COMMAND_DISPLAY_TEXT(position.x, position.y, NULL);
        }

        void Rect(Colour color, Vector2 position, Vector2 size) {// Creates the Rect from top left
            Vector2 centerPos = Vector2(position.x + size.x / 2, position.y + size.y / 2);
            GRAPHICS::DRAW_RECT(centerPos.x, centerPos.y, size.x, size.y, color.r, color.g, color.b, color.a, NULL);
        }

        void Rect_Center(Colour color, Vector2 position, Vector2 size) {//This is main used in the UI
            GRAPHICS::DRAW_RECT(position.x, position.y, size.x, size.y, color.r, color.g, color.b, color.a, NULL);
        }

        void Sprite(const std::string& textureDict, const std::string& textureName, Vector2 position, Vector2 size, float rotation, Colour color) {//Can draw UI elements from the game files
            if (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED((char*)textureDict.c_str())) {
                GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT((char*)textureDict.c_str(), false);
            }
            else {
                GRAPHICS::DRAW_SPRITE((char*)textureDict.c_str(), (char*)textureName.c_str(), position.x, position.y, size.x, size.y, rotation, color.r, color.g, color.b, color.a, NULL);
            }
        }

        void Line(Vector2 start, Vector2 end, Colour color) {
            GRAPHICS::DRAW_LINE(start.x, start.y, 0.0f, end.x, end.y, 0.0f, color.r, color.g, color.b, color.a);
        }

        void Circle(Vector2 center, float radius, int segments, Colour color) {
            float angleStep = 2.0f * M_PI / segments;
            for (int i = 0; i < segments; ++i) {
                float angle1 = i * angleStep;
                float angle2 = (i + 1) * angleStep;
                Vector2 point1 = { center.x + radius * cosf(angle1), center.y + radius * sinf(angle1) };
                Vector2 point2 = { center.x + radius * cosf(angle2), center.y + radius * sinf(angle2) };
                Line(point1, point2, color);
            }
        }

        void FilledCircle(Vector2 center, float radius, int segments, Colour color) {
            for (int i = 0; i < segments; i++) {
                float angle1 = (i * 2.0f * M_PI) / segments;
                float angle2 = ((i + 1) * 2.0f * M_PI) / segments;

                Vector2 point1 = { center.x + radius * cosf(angle1), center.y + radius * sinf(angle1) };
                Vector2 point2 = { center.x + radius * cosf(angle2), center.y + radius * sinf(angle2) };

                GRAPHICS::DRAW_POLY(center.x, center.y, 0.0f, point1.x, point1.y, 0.0f, point2.x, point2.y, 0.0f, color.r, color.g, color.b, color.a);
            }
        }
    }
}
