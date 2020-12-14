#version 330 core

//Interpolated values from the vertex shaders
in vec2 UV;

//output data
out vec3 color;

uniform sampler2D sampler;

void main(){
	color = texture(sampler, UV).rgb;
}
