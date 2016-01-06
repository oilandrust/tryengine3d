varying vec3 norm, position;

void main(){
	norm = normalize(gl_Normal);
	gl_Position = ftransform();
}