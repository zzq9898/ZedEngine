//---------------------------------
#type vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexture;
layout (location = 2) in vec3 aNormal;
uniform mat4 u_ViewProjection;
uniform mat4 u_Model;
out vec2 TexCoord;
out vec3 Normal;
void main()
{
    gl_Position = u_ViewProjection * u_Model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    TexCoord = aTexture;
    Normal = aNormal;
}

//---------------------------------
#type fragment
#version 330 core
out vec4 FragColor;
in vec2 TexCoord;
in vec3 Normal;
uniform sampler2D testTexture;
void main()
{
    vec4 color = texture(testTexture,TexCoord);
    FragColor = vec4(color);
}