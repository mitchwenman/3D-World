varying vec2 textureCoord;
varying vec3 normal;
varying vec3 position;
varying vec3 tangent;

uniform sampler2D gSampler;
uniform sampler2D gNormalSampler;

uniform vec3 lightDirection;
uniform mat4 gCameraMatrix;

//Transforms the normal map normal into world space
//so it can be used for lighting calculations.
vec3 getNormal()
{
	vec3 ntangent = normalize(tangent);
	vec3 nnormal = normalize(normal);
	ntangent = normalize(ntangent - dot(ntangent, nnormal) * nnormal);
	//Calculate bitangent
	vec3 bitangent = cross(ntangent, nnormal);

	//Get normal map normal and get between -1, 1
	vec3 nMapNormal = vec3(0, 0, 1);// texture2D(gNormalSampler, textureCoord).xyz;
	nMapNormal = 2.0 * nMapNormal - 1.0;
	nMapNormal = normalize(nMapNormal);

	//Build TBN matrix
	mat3 tbn = mat3(ntangent, bitangent, nnormal);
	
	//Transform nMap normal into world space 
	nMapNormal = normalize(tbn * nMapNormal);
	return nMapNormal;
}

void main()
{
	float ambientIntensity = 0.5; //Constant intensity
	vec4 ambientColour = gl_LightSource[0].ambient * ambientIntensity;
	
	//Calculate diffuse and specular
	vec4 diffuse = vec4(0.0, 0.0, 0.0, 0.0);
	vec4 specular = vec4(0.0, 0.0, 0.0, 0.0);

	vec3 lightDir = (gCameraMatrix * vec4(lightDirection, 1.0)).xyz;

	vec3 nMapNormal = getNormal();
	float diffuse_intensity = dot(normalize(nMapNormal), normalize(lightDir));
	if (diffuse_intensity > 0.0)
	{
		diffuse += gl_LightSource[0].diffuse * diffuse_intensity;

		//No specular if diffuse intensity is 0
		
		vec3 nLightDir = normalize(lightDir);
		vec3 nNorm = normalize(nMapNormal);
		vec3 lightReflection = normalize(reflect(-lightDir, nMapNormal));
		vec3 vertEye = normalize(-position); //Vector from pixel to eye at (0,0,0)
		float shininess = 4.0;
		float specularIntensity = max(0.0, pow(dot(vertEye, lightReflection), shininess)); //Negative angle shouldn't see specular
		specular += gl_LightSource[0].specular * specularIntensity;

	}
	
	gl_FragColor = texture2D(gSampler, textureCoord) * (specular + diffuse + ambientColour);

}