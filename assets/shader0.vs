attribute vec3 vertexPosition_modelspace; // vertex position attribute
attribute vec2 texCoord;                // vertex texture coordinate attribute

uniform mat4 ViewProj;
uniform mat4 Model;

varying vec2 texCoordVar;               // vertex texture coordinate varying

void main()
{
    gl_Position = ViewProj * Model * vec4(vertexPosition_modelspace, 1.0);
    texCoordVar = texCoord;             // assign the texture coordinate attribute to its varying
}
