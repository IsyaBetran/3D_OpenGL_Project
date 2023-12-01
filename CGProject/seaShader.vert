#version 330 core
layout (location = 0) in vec3 aPos;
uniform float time;
out vec3 FragPos;

void main() {
    vec3 pos = aPos;
    pos.z = sin(pos.x * 10.0 + time) * 0.1 * sin(pos.y * 10.0 + time);
    FragPos = pos;
    gl_Position = vec4(pos, 1.0);
}
