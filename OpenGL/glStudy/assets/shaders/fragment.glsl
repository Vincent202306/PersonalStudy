#version 460 core
//in vec3 color;
in vec2 uv;
out vec4 FragColor;
//uniform float time;
uniform sampler2D sampler;
void main()
{
   //float intensity = (sin(time) + 1.0) / 2.0;
   FragColor = texture(sampler,uv);
   //FragColor = vec4(vec3(intensity) + color, 1.0f);
   //FragColor = vec4(color * (sin(time) + 1.0) / 2.0, 1.0);
}