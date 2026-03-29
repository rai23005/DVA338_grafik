#version 420 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in vec3 worldPos[];

flat out vec3 flatNormal;
out vec3 flatPos;

void main()
{
    // Hämta tre hörn i world space
    vec3 A = worldPos[0];
    vec3 B = worldPos[1];
    vec3 C = worldPos[2];

    // Beräkna facett-normal
    vec3 N = normalize(cross(B - A, C - A));

    // Skicka ut till fragment shader (samma normal till alla tre hörn)
    flatNormal = N;

    for (int i = 0; i < 3; ++i) {
        flatPos = worldPos[i];
        gl_Position = gl_in[i].gl_Position;
        EmitVertex();
    }

    EndPrimitive();
}