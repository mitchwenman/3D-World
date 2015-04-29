varying vec2 textureCoord;

uniform sampler2D gSampler;

void main()
{
	gl_FragColor = texture2D(gSampler, textureCoord.st);
}