#include "hzpch.h"

#include "Application.h"

namespace Vipera
{
	int Application::Run()
	{
		mWindow.init();

		MSG msg {};

		mTimer.Reset();

		while(msg.message != WM_QUIT)
		{
			if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				mTimer.Tick();
				if (!mIsPaused)
				{
					CalculateFrameStats();
					UpdateScene(mTimer.DeltaTime());
					DrawScene();
				}
				else
				{
					Sleep(100);
				}
			}
		}
		return (int)msg.wParam;
	}

	void Application::CalculateFrameStats()
	{
		// Code computes the average frames per second, and also the
		// average time it takes to render one frame. These stats
		// are appeneded to the window caption bar.
		static int frameCnt = 0;
		static float timeElapsed = 0.0f;
		frameCnt++;
		// Compute averages over one second period.
		if ((mTimer.TotalTime() - timeElapsed) >= 1.0f)
		{
			float fps = (float)frameCnt; // fps = frameCnt / 1
			float mspf = 1000.0f / fps;
			std::wostringstream outs;
			outs.precision(6);
			outs << mMainWndCaption << L" "
				<< L"FPS: " << fps << L" "
				<< L"Frame Time: " << mspf << L" (ms)";
			SetWindowText(mhMainWnd, outs.str().c_str());
			// Reset for next average.
			frameCnt = 0;
			timeElapsed += 1.0f;
		}
	}
}
