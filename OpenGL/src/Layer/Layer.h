#pragma once
#include <string>


namespace Vipera
{
	class Layer
	{
	public:
		virtual ~Layer() = default;

		Layer(const std::string name)
			: m_Name(name)
		{ }

		virtual void Begin() const = 0;
		virtual void End() const = 0;
		virtual void Render() const = 0;

		inline const std::string& GetName() const { return m_Name; }

	protected:
		std::string m_Name;
	};
}
