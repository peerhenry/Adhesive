#version 400
layout(location=0) in vec3 VertexPosition;
layout(location=1) in vec3 VertexNormal;

out vec3 Color;

uniform vec3 LightDirection;
uniform vec3 LightColor;
uniform vec3 AmbientColor;
uniform vec3 MaterialColor;
uniform mat4 PVM;
uniform mat3 NormalMatrix;

void main()
{
  vec3 n = NormalMatrix * VertexNormal;
  vec3 ray = normalize(LightDirection);
  Color = MaterialColor * AmbientColor + MaterialColor * LightColor * max(dot(ray, -n), 0.0);

  gl_Position = PVM * vec4(VertexPosition, 1.0);
}