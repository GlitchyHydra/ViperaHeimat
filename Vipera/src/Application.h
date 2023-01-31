#pragma once

#include "GameTimer.h"
#include "Window.h"

namespace Vipera
{
	class Application
	{

	public:
		Application();

		int Run();

	private:

		void CalculateFrameStats();

		Window mWindow;
		GameTimer mTimer;

	};
}

