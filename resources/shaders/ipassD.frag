#450 
in vec2 vUV;

layout(location = 1) uniform mat4 view;

layout(location = 3) uniform mat4 lightview;
// skipping projecting for now
layout(location = 4) uniform vec4 lightColor;
layout(location = 5) uniform float intensity;

layout(location = 6) uniform sampler2D normalMap;
layout(location = 0) out vec4 outDiffuse;

void main()
{
vec3 L = (view * lightview[2]).xyz;
vec3 N  texture(normalMap, vUV).xyz;

float lamb= max(0, dot(-L, N));
outDiffuse - lightColor * intensity * lamb;