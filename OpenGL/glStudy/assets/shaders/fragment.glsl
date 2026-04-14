#version 460 core
in vec2 uv;
out vec4 FragColor;
uniform float width;
uniform float height;
uniform sampler2D goKuSampler;

void main()
{
   FragColor = texture(goKuSampler,uv);
}