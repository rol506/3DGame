#version 430 core

in vec3 Color;
in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D tex;
uniform float pos;

void main()
{
  int windowSizeX = 960;
  float borderLeft = abs(pos) + abs(pos) * windowSizeX;
  float borderRight = abs(pos) + abs(pos) * windowSizeX + windowSizeX/10;
  float borderMargin = windowSizeX/25;
  
  borderLeft += gl_FragCoord.y - windowSizeX/2;
  borderRight += gl_FragCoord.y - windowSizeX/2;

	//FragColor = texture(tex, texCoord + vec2(abs(pos), 0.0));
	FragColor = texture(tex, texCoord);
	
	if (gl_FragCoord.x >= borderLeft && gl_FragCoord.x <= borderRight)
	{
		if (gl_FragCoord.x <= borderLeft + borderMargin)
		{
			FragColor += vec4(Color, 1.0) * (1 - (borderMargin - (gl_FragCoord.x - borderLeft)) / borderMargin);
		}
		else if (gl_FragCoord.x >= borderRight - borderMargin)
		{
			FragColor += vec4(Color, 1.0) * (1 - ((gl_FragCoord.x - borderRight + borderMargin)/borderMargin));
		}
		else {
			FragColor += vec4(Color, 1.0);
		}
	}
}
