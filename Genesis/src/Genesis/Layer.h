#pragma once

#include "Genesis/Events/Event.h"

namespace Genesis
{
    /**
     * \brief Base class for layers; gets updated in the game loop according to their order in the LayerStack.
     */
    class GENESIS_API Layer
    {
      public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer();
        /**
         * \brief Called when a layer is added to the layer stack.
         */
        virtual void OnAttach() {}
        /**
         * \brief Called when a layer is removed from the layer stack.
         */
        virtual void OnDetach() {}
        /**
         * \brief Called in game loop according to Layer order in the LayerStack.
         */
        virtual void OnUpdate() {}
        virtual void OnEvent(Event& event) {}
        /**
         * \brief Here you can specify, which ImGui elements you want to draw (called after the ImGui frame is set up)
         */
        virtual void OnImGuiRender() {}

        const std::string& GetName() const { return m_DebugName; }

      protected:
        std::string m_DebugName;
    };
}  // namespace Genesis