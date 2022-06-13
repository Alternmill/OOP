#version 330 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Colors
layout (location = 1) in vec3 aColor;

// Outputs the color for the Fragment Shader
out vec3 color;

uniform float isOn;

void main()
{
	gl_Position = vec4(aPos, 1.0);
	color = vec3(aColor.x*isOn,aColor.y*isOn,aColor.z*isOn);
}