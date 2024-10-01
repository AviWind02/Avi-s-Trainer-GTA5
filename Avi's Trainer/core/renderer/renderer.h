#pragma once
namespace core {
    namespace renderer {
        void InitImGui(HWND hwnd, ID3D11Device* device, ID3D11DeviceContext* context);
        void ShutdownImGui();
        void OnPresent(IDXGISwapChain* swapChain);
    }
}