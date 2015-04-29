varying vec2 textureCoord;
varying vec3 normal;

uniform sampler2D gSampler;
uniform vec3 lightDirection;

void main()
{
	float ambientIntensity = 0.7; //Constant intensity
	vec4 ambientColour = gl_LightSource[0].ambient * ambientIntensity;
	
	//Calculate diffuse
	vec4 diffuse = vec4(0.0, 0.0, 0.0, 0.0);


	vec3 lightDir = (vec4(lightDirection, 1.0) * gl_ModelViewMatrix).xyz;

	float diffuse_intensity = dot(normalize(normal), lightDir);
	if (diffuse_intensity > 0.0)
	{
		diffuse += gl_LightSource[0].diffuse * diffuse_intensity;
	}
	
	gl_FragColor = texture2D(gSampler, textureCoord) * (diffuse + ambientColour);

}