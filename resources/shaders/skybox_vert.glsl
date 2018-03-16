#version 330 core

layout(location = 0) in vec3 vp;
uniform mat4 P, V;
uniform int fogSelector;
uniform int depthFog;
out vec3 texcoords;
out vec4 viewSpace;
void main() {
  mat3 view = mat3(V);
  texcoords = vp;
  viewSpace = V * vec4(vp, 1.0);
  gl_Position = P * mat4(view) * vec4(vp, 1.0);
}