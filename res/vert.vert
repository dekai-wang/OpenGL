#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTextureCoord;

out vec3 vertexColor;
out vec2 textureCoord;

uniform mat4 transform;

void main() {
//    gl_Position = vec4(aPosition, 1.0f);
    gl_Position = vec4(aPosition, 1.0f) * transform;
    vertexColor = aColor;
//    textureCoord = aTextureCoord;
    textureCoord = vec2(aTextureCoord.x, aTextureCoord.y);
}
