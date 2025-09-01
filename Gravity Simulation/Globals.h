#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
// 2D Vertex Shader
constexpr const char* vertexShaderSource2D = R"(
#version 330 core
layout(location = 0) in vec3 aPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
)";

// 2D Fragment Shader
constexpr const char* fragmentShaderSource2D = R"(
#version 330 core
out vec4 FragColor;
void main() {
    FragColor = vec4(0.0, 0.0, 0.0, 1.0); // Black edges
}
)";

// 3D Vertex Shader
constexpr const char* vertexShaderSource3D = R"(
#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

out vec2 vTexCoord;
out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    FragPos = aPos;        // In world space
    Normal = aNormal;      // In world space
    vTexCoord = aTexCoord;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
)";

// 3D Fragment Shader
constexpr const char* fragmentShaderSource3D = R"(
#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 vTexCoord;

out vec4 FragColor;

uniform sampler2D u_Texture;
uniform bool u_UseTexture;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

void main() {
    // Ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    if (u_UseTexture) {
        vec3 textureColor = texture(u_Texture, vTexCoord).rgb;
        vec3 result = (ambient + diffuse + specular) * textureColor;
        FragColor = vec4(result, 1.0);
    } else {
        vec3 result = (ambient + diffuse + specular) * objectColor;
        FragColor = vec4(result, 1.0);
    }
}
)";

GLFWwindow* InitOpenGL();
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void endFrame(GLFWwindow* window);
void terminateOpenGL(GLFWwindow* window);