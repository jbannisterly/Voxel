#version 330

in vec3 frag_pos;
out vec4 FragColor;

void main(){
    FragColor = vec4(frag_pos, 1);
}