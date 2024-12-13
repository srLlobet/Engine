#version 460
out vec4 color;

<<<<<<< HEAD
in vec2 uv0;

layout(binding=5) uniform sampler2D mytexture;

void main()
{
	 color = texture2D(mytexture, uv0);
=======
uniform sampler2D mytexture;

void main()
{
	color = texture2D(mytexture, uv0);
>>>>>>> test
}