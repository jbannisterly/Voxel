#version 330

in vec3 frag_pos;
out vec4 FragColor;
uniform sampler2D defer_position;

void main(){
    FragColor = vec4(texture(defer_position, fract(frag_pos.xy * 2)).rgb, 1);
}