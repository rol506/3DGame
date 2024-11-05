#version 430 core

layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec3 vertexColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 Color;
out vec2 texCoord;

void main()
{
  gl_Position = vec4(vertexPos, 1.0);
  Color = vertexColor;
  texCoord = aTexCoord;
}
