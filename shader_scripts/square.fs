#version 330 core

out vec4 FragColor;
//uniform vec4 ourColor;
in vec3 ourColor;
in vec2 TexCoord;

//uniform sampler2D ourTexture;
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
//FragColor = vertexColor;
//FragColor = ourColor;
    // FragColor = vec4(ourColor,1.0);
    // FragColor = texture(ourTexture, TexCoord);
    // FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
}