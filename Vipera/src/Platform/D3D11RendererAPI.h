#pragma once

namespace Platform
{
	class D3D11RendererAPI
	{
	public:
		void init();
		void cleanup();

		void render_indices();
		void render_line();
	};
}