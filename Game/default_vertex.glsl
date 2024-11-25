#version 460
layout(location=0) in vec3 my_vertex_position;


layout(location = 0) uniform mat4 model;
layout(location = 1) uniform mat4 view;
layout(location = 2) uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(my_vertex_position, 1.0);
}