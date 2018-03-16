#version 330 core
uniform sampler2D Texture0;

//in vec3 fragNor;
in vec2 fragTex;
in float dCo;
out vec4 color;
in vec4 viewSpace;
uniform int fogSelector;
uniform int depthFog;

const vec3 fogColor = vec3(0.5, 0.5, 0.5);
const float FogDensity = 0.05;

void main() {
    //vec4 texColor0 = texture(Texture0, vTexCoord);
    
    //Outcolor = dCo*texColor0;
    color = texture(Texture0, fragTex);
    //float dist = length(pos);
    //float s = dist/50.0;
    //s = pow(s, 5)-0.2;
    //color.a = s;
    
    vec3 waterColor = color.rgb;
    //DEBUG:Outcolor = vec4(vTexCoord.s, vTexCoord.t, 0, 1);
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
	   mixedColor = mix(fogColor, waterColor, fogFactor);
	}
	else if( fogSelector == 1)// exponential fog
	{
		fogFactor = 1.0 /exp(dist * FogDensity);
		fogFactor = clamp( fogFactor, 0.0, 1.0 );
 
		// mix function fogColor?(1?fogFactor) + lightColor?fogFactor
		mixedColor = mix(fogColor, waterColor, fogFactor);
	}
	else if( fogSelector == 2)
	{
		fogFactor = 1.0 /exp( (dist * FogDensity)* (dist * FogDensity));
		fogFactor = clamp( fogFactor, 0.0, 1.0 );
		mixedColor = mix(fogColor, waterColor, fogFactor);
	}
	color = vec4(mixedColor, 1.0);
}

