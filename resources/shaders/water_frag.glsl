#version 330 core
uniform sampler2D Texture0;
uniform sampler2D normal;

//in vec3 fragNor;
in vec2 fragTex;
in float dCo;
in vec3 T;
in vec3 B;
in vec3 N;
uniform float w;
in vec4 tpos;
out vec4 color;

void main() {
    //vec4 texColor0 = texture(Texture0, vTexCoord);
    vec4 diffuse = texture(Texture0, fragTex);
    //w/50 lets the normal walk. 
    vec3 normal = texture(normal, fragTex+w/50).rgb;
    //light position
    vec3 lp = vec3(100,100,100);
    //position of wave. 
    vec3 pos = tpos.xyz;
    //light direction
    vec3 ld = normalize(lp-pos);
    //camera position is stable at x = 1 and z = 5.0 however max y value is 20. 
    vec3 camPos = vec3(1.0, 20.0, 5.0);
    //calculating the surface normal here. 
    vec3 bumpNormal = vec3((normal.x * T) +  (normal.y*N) + (normal.z * B));
    //light coefficient. 
    float light = dot(ld, bumpNormal);
    //nice base magenta color
    vec4 baseColor = vec4(.282,.239,.545, 0);
    //camera position and light vector calculations for half vector. 
    camPos = camPos - pos;
    camPos = normalize(camPos);
    vec3 lightV = light*vec3(1,1,1);
    lightV = normalize(lightV);
    vec3 h = camPos + light*vec3(1,1,1);
    //get half angle vector for phong
    h = normalize(camPos + ld);
    float specular;
    //calculate specular. 
    specular = dot(h, bumpNormal);
    specular = pow(specular,1.0);
    specular = clamp(specular, 0.0, 1.0);
    color = baseColor;
    color += vec4(1,1,1,0) * specular;
    
    
    //DEBUG:Outcolor = vec4(vTexCoord.s, vTexCoord.t, 0, 1);
}

