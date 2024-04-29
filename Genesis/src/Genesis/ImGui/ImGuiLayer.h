#pragma once

#include "Genesis/Events/ApplicationEvent.h"
#include "Genesis/Events/KeyEvent.h"
#include "Genesis/Events/MouseEvent.h"
#include "Genesis/Layer.h"

namespace Genesis
{
    class GENESIS_API ImGuiLayer : public Layer
    {
      public:
        ImGuiLayer();
        virtual ~ImGuiLayer();

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnImGuiRender() override;

        void Begin();
        void End();

      private:
        float m_Time = 0.0f;
    };
}  // namespace Genesis
