varying vec2 textureCoord;
varying vec3 position;

void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	textureCoord = gl_MultiTexCoord0.st;


	position = (gl_Vertex * gl_ModelViewMatrix).xyz;

}