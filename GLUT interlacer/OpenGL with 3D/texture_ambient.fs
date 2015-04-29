varying vec2 textureCoord;

uniform sampler2D gSampler;

void main()
{
	float ambientIntensity = 0.7; //Constant intensity
	gl_FragColor = texture2D(gSampler, textureCoord.st) * gl_LightSource[0].ambient * ambientIntensity;
}