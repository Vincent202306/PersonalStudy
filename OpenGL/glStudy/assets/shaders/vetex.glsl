#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
out vec3 color;
uniform float time;

uniform float speed;
void main()
{
   float dx = sin(time * speed) * 0.3;
   gl_Position = vec4(aPos.x + dx, aPos.y, aPos.z, 1.0);
   color = aColor * (cos(time) + 1.0) / 2.0;
}