attribute vec3 position; // vertex position attribute
attribute vec2 texCoord;                // vertex texture coordinate attribute
attribute vec3 normal;
attribute vec3 tangent;

uniform mat4 ViewProj;
uniform mat4 World;

varying vec2 texCoordVar;               // vertex texture coordinate varying

void main()
{
    gl_Position = ViewProj * World * vec4(position, 1.0);
    texCoordVar = texCoord;             // assign the texture coordinate attribute to its varying
}
