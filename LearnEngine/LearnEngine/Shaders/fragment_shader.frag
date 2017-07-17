#version 450 core

in VS_OUT {
	vec2 textureCoordinate;
} FS_IN;


uniform TextureData (std140, binding = 2) {
	sampler2D mainTexture;
} textureData;

out vec4 color;

void main()
{
	color = texture(textureData.mainTexture, FS_IN.textureCoordinate);
}