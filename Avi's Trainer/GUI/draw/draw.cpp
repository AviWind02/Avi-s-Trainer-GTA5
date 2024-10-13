#include "pch.h"
#include "draw.h"

#include <vendor/imgui/imgui.h>

#include "app/feature/weapons/weaponclub/weaponclub.h"
#include "app/feature/vehicle/vehicleshop/vehicleshop.h"

#define M_PI 3.14159265358979323846f

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

        namespace DX {//Move these later or make them in native tbh

            const float windowSizeX = 375.0f;

            void RenderStatBar(const char* label, float value)
            {
                ImGui::Text("%s: %.2f", label, value);
                ImGui::SameLine();
                
                float fullBarWidth = 200.0f;
                float fullWindowWidth = windowSizeX - 10.f;
                float labelWidth = ImGui::CalcTextSize(label).x + 80.0f;
                float barStartX = fullWindowWidth - fullBarWidth;


                ImGui::SetCursorPosX(barStartX);

                ImGui::ProgressBar(value / 100.0f, ImVec2(fullBarWidth, 10.0f), ""); 
            }



            void ShowWeaponWindow()
            {
                const ImVec2 windowSize(windowSizeX, 250.0f);

                if (!feature::weapon::weaponclub::weaponsdataonoption::showDisplay) return;//Switch to Case

                ImGui::SetNextWindowSize(windowSize, ImGuiCond_Always);

                ImGui::Begin("Weapon Stats", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDecoration);

                ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(feature::weapon::weaponclub::weaponsdataonoption::displayName.c_str()).x) * 0.5f);
                ImGui::Text(feature::weapon::weaponclub::weaponsdataonoption::displayName.c_str());
                ImGui::Separator();
                for (auto image : core::renderer::image::weaponTextures)
                {
                    if (image.fileName == ToLowerCase(feature::weapon::weaponclub::weaponsdataonoption::hashstring))
                    {
                        if (image.Texture)
                        {
                            ImVec2 imageSize = ImVec2(164, 64);
                            ImGui::SetCursorPosX((ImGui::GetWindowSize().x - imageSize.x) * 0.5f);
                            ImGui::Image((void*)(intptr_t)image.Texture, imageSize);
                        }
                    } 
                }

                for (auto weapon : feature::weapon::weaponclub::g_weaponList)
                {
                    if (weapon.hashstring == feature::weapon::weaponclub::weaponsdataonoption::hashstring)
                    {
                        RenderStatBar("Damage", weapon.damage);
                        RenderStatBar("Speed", weapon.speed);
                        RenderStatBar("Capacity", weapon.capacity);
                        RenderStatBar("Accuracy", weapon.accuracy);
                        RenderStatBar("Range", weapon.hudrange);
                    }
                }

                ImGui::End();
            }

            void ShowVehicleShopwWindow()
            {
                const ImVec2 windowSize(windowSizeX, 150.0f);

                if (controls::currentSubMenu == pages::VehicleShop_PickedMod_page || controls::currentSubMenu == pages::VehicleShop_page)
                {
                    ImGui::SetNextWindowSize(windowSize, ImGuiCond_Always);

                    ImGui::Begin("Vehicle Specifications", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDecoration);

                    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("Vehicle Specifications").x) * 0.5f);
                    ImGui::Text("Vehicle Specifications");

                    if (feature::vehicleshop::Spec.has_value())
                    {
                        auto& spec = feature::vehicleshop::Spec.value();

                        ImGui::Text("Top Speed KPH %.1f", spec.maxSpeed * 3.6);
                        RenderStatBar("Max Speed m/s", spec.maxSpeed);
                        RenderStatBar("Max Braking", spec.maxBraking * 50);
                        RenderStatBar("Max Acceleration", spec.maxAcceleration * 50);
                        RenderStatBar("Max Traction", spec.maxTraction * 25);
                    }

                    ImGui::End();
                }
            }
        }
    }
}
