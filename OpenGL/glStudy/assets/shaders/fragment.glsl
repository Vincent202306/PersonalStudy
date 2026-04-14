#version 460 core
in vec2 uv;
out vec4 FragColor;
uniform float width;
uniform float height;
uniform sampler2D goKuSampler;

void main()
{
   vec2 location = uv * vec2(width, height);
   vec2 dx = dFdx(location);
   vec2 dy = dFdy(location);

   float deltaLen = sqrt(max(dot(dx,dx),dot(dy,dy)));

   float L = log2(deltaLen);						
   L= int(L + 0.5);
   FragColor = textureLod(goKuSampler,uv,L);
}