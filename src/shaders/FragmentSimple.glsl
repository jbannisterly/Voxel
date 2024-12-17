#version 330

in vec3 frag_pos;
out vec4 FragColor;

void main(){
    FragColor = vec4(0,0,1 / (frag_pos.z + 1),1);
}