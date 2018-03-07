#version  330 core

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 vTextureCoordinates;

out vec3 fNormal;
out vec2 fTextureCoordinates;
out vec3 fPosition_World;
out vec4 viewSpace;

void main()
{
	viewSpace = V * M * vec4(vPosition, 1.0);
    gl_Position = P * viewSpace; //Move position to VIEW space
    fNormal = (V * M * vec4(vNormal, 0.0)).xyz; //Move normal to WORLD space
    fPosition_World = vPosition; //We need world position for
    
    fTextureCoordinates = vTextureCoordinates;
	
}

