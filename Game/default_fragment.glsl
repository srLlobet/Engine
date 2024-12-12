#version 460
out vec4 color;

uniform sampler2D mytexture;

void main()
{
	color = texture2D(mytexture, uv0);
}