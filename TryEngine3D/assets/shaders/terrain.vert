varying vec2 texCoord;
varying vec2 alphaCoord;

void main(){
	vec4 pos = gl_Vertex;
	texCoord = pos.xy;
	alphaCoord = texCoord/64;
	//float h = texture2D(heightMap, alphaCoord).r;
	
	pos = gl_ModelViewMatrix*pos;
	gl_Position = gl_ProjectionMatrix*pos;
}