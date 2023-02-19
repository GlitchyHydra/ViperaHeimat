#pragma once

#include <vector>
#include "Layer/Layer.h"

namespace Vipera {
	
	class LayerStack
	{
	public:
		LayerStack() {}
		~LayerStack();

		void PushLayer(Vipera::Layer* layer);
		void PopLayer(Vipera::Layer* layer);

		std::vector<Vipera::Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Vipera::Layer*>::iterator end() { return m_Layers.end(); }
	private:
		std::vector<Vipera::Layer*> m_Layers;
	};

}

