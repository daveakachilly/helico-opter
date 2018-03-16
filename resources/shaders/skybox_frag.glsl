#version 330 core

in vec3 texcoords;
uniform samplerCube cube_texture;
out vec4 frag_colour;
in vec4 viewSpace;
uniform int fogSelector;
uniform int depthFog;

const vec3 fogColor = vec3(0.5, 0.5, 0.5);
const float FogDensity = 0.025;

void main() {
  frag_colour = texture(cube_texture, texcoords);
  vec3 skyColor = frag_colour.rgb;
  vec3 mixedColor = vec3(0, 0, 0);

	//distance
    float dist = 0;
    float fogFactor = 0;
 
    //compute distance used in fog equations
	if(depthFog == 0)//select plane based vs range based
	{
		//plane based
		dist = abs(viewSpace.z);
		//dist = (gl_FragCoord.z / gl_FragCoord.w);
	}
	else
	{
	   //range based
	   dist = length(viewSpace);
	}
 
	if(fogSelector == 0)//linear fog
	{
	   // 20 - fog starts; 80 - fog ends
	   fogFactor = (80 - dist)/(80 - 20);
	   fogFactor = clamp( fogFactor, 0.0, 1.0 );
 
	   //if you inverse color in glsl mix function you have to
	   //put 1.0 - fogFactor
	   mixedColor = mix(fogColor, skyColor, fogFactor);
	}
	else if( fogSelector == 1)// exponential fog
	{
		fogFactor = 1.0 /exp(dist * FogDensity);
		fogFactor = clamp( fogFactor, 0.0, 1.0 );
 
		// mix function fogColor?(1?fogFactor) + lightColor?fogFactor
		mixedColor = mix(fogColor, skyColor, fogFactor);
	}
	else if( fogSelector == 2)
	{
		fogFactor = 1.0 /exp( (dist * FogDensity)* (dist * FogDensity));
		fogFactor = clamp( fogFactor, 0.0, 1.0 );
		mixedColor = mix(fogColor, skyColor, fogFactor);
	}
	frag_colour = vec4(mixedColor, 1.0);
}