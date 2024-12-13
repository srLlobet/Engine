#version 460
<<<<<<< HEAD
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 vertex_uv0;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
=======
layout(location=0) in vec3 my_vertex_position;
layout(location = 1) in vec2 vertex_uv0;
>>>>>>> test

out vec2 uv0;

out vec2 uv0;

void main()
{
<<<<<<< HEAD
	gl_Position = projection * view * model * vec4(position, 1.0);
=======
	gl_Position = projection * view * model * vec4(my_vertex_position, 1.0);
>>>>>>> test
	uv0 = vertex_uv0;
}