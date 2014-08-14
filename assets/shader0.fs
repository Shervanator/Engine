precision mediump float;        // set default precision for floats to medium

uniform sampler2D texture;      // shader texture uniform

varying vec2 texCoordVar;       // fragment texture coordinate varying

void main()
{
    // sample the texture at the interpolated texture coordinate
    // and write it to gl_FragColor
    gl_FragColor = texture2D( texture, texCoordVar);
}
