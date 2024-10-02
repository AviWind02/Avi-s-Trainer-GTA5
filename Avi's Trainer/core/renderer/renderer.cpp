#include "pch.h"

#include "GUI/menu/menu.h"

#include <vendor/imgui/imgui.h>
#include <vendor/imgui/imgui_impl_dx11.h>
#include <vendor/imgui/imgui_impl_win32.h>
#include <vendor/imgui/imgui_internal.h>

bool g_ShowDebug = true;

namespace core {
	namespace renderer {

        HWND g_hWnd = nullptr;
        ID3D11Device* g_pd3dDevice = nullptr;
        ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
        bool imgui_initialized = false;


        void InitImGui(HWND hwnd, ID3D11Device* device, ID3D11DeviceContext* context)
        {
            if (imgui_initialized) return; // Only initialize once

            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO(); (void)io;

            ImGui::StyleColorsDark();
            io.IniFilename = "Avi\\Avi.ini";
            // Initialize ImGui for DirectX 11
            ImGui_ImplWin32_Init(hwnd);
            ImGui_ImplDX11_Init(device, context);

            imgui_initialized = true;
        }

        void ShutdownImGui()
        {
            if (!imgui_initialized) return;

            // Cleanup ImGui and DirectX resources
            ImGui_ImplDX11_Shutdown();
            ImGui_ImplWin32_Shutdown();
            ImGui::DestroyContext();

            imgui_initialized = false;
        }

        void UpdateMouseInputs()// Updates the Mouse clicks
        {
            ImGuiIO& io = ImGui::GetIO();
            io.MouseDown[0] = GetAsyncKeyState(VK_LBUTTON) & 0x8000;
            io.MouseDown[1] = GetAsyncKeyState(VK_RBUTTON) & 0x8000;
        }

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
                    g_pd3dDevice->GetImmediateContext(&g_pd3dDeviceContext);
                    InitImGui(g_hWnd, g_pd3dDevice, g_pd3dDeviceContext);


                }
            }

            if (1) {
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
            ///////////////////
            
            if (g_ShowDebug)
            {
                Logger_c::DebugWindow::Render();//Log Window
                GUI::menu::DebugMenu();//UI Debug
            }

            ///////////////////
            ImGui::Render();
            ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
        }

	}
}