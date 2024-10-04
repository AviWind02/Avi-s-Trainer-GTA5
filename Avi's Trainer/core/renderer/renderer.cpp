#include "pch.h"
#include "GUI/menu/menu.h"
#include "core/pool/pool.h"

#include <vendor/imgui/imgui.h>
#include <vendor/imgui/imgui_impl_dx11.h>
#include <vendor/imgui/imgui_impl_win32.h>
#include <vendor/imgui/imgui_internal.h>

#define STB_IMAGE_IMPLEMENTATION
#include <vendor/imgui/stb_image.h>

#include "fonts/rubik.hpp"

bool g_ShowDebug = true;
namespace core {
    namespace renderer {
        bool loadOnce = true;

        ImFont* g_rubikFont_15;
        ImFont* g_rubikFont_25;
        ImFont* g_rubikFont_40;

        HWND g_hWnd = nullptr;
        ID3D11Device* g_pd3dDevice = nullptr;
        ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
        bool imgui_initialized = false;


        //Images
        void LoadWeaponTextures() {
            image::LoadImages("Avi\\Textures\\Weapon", image::weaponTextures);
        }

        void LoadVehicleTextures() {
            image::LoadImages("Avi\\Textures\\Vehicle", image::vehicleTextures);
        }

        // Initialize ImGui
        void InitImGui(HWND hwnd, ID3D11Device* device, ID3D11DeviceContext* context)
        {
            if (imgui_initialized) {
                LOG_TAG("DEBUG") << "ImGui already initialized, skipping initialization";
                return;  // Only initialize once
            }

            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO(); (void)io;

            ImGui::StyleColorsDark();
            io.IniFilename = "Avi\\Avi.ini";

            LOG << "Initializing ImGui for DirectX 11";

            // Initialize ImGui for DirectX 11
            if (!ImGui_ImplWin32_Init(hwnd)) {
                LOG_TAG("ERROR") << "Failed to initialize ImGui for Win32";
                return;
            }

            if (!ImGui_ImplDX11_Init(device, context)) {
                LOG_TAG("ERROR") << "Failed to initialize ImGui for DirectX 11";
                return;
            }

            imgui_initialized = true;
            LOG << "ImGui successfully initialized";
        }

        // Shutdown ImGui
        void ShutdownImGui()
        {
            if (!imgui_initialized) {
                LOG_TAG("WARN") << "ImGui not initialized, skipping shutdown";
                return;
            }

            LOG << "Shutting down ImGui";

            // Cleanup ImGui and DirectX resources
            ImGui_ImplDX11_Shutdown();
            ImGui_ImplWin32_Shutdown();
            ImGui::DestroyContext();

            imgui_initialized = false;
            LOG << "ImGui successfully shut down";
        }

        // Update mouse inputs
        void UpdateMouseInputs()
        {
            ImGuiIO& io = ImGui::GetIO();
            io.MouseDown[0] = GetAsyncKeyState(VK_LBUTTON) & 0x8000;
            io.MouseDown[1] = GetAsyncKeyState(VK_RBUTTON) & 0x8000;

        }

        // Render loop
        void OnPresent(IDXGISwapChain* swapChain)
        {
            if (!imgui_initialized)
            {
                DXGI_SWAP_CHAIN_DESC swapChainDesc;
                swapChain->GetDesc(&swapChainDesc);
                g_hWnd = swapChainDesc.OutputWindow;

                HRESULT hr = swapChain->GetDevice(__uuidof(ID3D11Device), (void**)&g_pd3dDevice);
                if (SUCCEEDED(hr))
                {
                    ImFontConfig font_cfg{};
                    font_cfg.FontDataOwnedByAtlas = false;
                    strcpy_s(font_cfg.Name, "Rubik");
                    
                    g_pd3dDevice->GetImmediateContext(&g_pd3dDeviceContext);
                    InitImGui(g_hWnd, g_pd3dDevice, g_pd3dDeviceContext);
                    LOG << "ImGui initialized in OnPresent";

                    g_rubikFont_15 = ImGui::GetIO().Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(font_rubik), sizeof(font_rubik), 15.f, &font_cfg);
                    g_rubikFont_25 = ImGui::GetIO().Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(font_rubik), sizeof(font_rubik), 25.f, &font_cfg);
                    g_rubikFont_40 = ImGui::GetIO().Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(font_rubik), sizeof(font_rubik), 40.f, &font_cfg);

                    
                    Style();
                }
                else
                {
                    LOG_TAG("ERROR") << "Failed to retrieve DirectX device in OnPresent";
                }
            }

            if (GUI::controls::cursorVisible) {
                ImGui::GetIO().MouseDrawCursor = true;
                ImGui::GetIO().ConfigFlags &= ~ImGuiConfigFlags_NoMouse;
            }
            else {
                ImGui::GetIO().MouseDrawCursor = false;
                ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NoMouse;
            }

            UpdateMouseInputs();

            ImGui_ImplDX11_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();
            if (loadOnce)
            {
                std::thread weaponThread(LoadWeaponTextures);
                weaponThread.detach();

                std::thread vehicleThread(LoadVehicleTextures);
                vehicleThread.detach();

                std::cout << "Weapon and Vehicle textures are loading." << std::endl;

                loadOnce = false;
            }
            if (g_ShowDebug)
            {
                Logger_c::DebugWindow::Render();// Log Window
                GUI::menu::DebugMenu();// UI Debug
                core::pool::PoolDebugMenu();
            }

            GUI::draw::DX::ShowWeaponWindow();

            ImGui::Render();
            ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        }

        bool LoadTextureFromFile(const char* filename, ImTextureID out_srv, int* out_width, int* out_height)
        {
            // Load from disk into a raw RGBA buffer
            int image_width = 1920;
            int image_height = 1080;
            unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
            if (image_data == NULL)
                return false;

            // Create texture
            D3D11_TEXTURE2D_DESC desc;
            ZeroMemory(&desc, sizeof(desc));
            desc.Width = image_width;
            desc.Height = image_height;
            desc.MipLevels = 1;
            desc.ArraySize = 1;
            desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
            desc.SampleDesc.Count = 1;
            desc.Usage = D3D11_USAGE_DEFAULT;
            desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
            desc.CPUAccessFlags = 0;

            ID3D11Texture2D* pTexture = NULL;
            D3D11_SUBRESOURCE_DATA subResource;
            subResource.pSysMem = image_data;
            subResource.SysMemPitch = desc.Width * 4;
            subResource.SysMemSlicePitch = 0;
            g_pd3dDevice->CreateTexture2D(&desc, &subResource, &pTexture);

            // Create texture view
            D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
            ZeroMemory(&srvDesc, sizeof(srvDesc));
            srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
            srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
            srvDesc.Texture2D.MipLevels = desc.MipLevels;
            srvDesc.Texture2D.MostDetailedMip = 0;
            g_pd3dDevice->CreateShaderResourceView(pTexture, &srvDesc, (ID3D11ShaderResourceView**)out_srv);
            pTexture->Release();

            *out_width = image_width;
            *out_height = image_height;
            stbi_image_free(image_data);

            return true;
        }

    

    }
}
