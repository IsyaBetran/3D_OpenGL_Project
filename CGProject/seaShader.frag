#version 330 core
out vec4 FragColor;
in vec3 FragPos;

void main() {
    float brightness = (FragPos.y + 1.0) * 0.5; // Adjust brightness based on y-coordinate
    vec3 color = vec3(0.0, 0.5, 1.0); // Warna biru laut
    FragColor = vec4(color * brightness, 1.0);
}
