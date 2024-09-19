#version 330 core

layout(location = 0) in vec3 a_position;

out vec3 fregColor;
uniform float u_pointSize;
uniform vec3 u_color;
uniform mat4 mvp_matrix;

void main()
{
    gl_Position = mvp_matrix * vec4(a_position, 1.0);
    gl_PointSize = u_pointSize;
    fregColor = u_color;
}
