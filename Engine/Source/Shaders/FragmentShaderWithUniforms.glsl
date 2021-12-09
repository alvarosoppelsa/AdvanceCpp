#version 330 core

out vec4 color;
out vec4 shade;
in vec2 uv0;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;

void main()
{
	color = texture2D(texture_diffuse1, uv0);
	shade = texture2D(texture_diffuse2, uv0);
}