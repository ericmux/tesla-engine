#version 410

in vec3 Color;
in vec2 fUV;

out vec4 outColor;

uniform sampler2D spriteTex;

void main(){
    vec4 colSprite = texture(spriteTex,fUV);
    outColor = colSprite;
}
