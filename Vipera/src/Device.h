#pragma once

namespace Vipera
{
	class Device
	{
	public:
		enum QualityLevel
		{
			MSAA = 0
		};

		Device();

		bool init();

		virtual ~Device();

		bool checkMultisampleQualityLevel(QualityLevel format);
	};
}