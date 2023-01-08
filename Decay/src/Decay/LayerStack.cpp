#include "dcpch.h"
#include "LayerStack.h"

namespace Decay
{
	LayerStack::LayerStack()
	{
		m_LayerInsert = m_Layer.begin();
	}

	LayerStack::~LayerStack()
	{
		m_Layer.clear();
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_LayerInsert = m_Layer.emplace(m_LayerInsert, std::shared_ptr<Layer>(layer));
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layer.emplace_back(std::shared_ptr<Layer>(overlay));
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layer.begin(), m_Layer.end(), std::shared_ptr<Layer>(layer));
		if (it != m_Layer.end())
		{
			m_Layer.erase(it);
			m_LayerInsert--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_Layer.begin(), m_Layer.end(), std::shared_ptr<Layer>(overlay));
		if (it != m_Layer.end())
		{
			m_Layer.erase(it);
		}
	}
}