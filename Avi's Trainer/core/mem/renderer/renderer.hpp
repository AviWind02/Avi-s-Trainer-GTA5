#pragma once
#include <pch.h>



namespace core {

	namespace renderer {
	/*	enum class Alignment {
			Left,
			Center,
			Right
		};


		template <typename com>
		using comptr = Microsoft::WRL::ComPtr<com>;

		class Renderer
		{
		public:
			static Renderer& get();

			void initialize();
			void free();

			void on_present();
			void pre_reset();
			void post_reset();

			void wnd_proc(
				HWND hwnd,
				UINT msg,
				WPARAM wparam,
				LPARAM lparam
			);

			void text(
				const char* text,
				float pos_x,
				float pos_y,
				ImColor& color,
				ImFont* font
			);

			void rect(
				float pos_x,
				float pos_y,
				float size_x,
				float size_y,
				ImColor color
			);

			void texture(
				ImTextureID texture,
				float pos_x,
				float pos_y,
				float size_x,
				float size_y,
				ImColor& color
			);

			ImVec2 center_text(
				const std::string& text,
				const float rect_x,
				const float rect_y,
				const float rect_width,
				const float rect_height,
				const float font_size,
				const renderer::Alignment align
			);

			ImVec2 add_vectors(
				ImVec2 vector_a,
				ImVec2 vector_b
			);

		public:
			comptr<IDXGISwapChain> m_dxgi_swapchain;
			comptr<ID3D11Device> m_d3d_device;
			comptr<ID3D11DeviceContext> m_d3d_device_context;
		private:
			Renderer();
			~Renderer();
		};*/
	}
} 