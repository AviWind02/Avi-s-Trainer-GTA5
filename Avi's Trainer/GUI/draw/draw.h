#pragma once



namespace GUI {
    namespace draw {



        void FilledCircle(Vector2 center, float radius, int segments, Colour color);
        void Circle(Vector2 center, float radius, int segments, Colour color);
        void Line(Vector2 start, Vector2 end, Colour color);
        void Sprite(const std::string& textureDict, const std::string& textureName, Vector2 position, Vector2 size, float rotation, Colour color);
        void Rect(Colour color, Vector2 position, Vector2 size);
        void Rect_Center(Colour color, Vector2 position, Vector2 size);
        void Text(const char* text, Colour color, Vector2 position, Vector2 size, bool center, bool rightAlign);
        
        namespace DX
        {
            void ShowWeaponWindow();
        }

    }
}