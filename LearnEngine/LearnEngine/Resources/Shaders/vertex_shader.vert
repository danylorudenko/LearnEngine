#version 450 core

//////////////////////////////////////////////////
// Conventional uniforms which are binded to shader by every (GLObject : IGLTransfromable)
//////////////////////////////////////////////////

layout (std140, binding = 0) uniform RenderingSystemData {
	mat4 viewMatrix;
	mat4 perspectiveMatrix;
	vec3 cameraPos;
	vec3 cameraRot;
} systemData;

layout (std140, binding = 1) uniform ModelData { 
	mat4 modelMatrix;
} modelData;

layout (binding = 0) uniform sampler2D mainTexture;

//////////////////////////////////////////////////
// Vertex attributes inputs
//////////////////////////////////////////////////

layout (location = 0) in vec3 _vertex_position;
layout (location = 1) in vec2 _texCoord;


//////////////////////////////////////////////////
// Vertex outputs
//////////////////////////////////////////////////

out VS_OUT {
	vec2 textureCoordinate;
} vs_out;

void main()
{
	vs_out.textureCoordinate = _texCoord;
	gl_Position = systemData.perspectiveMatrix * systemData.viewMatrix * modelData.modelMatrix * vec4(_vertex_position, 1.0f);
}