uniform sampler2D tex0;
uniform sampler2D tex1;
uniform sampler2D tex2;
uniform sampler2D alphaMap;
varying vec2 texCoord;
varying vec2 alphaCoord;

void main(){
	vec4 low = texture2D(tex0, texCoord);
	vec4 mid = texture2D(tex1, texCoord);
	vec4 hi = texture2D(tex2, texCoord);
	vec4 alpha = texture2D(alphaMap, alphaCoord);
	
	vec4 color = mix(vec4(0),low,alpha.x);
	color = mix(color ,mid,alpha.y);
	color = mix(color ,hi,alpha.z);
		
	
	gl_FragColor = color;//alpha.x*low + alpha.y*mid + alpha.z*hi;
}
	