#version  410 core
layout(location = 0) in vec4 vertPos;
layout(location = 1) in vec3 vertNor;
layout(location = 2) in vec2 vertTex;

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
uniform vec2 offset;
uniform float w;

out vec3 fragNor;
out vec2 fragTex;
out vec3 T;
out vec3 B;
out vec3 N;
out vec4 tpos;

uniform sampler2D tex;
uniform sampler2D normal;
const float amplitude = 0.12f;
const float phi = 0.002f;
const float steepness = 0.3f;
const float num_waves = 3;
const float frequency = .01f;
vec3 wavePosition1 = vec3(20,0,10);
vec3 wavePosition2 = vec3(-20, 0, 5);
vec3 wavePosition3 = vec3(0, 0, 5);
void main()
{
    
    vec2 texcoord = vertTex + offset;
    tpos = vertPos;
    vec4 npos = vertPos;
    //Working is below. 
    //tpos.z += .3*sin(.2*tpos.x + w/50) + .2*cos(.5*tpos.y + w/50);
    //Height function: Sum of (Ai x sin(D_i * (x,y)) x w_i + t*phi)
    for(int i = 0; i < num_waves; i++){
	tpos.z += amplitude * sin(dot(wavePosition1.xz, vec2(tpos.x, tpos.z))*frequency + w*phi);
	npos.z += frequency * wavePosition1.x * amplitude * cos(dot(wavePosition1.xz, vec2(tpos.x, tpos.z))*frequency + w*phi);
    }
    //calculate normals
    vec3 b = vec3(1, 0, npos.z);
    vec3 t = vec3(0, 1, npos.z);
    vec3 n = cross(b, t);
    B = normalize(vec3(M * vec4(b,  0.0)));
    T = normalize(vec3(M * vec4(t, 0.0)));
    N = normalize(vec3(M * vec4(n, 0.0)));
    mat3 TBN = mat3(T,B,N);
    
    
    gl_Position = P * V * M * tpos;
    
    //fragNor = (M * vec4(vertNor, 0.0)).xyz;
    fragTex = texcoord;
    
}
