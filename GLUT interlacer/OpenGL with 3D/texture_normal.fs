varying vec2 textureCoord;
varying vec3 position;

uniform sampler2D gSampler; //The texture
uniform sampler2D normSampler; //The normal map
uniform vec3 lightDirection;

void main()
{
	float ambientIntensity = 0.5; //Constant intensity
	vec4 ambientColour = gl_LightSource[0].ambient * ambientIntensity;
	
	//Calculate diffuse and specular
	vec4 diffuse = vec4(0.0, 0.0, 0.0, 0.0);
	vec4 specular = vec4(0.0, 0.0, 0.0, 0.0);

	vec3 lightDir = (vec4(lightDirection, 1.0) * gl_ModelViewMatrix).xyz;

	//Get normal from normal map
	vec3 nMapValue = texture2D(normSampler, textureCoord).rgb * 2.0 - 1.0;
	vec3 nMapCamSpace = vec4(nMapValue, 1.0) * gl_ModelViewMatrix;
	vec3 normal = normalize(nMapValue);

	float diffuse_intensity = dot(normalize(normal), normalize(lightDir));
	if (diffuse_intensity > 0.0)
	{
		diffuse += gl_LightSource[0].diffuse * diffuse_intensity;

		//No specular if diffuse intensity is 0
		
		vec3 nLightDir = normalize(lightDirection);
		vec3 nNorm = normalize(normal);
		vec3 lightReflection = normalize(reflect(nLightDir, nNorm));
		vec3 vertEye = normalize(-position); //Vector from pixel to eye at (0,0,0)
		float shininess = 4.0;
		float specularIntensity = max(0.0, pow(dot(vertEye, lightReflection), shininess)); //Negative angle shouldn't see specular
		specular += gl_LightSource[0].specular * specularIntensity;

	}
	
	gl_FragColor = texture2D(gSampler, textureCoord) * (specular + diffuse + ambientColour);

}