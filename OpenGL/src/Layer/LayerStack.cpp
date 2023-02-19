#include "LayerStack.h"

namespace Vipera {
	
	LayerStack::~LayerStack()
	{
		for (Vipera::Layer* layer : m_Layers)
			delete layer;
	}

	void LayerStack::PushLayer(Vipera::Layer* layer)
	{
		m_Layers.emplace_back(layer);
	}

	void LayerStack::PopLayer(Vipera::Layer* layer)
	{
		auto it = std::find(m_Layers.begin(),
			m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			//m_LayerInsertIndex--;
		}
	}
}