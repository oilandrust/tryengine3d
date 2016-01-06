varying vec3 norm, position;
uniform mat4 shadowMat;

void main(){
	norm = normalize(gl_NormalMatrix*gl_Normal);
	
	position = (gl_ModelViewMatrix*gl_Vertex).xyz;
	
	vec4 pos = gl_ModelViewMatrix*gl_Vertex;
	gl_TexCoord[0] = gl_MultiTexCoord0;
	gl_TexCoord[1] = shadowMat*pos;
	
	gl_Position = ftransform();
}