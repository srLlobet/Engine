#version 460

out vec4 color;

in vec2 uv0;

layout(binding=5) uniform sampler2D mytexture;

uniform vec4 baseColorFactor; // Base color factor (RGBA)
uniform float metallicFactor; // Metallic factor

//uniform float roughnessFactor; // Roughness factor

void main()
{
	vec4 texColor = texture2D(mytexture, uv0);

	vec4 finalColor = texColor * baseColorFactor;

	color = baseColorFactor;
}