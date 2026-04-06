#version 460 core
//in vec3 color;
in vec2 uv;
out vec4 FragColor;
//uniform float time;
uniform sampler2D grassSampler;
uniform sampler2D landSampler;
uniform sampler2D noiseSampler;

void main()
{
   //float intensity = (sin(time) + 1.0) / 2.0;
   vec4 grassColor = texture(grassSampler,uv);
   vec4 landColor = texture(landSampler,uv);
   vec4 noiseColor = texture(noiseSampler,uv);
   FragColor = mix(grassColor,landColor,noiseColor.x);
   //FragColor = vec4(vec3(intensity) + color, 1.0f);
   //FragColor = vec4(color * (sin(time) + 1.0) / 2.0, 1.0);
}