#version 330 core

//Interpolated values from the vertex shaders
in vec2 UV;
vec4 blue = vec4(0.5,1.0,0.0,0.0);

//output data
out vec4 color;

uniform sampler2D grass;
uniform sampler2D stone;

bool rand(vec2 co){
    if(fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453) > 0.5){
		return true;
	} else {
		return false;
	}
}

void main(){
	vec4 colGrass = texture(grass, UV);
	vec4 colStone = texture(stone, UV);

	//color = mix(colGrass, blue, 0.5);
	color = colGrass;
}