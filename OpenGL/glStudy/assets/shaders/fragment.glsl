#version 460 core
in vec3 color;
out vec4 FragColor;
uniform float time;
void main()
{
   float intensity = (sin(time) + 1.0) / 2.0;
   FragColor = vec4(vec3(intensity) + color, 1.0f);
   //FragColor = vec4(color * (sin(time) + 1.0) / 2.0, 1.0);
}