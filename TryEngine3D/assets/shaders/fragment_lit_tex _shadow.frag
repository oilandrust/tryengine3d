uniform sampler2D mainTex;
uniform sampler2D shadowMap;

uniform float receiveShadow;
varying vec3 norm, position;


void main(){
	vec4 color = vec4(0);

	//ADD AMBIENT CONTRIBUTION
	color += gl_LightSource[0].ambient*gl_FrontMaterial.ambient;
	
	//COMPUTE NORMAL AND LIGHT DIR
	vec3 normal = normalize(norm);

	vec3 lightDirection = -normalize(position - gl_LightSource[0].position.xyz);

	float d = dot(normal,lightDirection);
	vec3 h = normalize(gl_LightSource[0].halfVector.xyz);
	
	//ADD DIFFUSE AND SPEC CONTRIB 	
	//DIFFUSE
	color += d*gl_LightSource[0].diffuse*gl_FrontMaterial.diffuse;
	float s = dot(normal, h);
	
	/*
	//SHADOW MAP LOOKUP
	vec3 projectiveBiased = (gl_TexCoord[1].xyz / gl_TexCoord[1].w);
	if(receiveShadow != 0.0){
		float texDepth = texture2D(shadowMap, projectiveBiased.xy).x;
		if(texDepth < projectiveBiased.z-0.0001  )
			color *= 0.5;
	}*/

	gl_FragColor = color;// * texture2D(mainTex, gl_TexCoord[0].xy);
}
	