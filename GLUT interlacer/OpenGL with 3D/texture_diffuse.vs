varying vec2 textureCoord;
varying vec3 normal;

void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	textureCoord = gl_MultiTexCoord0.st;
	//Multiply normal by camera space
	vec4 normal4d = vec4(gl_Normal, 1.0) * gl_ModelViewMatrix;
	normal = normal4d.xyz;

	

}