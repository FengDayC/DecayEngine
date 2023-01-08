#pragma once
#include "Layer.h"
#include "Core.h"

namespace Decay 
{
	class DECAY_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<S_PTR(Layer)>::iterator begin() { return m_Layer.begin(); }
		std::vector<S_PTR(Layer)>::iterator end() { return m_Layer.end(); }

	private:
		std::vector<S_PTR(Layer)> m_Layer;
		std::vector<S_PTR(Layer)>::iterator m_LayerInsert;
	};
}