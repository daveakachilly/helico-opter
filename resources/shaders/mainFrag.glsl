#version 330 core

in vec3 fNormal;
in vec2 fTextureCoordinates;
in vec3 fPosition_World;
in vec4 viewSpace;

//to send the color to a frame buffer
layout(location = 0) out vec4 color;

uniform sampler2D Texture0;

uniform vec3 eyePosition;
uniform vec3 directionTowardsLight;

uniform vec3 mDiffusionCoefficient;
uniform vec3 mAmbientCoefficient;
uniform vec3 mSpecularCoefficient;
uniform float mSpecularAlpha;

uniform int fogSelector;
uniform int depthFog;

const vec3 fogColor = vec3(0.5, 0.5, 0.5);
const float FogDensity = 0.05;

/* Very simple Diffuse shader with a directional light*/
void main()
{
    vec3 directionTowardsEye = normalize(eyePosition - fPosition_World); // L
    
    vec3 L = normalize(directionTowardsLight);
    vec3 N = normalize(fNormal);
    vec3 H = normalize(directionTowardsLight + directionTowardsEye);
    
    vec3 lightColor = vec3(0.0f);
    
    lightColor += mAmbientCoefficient;
    lightColor += mDiffusionCoefficient * clamp(dot(L, N), 0.0, 1.0);
    lightColor += mSpecularCoefficient * pow( clamp(dot(H, N), 0.0, 1.0), mSpecularAlpha);
    
	vec3 mixedColor = vec3(0, 0, 0);

    float dist = 0;
    float fogFactor = 0;
 
	if(depthFog == 0)//select plane based vs range based
	{
		dist = abs(viewSpace.z);
	}
	else
	{
	   dist = length(viewSpace);
	}
 
	if(fogSelector == 0)//linear fog
	{
	   fogFactor = (80 - dist)/(80 - 20);
	   fogFactor = clamp( fogFactor, 0.0, 1.0 );
	   mixedColor = mix(fogColor, lightColor, fogFactor);
	}
	else if( fogSelector == 1)// exponential fog
	{
		fogFactor = 1.0 /exp(dist * FogDensity);
		fogFactor = clamp( fogFactor, 0.0, 1.0 );
		mixedColor = mix(fogColor, lightColor, fogFactor);
	}
	else if( fogSelector == 2)
	{
		fogFactor = 1.0 /exp( (dist * FogDensity)* (dist * FogDensity));
		fogFactor = clamp( fogFactor, 0.0, 1.0 );
		mixedColor = mix(fogColor, lightColor, fogFactor);
	}
	vec4 fog_tex = texture(Texture0, fTextureCoordinates);
    color = mix(vec4(lightColor, 1.0), fog_tex, 0.75);
    //color = vec4(fNormal, 1.0);
    vec4 textureColor = texture(Texture0, fTextureCoordinates);
    //color = 0.5 * (color+textureColor);
}
