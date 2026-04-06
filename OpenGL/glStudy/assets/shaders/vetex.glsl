#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aUV;
out vec3 color;
out vec2 uv;
uniform float time;

//uniform float speed;

//uniform vec3 ucolor; 

void main()
{
   float dx = time * 0.3;
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
   //color = aColor * (cos(time) + 1.0) / 2.0;
   //color = ucolor;
   uv = vec2(aUV.x + dx,aUV.y);
}