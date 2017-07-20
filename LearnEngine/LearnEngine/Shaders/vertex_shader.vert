#version 450 core

layout (location = 0) in vec3 _position;
layout (location = 1) in vec2 _texCoord;

layout (std140, binding - 0) uniform RenderingSystemData {
	mat4 viewMatrix;
	mat4 perspectiveMatrix;
	vec3 cameraPos;
} systemData;

layout (std140, binding = 1) uniform ModelData { 
	mat4 modelMatrix;
} modelData;

layout (std140, binding = 2) uniform TextureData {
	sampler2D mainTexture;
} textureData;

out VS_OUT {
	vec2 textureCoordinate;
}

void main()
{
	VS_OUT.textureCoordinate = _texCoord;
	gl_Position = systemData.perspectiveMatrix * systemData.viewMatrix * modelData.modelMatrix * vec4(_position, 1.0f);
}