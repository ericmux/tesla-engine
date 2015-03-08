#version 410

in vec2 position;
in vec4 color;
in vec2 vUV;

out vec4 Color;
out vec2 fUV;

void main(){
    Color = color;
    fUV = vec2(vUV.x, 1.0 - vUV.y);
    gl_Position = vec4(position, 0.0, 1.0);

}


