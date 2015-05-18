varying vec3 normal;
varying vec3 position;

//! Vertex shader for use with Phong shading.
void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	//Multiply normal by camera space
	vec4 normal4d = gl_ModelViewMatrix * vec4(gl_Normal, 1.0);
	normal = gl_NormalMatrix * gl_Normal;

	position = (gl_ModelViewMatrix * gl_Vertex).xyz;

}