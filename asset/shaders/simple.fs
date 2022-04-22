#version 330 core
out vec4 fragColor;

in vec3 v_normal;
in vec3 v_fragPos;

uniform vec3 viewPos;
uniform vec3 sunPosition;

void main()
{
    vec3 dif_color = vec3(1,.5,0);

    vec3 norm = normalize(v_normal);

    vec3 lightDir = normalize(sunPosition-v_fragPos);

    vec3 viewDir = normalize(viewPos - v_fragPos);

    float dif = max(0.,dot(norm,lightDir));
    
    vec3 reflectDir = reflect(-lightDir, norm); 

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 128.);

    vec3 col = .05
    + dif_color * dif * .5
    + vec3(1) * spec * .3;

	fragColor = vec4(vec3(1,0,1),1);
}