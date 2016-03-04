#include <stdio.h>
#include <math.h>

#include "z-maths.h"

void vec3_print(char *name, float vec[3])
{
    printf("%s : [ ", name);
    for (int i = 0; i < 3; i++) {
	printf("%7.5f ", vec[i]);
    }
    printf("]\n");
}

void vec4_print(char *name, float vec[4])
{
    printf("%s : [ ", name);
    for (int i = 0; i < 4; i++) {
	printf("%7.5f ", vec[i]);
    }
    printf("]\n");
}

void mat4_print(char *name, float mat[4][4])
{
    printf("%s :\n", name);
    for (int i = 0; i < 4; i++) {
	printf("[ ");
	for (int j = 0; j < 4; j++)
	    printf("%7.5f ", mat[j][i]);
	printf("]\n");
    }
}

void mat4_identity(float mat[][4])
{
    for (int j = 0; j < 4; j++) {
	for (int i = 0; i < 4; i++) {
	    mat[j][i] = 0.0;
	}
	mat[j][j] = 1.0;
    }
}

void vec3_set_1f(float v[], float x)
{
    v[0] = x;
    v[1] = x;
    v[2] = x;
}

void vec4_set_1f(float v[], float x)
{
    v[0] = x;
    v[1] = x;
    v[2] = x;
    v[3] = x;
}

void vec2_zero(float v[])
{
    v[0] = 0.0f;
    v[1] = 0.0f;
}

void vec3_zero(float v[])
{
    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = 0.0f;
}

void vec4_zero(float v[])
{
    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = 0.0f;
    v[3] = 0.0f;
}

void vec2_set(float v[], float v0, float v1)
{
    v[0] = v0;
    v[1] = v1;
}

void vec3_set(float v[], float v0, float v1, float v2)
{
    v[0] = v0;
    v[1] = v1;
    v[2] = v2;
}

void vec4_set(float v[], float v0, float v1, float v2, float v3)
{
    v[0] = v0;
    v[1] = v1;
    v[2] = v2;
    v[3] = v3;
}

void vec2_copy(float res[], float v[2])
{
    res[0] = v[0];
    res[1] = v[1];
}

void vec3_copy(float res[], float v[3])
{
    res[0] = v[0];
    res[1] = v[1];
    res[2] = v[2];
}

void vec4_copy(float res[], float v[4])
{
    res[0] = v[0];
    res[1] = v[1];
    res[2] = v[2];
    res[3] = v[3];
}

void mat4_copy(float res[][4], float a[4][4])
{
    for (int j = 0; j < 4; j++) {
	for (int i = 0; i < 4; i++) {
	    res[j][i] = a[j][i];
	}
    }
}

void mat4_copy_mat3(float res[][4], float a[3][3])
{
    for (int j = 0; j < 3; j++) {
	for (int i = 0; i < 3; i++) {
	    res[j][i] = a[j][i];
	}
	res[3][j] = 0.0;
	res[j][3] = 0.0;
    }
    res[3][3] = 1.0;
}

void mat3_copy_mat4(float res[][3], float a[4][4])
{
    for (int j = 0; j < 3; j++) {
	for (int i = 0; i < 3; i++) {
	    res[j][i] = a[j][i];
	}
    }
}

void mat4_transpose(float res[][4], float a[][4])
{
    float tmp;

    for (int j = 0; j < 4; j++) {
	    res[j][j] = a[j][j];
	for (int i = j+1; i < 4; i++) {
	    tmp = a[i][j];
	    res[i][j] = a[j][i];
	    res[j][i] = tmp;
	}
    }
}

void mat4_add(float res[][4], float a[4][4], float b[4][4])
{
    for (int j = 0; j < 4; j++) {
	for (int i = 0; i < 4; i++) {
	    res[j][i] = a[j][i] + b[j][i];
	}
    }
}

void vec3_sub(float res[], float v1[3], float v2[3])
{
    res[0] = v1[0] - v2[0];
    res[1] = v1[1] - v2[1];
    res[2] = v1[2] - v2[2];
}

void vec3_add(float res[], float v1[3], float v2[3])
{
    res[0] = v1[0] + v2[0];
    res[1] = v1[1] + v2[1];
    res[2] = v1[2] + v2[2];
}

void mat4_mult(float res[][4], float a[4][4], float b[4][4])
{
    float tmp[4][4];

    for (int j = 0; j < 4; j++) {
	for (int i = 0; i < 4; i++) {
	    float sum = 0;

	    for (int k = 0; k < 4; k++) {
		sum += a[k][i] * b[j][k];
	    }
	    tmp[j][i] = sum;
	}
    }
    mat4_copy(res, tmp);
}

void vec3_normalize(float v[])
{
    float len = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);

    if (len != 0.0f) {
	v[0] = v[0] / len;
	v[1] = v[1] / len;
	v[2] = v[2] / len;
    } else {
	v[0] = 1.0;
	v[1] = v[2] = 0.0;
    }
}

