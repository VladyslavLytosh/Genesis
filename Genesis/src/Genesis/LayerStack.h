#pragma once

#include "Genesis/Core.h"
#include "Layer.h"

namespace Genesis
{
	/**
	 * \brief Wrapper around a vector of Layers, which defines the order in which the layer update function is called.
	 * \remark Lifetime of layers controlled by LayerStack.
	 */
	class GENESIS_API LayerStack
	{
	public:
		LayerStack();
		virtual ~LayerStack();
		/**
		 * \brief Pushes a layer after the last layer that was pushed.
		 * \param layer Layer to push
		 */
		void PushLayer(Layer* layer);
		/**
		 * \brief Pushes a overlay to the end of the layer stack. (Overlays are always placed after all layers.)
		 * \param overlay Overlay to push
		 */
		void PushOverlay(Layer* overlay);
		/**
		 * \brief Removes a layer from the LayerStack (without deleting it).
		 * \param layer Layer to pop
		 */
		void PopLayer(Layer* layer);
		/**
		 * \brief Removes a overlay from the LayerStack (without deleting it).
		 * \param overlay overlay to pop
		 */
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }

	private:
		std::vector<Layer*> m_Layers;
		// Index of the last pushed layer plus 1 (used to push layers before overlays).
		unsigned int m_LayerInsertIndex = 0; 
	};
}