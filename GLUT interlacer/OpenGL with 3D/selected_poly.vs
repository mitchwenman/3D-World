varying vec2 textureCoord;
varying vec3 normal;
varying vec3 position;

void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	textureCoord = gl_MultiTexCoord0.st;
	//Multiply normal by camera space
	vec4 normal4d = gl_ModelViewMatrix * vec4(gl_Normal, 1.0);
	normal = gl_NormalMatrix * gl_Normal;

	position = (gl_ModelViewMatrix * gl_Vertex).xyz;

}