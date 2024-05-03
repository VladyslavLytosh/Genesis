#shader vertex
#version 460 core

layout(location = 0) in vec3 a_Position;

uniform vec4 u_Color;

out vec4 ourColor;
void main()
{
    gl_Position = vec4(a_Position, 1.0);
    ourColor = u_Color;
}

#shader fragment
#version 460 core

in vec4 ourColor;

out vec4 color;

void main()
{
    color = ourColor;
}