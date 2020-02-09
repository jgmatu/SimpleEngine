// Defined before aTangent and aNormal primitive data atributes

mat3 getTBNMatrix(mat4 model)
{
    vec3 T = normalize(vec3(model * vec4(aTangent, 0.0)));
    vec3 N = normalize(vec3(model * vec4(aNormal, 0.0)));

    // Re-orthogonalize T with respect to N.
    T = normalize(T - dot(T, N) * N);

    // Then retrieve perpendicular vector B with the cross product of T and N.
    vec3 B = cross(N, T);

    return transpose(mat3(T, B, N));
}
