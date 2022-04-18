#version 330 core
out vec4 fragColor;

/* in vec2 v_texCoord; */
in vec3 v_normal;
in vec3 v_fragPos;
in vec3 v_viewPos;

float rand(float n){return fract(sin(n) * 43758.5453123);}

float noise(float p){
    float fl = floor(p);
  float fc = fract(p);
    return mix(rand(fl), rand(fl + 1.0), fc);
}

void main()
{

    vec3 dif_color = vec3(0,
        .1,
        1.);

    vec3 norm = normalize(v_normal);
    vec3 light = vec3(0,50,55);

    vec3 lightDir = normalize(light-v_fragPos);

    float dif = max(0.,dot(norm,lightDir));

    vec3 viewDir = normalize(v_viewPos - v_fragPos);
    vec3 reflectDir = reflect(-lightDir, norm); 

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 128.);

    vec3 col = .05
    + dif_color * dif * .5
    + vec3(1) * spec * .3;

    //col = pow(col,vec3(1./2.2));

    fragColor = vec4(col,1);
}