/*!
	@class TextureNormalShader
	Vertex Shader: Transforms the tangent vector (passed in via a gl_Color pointer)
	into world space.
*/

varying vec2 textureCoord;
varying vec3 normal;
varying vec3 position;
varying vec3 tangent;

//! A vertex shader for normal mapping. 
/*!
	Transforms the tangent vector (passed in via a gl_Color pointer)
	into world space.
*/
void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	textureCoord = gl_MultiTexCoord0.st;
	//Multiply normal by world space
	normal = gl_NormalMatrix * gl_Normal;
	tangent = (gl_NormalMatrix * gl_Color.xyz); //Tangent given by glColor pointer
	position = (gl_ModelViewMatrix * gl_Vertex).xyz;

}