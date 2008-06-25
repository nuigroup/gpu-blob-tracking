uniform sampler2D tex;
uniform float Contrast;
uniform float Brightness;
void main()
{

	vec4 color = texture2D(tex,gl_TexCoord[0].st);
	color.rgb = color.ggg * Brightness;
	gl_FragColor = mix(1.0, color, vec4(Contrast));
}