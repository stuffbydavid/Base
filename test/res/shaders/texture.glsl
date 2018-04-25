/* Renders using a colored texture */

// Vertex

#version 420 core

in vec3 aPos;
in vec3 aNormal;
in vec2 aTexCoord;
out vec2 vTexCoord;
uniform mat4 uMat;

void main(void)
{
    vTexCoord = aTexCoord;
    gl_Position = uMat * vec4(aPos, 1.0);
}

// Fragment

#version 420 core

in vec2 vTexCoord; 
out vec4 fColor;
uniform sampler2D uSampler;
uniform vec4 uColor;

void main(void)
{
    vec4 col = vec4(0.1, 0.7, 1.0, 1.0);
    gl_FragColor = col * uColor * texture2D(uSampler, vTexCoord);
    //gl_FragColor = vec4(vTexCoord.x, vTexCoord.y, 1.0, 1.0);
}