#version 330

layout(location = 0) in vec3 pos;
out vec3 frag_pos;

void main(){
    gl_Position = vec4(pos, 1);
    frag_pos = pos;
}