#pragma once
#include <vendor/imgui/imgui.h>//Might be an issue return back later

namespace core {
    namespace renderer {

        void InitImGui(HWND hwnd, ID3D11Device* device, ID3D11DeviceContext* context);
        void ShutdownImGui();
        void OnPresent(IDXGISwapChain* swapChain);
        bool LoadTextureFromFile(const char* filename, ImTextureID out_srv, int* out_width, int* out_height);
        void Style();
        namespace image
        {
            struct dximage {
                ID3D11ShaderResourceView* Texture;
                std::string fileName;
            };

            inline std::vector<dximage> vehicleTextures;
            inline std::vector<dximage> weaponTextures;

            bool IsValidImageExtension(const std::string& extension);
            void LoadImages(const std::string& directoryPath, std::vector<dximage>& imageResources);
        }
    }
}