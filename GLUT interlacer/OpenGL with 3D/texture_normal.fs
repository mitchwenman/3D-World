/*!
	@class TextureNormalShader
	Fragment Shader: Uses the incoming tangent and normal vectors to build
	a Tangent, Bitangent, Normal matrix which is used to 
	transform the normal map vector into world space. Lighting
	calculations are then performed using this normal map vector
	rather than the vertex's original normal.
*/

varying vec2 textureCoord;
varying vec3 normal;
varying vec3 position;
varying vec3 tangent;


uniform sampler2D gSampler;
uniform sampler2D gNormalSampler;

uniform vec3 lightDirection;
uniform mat4 gCameraMatrix;

//! A fragment shader for normal mapping.
/*!
	
*/
void main()
{
	float ambientIntensity = 0.5; //Constant intensity
	vec4 ambientColour = gl_LightSource[0].ambient * ambientIntensity;
	
	//Calculate diffuse and specular
	vec4 diffuse = vec4(0.0, 0.0, 0.0, 0.0);
	vec4 specular = vec4(0.0, 0.0, 0.0, 0.0);

	vec3 lightDir = (gCameraMatrix * vec4(lightDirection, 1.0)).xyz;

	//Get normal map normal and get between -1, 1
	vec3 nMapNormal = texture2D(gNormalSampler, textureCoord).xyz;
	nMapNormal = 2.0 * nMapNormal - 1;
	
	//Normalise tangents
	vec3 ntangent = normalize(tangent);
	vec3 nnormal = normalize(normal);

	//Calculate bitangent
	vec3 bitangent = normalize(cross(ntangent, nnormal));

	//Build TBN -> World space matrix
	mat3 tbn = mat3(ntangent, bitangent, nnormal);
	
	//Transform nMap normal into world space 
	nMapNormal = normalize(nMapNormal);
	nMapNormal = normalize(tbn * nMapNormal);

	float diffuse_intensity = dot(normalize(nMapNormal), normalize(lightDir));
	if (diffuse_intensity > 0.0)
	{
		diffuse += gl_LightSource[0].diffuse * diffuse_intensity;

		//No specular if diffuse intensity is 0
		
		vec3 lightReflection = normalize(reflect(-lightDir, nMapNormal));
		vec3 vertEye = normalize(-position); //Vector from pixel to eye at (0,0,0)
		float specularIntensity = max(0.0, pow(dot(vertEye, lightReflection), 4.0)); //Negative angle shouldn't see specular
		specular += gl_LightSource[0].specular * specularIntensity;

	}
	
	gl_FragColor = texture2D(gSampler, textureCoord) * (specular + diffuse + ambientColour);

}