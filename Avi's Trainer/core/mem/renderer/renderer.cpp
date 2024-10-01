#include "pch.h"

//IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


namespace core {
	namespace renderer {

		//Renderer& Renderer::get() {
		//	static Renderer instance;
		//	return instance;
		//}

		//void Renderer::initialize() {
		//	void* d3d_device{};

		//	if (SUCCEEDED(m_dxgi_swapchain->GetDevice(__uuidof(ID3D11Device), &d3d_device))) {
		//		m_d3d_device.Attach(static_cast<ID3D11Device*>(d3d_device));
		//	}
		//	else {
		//		throw std::runtime_error("Failed to get D3D device.");
		//	}

		//	m_d3d_device->GetImmediateContext(m_d3d_device_context.GetAddressOf());

		//	ImGuiContext* ctx = ImGui::CreateContext();

		//	ImGui_ImplDX11_Init(m_d3d_device.Get(), m_d3d_device_context.Get());
		//	ImGui_ImplWin32_Init(pointers::g_window);

		//}

		//void Renderer::free() {
		//	ImGui_ImplWin32_Shutdown();
		//	ImGui_ImplDX11_Shutdown();
		//	ImGui::DestroyContext();
		//}

		//void Renderer::on_present() {
		//	ImGui_ImplDX11_NewFrame();
		//	ImGui_ImplWin32_NewFrame();
		//	ImGui::NewFrame();
		//	//////////////////

		//	

		//	/////////////////
		//	ImGui::Render();
		//	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		//}

		//void Renderer::pre_reset() {
		//	ImGui_ImplDX11_InvalidateDeviceObjects();
		//}

		//void Renderer::post_reset() {
		//	ImGui_ImplDX11_CreateDeviceObjects();
		//}

		//void Renderer::wnd_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
		//	ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam);
		//}

		//void Renderer::text(
		//	const char* text,
		//	float pos_x,
		//	float pos_y,
		//	ImColor& color,
		//	ImFont* font
		//)
		//{
		//	ImGui::PushFont(font);
		//	ImGui::GetCurrentWindow()->DrawList->AddText(
		//		ImVec2(pos_x, pos_y),
		//		color,
		//		text
		//	);
		//	ImGui::PopFont();
		//}

		//void Renderer::rect(
		//	float pos_x,
		//	float pos_y,
		//	float size_x, float size_y, ImColor color)
		//{
		//	ImRect rect(
		//		ImVec2(pos_x, pos_y),
		//		add_vectors(ImVec2(pos_x, pos_y),
		//			ImGui::CalcItemSize(ImVec2(size_x, size_y),
		//				0.0f,
		//				0.0f
		//			)
		//		)
		//	);

		//	ImGui::GetCurrentWindow()->DrawList->AddRectFilled(rect.Max, rect.Min, color);
		//}

		//void Renderer::texture(
		//	ImTextureID texture,
		//	float pos_x,
		//	float pos_y,
		//	float size_x,
		//	float size_y,
		//	ImColor& color
		//)
		//{
		//	const ImVec2 pos = ImGui::GetCursorScreenPos();
		//	ImGui::SetCursorPos(ImVec2(pos_x, pos_y));

		//	ImGui::Image(
		//		texture,
		//		ImVec2(size_x, size_y),
		//		ImVec2(0, 0),
		//		ImVec2(1, 1),
		//		color
		//	);

		//	ImGui::SetCursorPos(pos);
		//}

		//ImVec2 Renderer::center_text(
		//	const std::string& text,
		//	const float rect_x,
		//	const float rect_y,
		//	const float rect_width,
		//	const float rect_height,
		//	const float font_size,
		//	const Alignment align
		//)
		//{
		//	const ImFont* font = ImGui::GetFont();
		//	const ImVec2 text_size = font->CalcTextSizeA(font_size, FLT_MAX, 0, text.c_str());
		//	float x{};
		//	float y{};

		//	switch (align)
		//	{
		//	case Alignment::Left:
		//		x = rect_x;
		//		break;
		//	case Alignment::Center:
		//		x = rect_x + (rect_width - text_size.x) / 2;
		//		break;
		//	case Alignment::Right:
		//		x = rect_x + rect_width - text_size.x;
		//		break;
		//	}

		//	y = rect_y + (rect_height - text_size.y) / 2;

		//	return ImVec2(x, y);
		//}

		//ImVec2 Renderer::add_vectors(ImVec2 vector_a, ImVec2 vector_b) {
		//	ImVec2 result{};
		//	result.x = vector_a.x;
		//	result.y = vector_a.y;
		//	result.x += vector_b.x;
		//	result.y += vector_b.y;

		//	return result;
		//}

		//Renderer::Renderer()
		//	: m_dxgi_swapchain(*pointers::g_swap_chain) {}

		//Renderer::~Renderer() {}


	}
}