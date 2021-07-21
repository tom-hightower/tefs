#version 330 core
out vec4 FragColor;
in vec3 sColor;

void main() {
    FragColor = vec4(sColor, 1.0);
}