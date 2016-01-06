uniform sampler2D shadowMap;

uniform float receiveShadow;
varying vec3 norm, position;


void main(){
	vec4 color = vec4(0);
	
	//LOOP OVER LIGHTS
	for(int i = 1;i<2;i++){
	
		//ADD AMBIENT CONTRIBUTION
		color += gl_LightSource[i].ambient*gl_FrontMaterial.ambient;
		
		//COMPUTE NORMAL AND LIGHT DIR
		vec3 normal = normalize(norm);
		if(dot(normal,-position)<0.0) 
			normal = -normal;
		vec3 lightDirection = -normalize(position - gl_LightSource[i].position.xyz);
		float d = dot(normal,lightDirection);
		vec3 h = normalize(gl_LightSource[i].halfVector.xyz);
		
		//ADD DIFFUSE AND SPEC CONTRIB IF IN SPOT ANGLE
			if(d>0.0){
				//DIFFUSE
				color += d*gl_LightSource[i].diffuse*gl_FrontMaterial.diffuse;
				float s = dot(normal, h);
				//SPECULAR
				if(s>0.0){
					color += pow(s, gl_FrontMaterial.shininess)*
					gl_LightSource[i].specular*gl_FrontMaterial.specular;
				}
			}

	}
	
	vec3 projectiveBiased = (gl_TexCoord[0].xyz / gl_TexCoord[0].w);
	if(receiveShadow != 0.0){
		float texDepth = texture2D(shadowMap, projectiveBiased.xy).x;
		if(texDepth < projectiveBiased.z-0.0001  )
			color *= 0.5;
	}

	gl_FragColor = color;
}
	