void vec3_cross(float res[], float v1[3], float v2[3])
{
    res[0] = v1[1] * v2[2] - v1[2] * v2[1];
    res[1] = v1[2] * v2[0] - v1[0] * v2[2];
    res[2] = v1[0] * v2[1] - v1[1] * v2[0];
}

float vec3_dot(float v1[3], float v2[3])
{
    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

void mat3_inverse(float res[][3], float m[3][3])
{
    // computes the inverse of a matrix m

    float m00 = (m[1][1] * m[2][2] - m[2][1] * m[1][2]);
    float m10 = (-m[1][0] * m[2][2] + m[1][2] * m[2][0]);
    float m20 = (m[1][0] * m[2][1] - m[1][1] * m[2][0]);

    float det = m[0][0] * m00 + m[0][1] * m10 + m[0][2] * m20;

    float invdet = 1 / det;

    res[0][0] = m00 * invdet;
    res[0][1] = (m[0][2] * m[2][1] - m[0][1] * m[2][2]) * invdet;
    res[0][2] = (m[0][1] * m[1][2] - m[0][2] * m[1][1]) * invdet;
    res[1][0] = m10 * invdet;
    res[1][1] = (m[0][0] * m[2][2] - m[0][2] * m[2][0]) * invdet;
    res[1][2] = (m[1][0] * m[0][2] - m[0][0] * m[1][2]) * invdet;
    res[2][0] = m20 * invdet;
    res[2][1] = (m[2][0] * m[0][1] - m[0][0] * m[2][1]) * invdet;
    res[2][2] = (m[0][0] * m[1][1] - m[1][0] * m[0][1]) * invdet;
}

void mat4_inverse(float res[][4], float a[4][4])
{
    float s0 = a[0][0] * a[1][1] - a[1][0] * a[0][1];
    float s1 = a[0][0] * a[1][2] - a[1][0] * a[0][2];
    float s2 = a[0][0] * a[1][3] - a[1][0] * a[0][3];
    float s3 = a[0][1] * a[1][2] - a[1][1] * a[0][2];
    float s4 = a[0][1] * a[1][3] - a[1][1] * a[0][3];
    float s5 = a[0][2] * a[1][3] - a[1][2] * a[0][3];

    float c5 = a[2][2] * a[3][3] - a[3][2] * a[2][3];
    float c4 = a[2][1] * a[3][3] - a[3][1] * a[2][3];
    float c3 = a[2][1] * a[3][2] - a[3][1] * a[2][2];
    float c2 = a[2][0] * a[3][3] - a[3][0] * a[2][3];
    float c1 = a[2][0] * a[3][2] - a[3][0] * a[2][2];
    float c0 = a[2][0] * a[3][1] - a[3][0] * a[2][1];

    // Should check for 0 determinant
    float invdet =
	1.0 / (s0 * c5 - s1 * c4 + s2 * c3 + s3 * c2 - s4 * c1 + s5 * c0);

    res[0][0] = (a[1][1] * c5 - a[1][2] * c4 + a[1][3] * c3) * invdet;
    res[0][1] = (-a[0][1] * c5 + a[0][2] * c4 - a[0][3] * c3) * invdet;
    res[0][2] = (a[3][1] * s5 - a[3][2] * s4 + a[3][3] * s3) * invdet;
    res[0][3] = (-a[2][1] * s5 + a[2][2] * s4 - a[2][3] * s3) * invdet;

    res[1][0] = (-a[1][0] * c5 + a[1][2] * c2 - a[1][3] * c1) * invdet;
    res[1][1] = (a[0][0] * c5 - a[0][2] * c2 + a[0][3] * c1) * invdet;
    res[1][2] = (-a[3][0] * s5 + a[3][2] * s2 - a[3][3] * s1) * invdet;
    res[1][3] = (a[2][0] * s5 - a[2][2] * s2 + a[2][3] * s1) * invdet;

    res[2][0] = (a[1][0] * c4 - a[1][1] * c2 + a[1][3] * c0) * invdet;
    res[2][1] = (-a[0][0] * c4 + a[0][1] * c2 - a[0][3] * c0) * invdet;
    res[2][2] = (a[3][0] * s4 - a[3][1] * s2 + a[3][3] * s0) * invdet;
    res[2][3] = (-a[2][0] * s4 + a[2][1] * s2 - a[2][3] * s0) * invdet;

    res[3][0] = (-a[1][0] * c3 + a[1][1] * c1 - a[1][2] * c0) * invdet;
    res[3][1] = (a[0][0] * c3 - a[0][1] * c1 + a[0][2] * c0) * invdet;
    res[3][2] = (-a[3][0] * s3 + a[3][1] * s1 - a[3][2] * s0) * invdet;
    res[3][3] = (a[2][0] * s3 - a[2][1] * s1 + a[2][2] * s0) * invdet;

}
