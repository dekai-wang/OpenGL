#version 330 core

in vec3 vertexColor;

out vec4 FragColor;

uniform vec4 ourColor; // 在OpenGL程序代码中设定这个变量

void main() {
    FragColor = vec4(vertexColor, 1.0f) + ourColor;
}
