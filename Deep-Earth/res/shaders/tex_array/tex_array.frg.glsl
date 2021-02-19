#version 330 core

in vec3 passTexCoord;

out vec4 FragColor;

// texture sampler
uniform sampler2DArray textureArray;

void main()
{
	FragColor = texture(textureArray, passTexCoord);

	if (FragColor.a == 0)
	{
		discard;
	}
}
