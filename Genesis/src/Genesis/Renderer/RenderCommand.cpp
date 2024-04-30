#include "gspch.h"
#include "RenderCommand.h"
#include "Genesis/Platform/OpenGL/OpenGLRendererAPI.h"

namespace Genesis
{
    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}