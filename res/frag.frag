#version 330 core

in vec3 vertexColor;
in vec2 textureCoord;

out vec4 FragColor;

//uniform vec4 ourColor; // 在OpenGL程序代码中设定这个变量

uniform sampler2D outTexture;

void main() {
//    FragColor = vec4(vertexColor, 1.0f) + ourColor;
    FragColor = texture(outTexture, textureCoord);
}
