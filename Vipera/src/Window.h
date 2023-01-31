#pragma once

namespace Vipera
{
	LRESULT WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	class Window
	{
	public:
		struct Rect
		{
			int left, top, right, bottom;
		};

		//Window(Rect& rect);

		void init(HINSTANCE hInstance);
		HWND getHWND() { return hWnd; }

	private:
		// the handle for the window, filled by a function
		HWND hWnd;

	};
}


