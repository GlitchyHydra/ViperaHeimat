#include "hzpch.h"
#include "Window.h"

namespace Vipera
{
    LRESULT WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        switch (message)
        {
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }
        }

        // Handle any messages the switch statement didn't
        return DefWindowProc(hWnd, message, wParam, lParam);
    }


    void Window::init(HINSTANCE hInstance)
    {
        // this struct holds information for the window class
        WNDCLASSEX wc;

        // clear out the window class for use
        ZeroMemory(&wc, sizeof(WNDCLASSEX));

        // fill in the struct with the needed information
        wc.cbSize = sizeof(WNDCLASSEX);
        wc.style = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc = WindowProc;
        wc.hInstance = hInstance;
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        //wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
        wc.lpszClassName = L"WindowClass1";

        // register the window class
        RegisterClassEx(&wc);

        RECT wr{ 0, 0, 500, 400 };
        AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

        // create the window and use the result as the handle
        hWnd = CreateWindowEx(NULL,
            L"WindowClass1",    // name of the window class
            L"Our First Windowed Program",   // title of the window
            WS_OVERLAPPEDWINDOW,    // window style
            300,    // x-position of the window
            300,    // y-position of the window
            wr.right - wr.left,    // width of the window
            wr.bottom - wr.top,    // height of the window
            NULL,    // we have no parent window, NULL
            NULL,    // we aren't using menus, NULL
            hInstance,    // application handle
            NULL);    // used with multiple windows, NULL
    }

}


