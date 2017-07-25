#version 450 core

in VS_OUT {
	vec2 textureCoordinate;
} FS_IN;

layout (binding = 0) uniform sampler2D mainTexture;

out vec4 color;

void main()
{
	color = texture(mainTexture, FS_IN.textureCoordinate);
}