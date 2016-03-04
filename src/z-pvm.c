#include <stdio.h>
#include <math.h>

#include "z-pvm.h"
#include "z-maths.h"

void pvm_compute_scale_mat4(float mat[][4], float v[3])
{
    mat4_identity(mat);
    for (int i = 0; i < 3; i++)
	mat[i][i] = v[i];
}

void pvm_compute_translate_mat4(float mat[][4], float v[3])
{
    mat4_identity(mat);
    for (int i = 0; i < 3; i++)
	mat[3][i] = v[i];
}

void pvm_compute_rotate_mat4(float mat[][4], float v[3], float alpha)
{
    float c = cosf(alpha);
    float s = sinf(alpha);
    float t = 1 - c;

    vec3_normalize(v);
    float x = v[0];
    float y = v[1];
    float z = v[2];

    /*
     *     | (tx² + c)  (txy - sz) (txz + sy) |
     * M = | (txy + sz) (ty² + c)  (tyz - sx) |
     *     | (txz - sy) (tyz + sx) (tz² + c)  |
     */

    mat[0][0] = t * x * x + c;
    mat[1][0] = t * x * y - s * z;
    mat[2][0] = t * x * z + s * y;

    mat[0][1] = t * y * x + s * z;
    mat[1][1] = t * y * y + c;
    mat[2][1] = t * y * z - s * x;

    mat[0][2] = t * z * x - s * y;
    mat[1][2] = t * z * y + s * x;
    mat[2][2] = t * z * z + c;

    mat[3][0] = mat[3][1] = mat[3][2] = 0;
    mat[0][3] = mat[1][3] = mat[2][3] = 0;
    mat[3][3] = 1.0;

}

void pvm_compute_model_mat4(float res[][4], float tr[3],
			    float sc[3], float rot[3], float rot_ang)
{
    float scale[4][4];
    float translate[4][4];
    float rotate[4][4];

    pvm_compute_scale_mat4(scale, sc);
    pvm_compute_translate_mat4(translate, tr);
    pvm_compute_rotate_mat4(rotate, rot, rot_ang);

    float tmp[4][4];

    mat4_mult(tmp, rotate, scale);
    mat4_mult(res, translate, tmp);
}

void pvm_compute_view_mat4(float res[][4],
			   float cpos[3], float ctgt[3], float up[3])
{
    float zaxis[3];
    float yaxis[3];
    float xaxis[3];

    vec3_sub(zaxis, cpos, ctgt);
    vec3_normalize(zaxis);

    vec3_cross(xaxis, up, zaxis);
    vec3_normalize(xaxis);

    vec3_cross(yaxis, zaxis, xaxis);
    // Not needed
    // normalize(yaxis);

    res[0][0] = xaxis[0];
    res[1][0] = xaxis[1];
    res[2][0] = xaxis[2];

    res[0][1] = yaxis[0];
    res[1][1] = yaxis[1];
    res[2][1] = yaxis[2];

    res[0][2] = zaxis[0];
    res[1][2] = zaxis[1];
    res[2][2] = zaxis[2];

    res[3][0] = -vec3_dot(xaxis, cpos);
    res[3][1] = -vec3_dot(yaxis, cpos);
    res[3][2] = -vec3_dot(zaxis, cpos);

    res[0][3] = 0;
    res[1][3] = 0;
    res[2][3] = 0;

    res[3][3] = 1;

}

void pvm_compute_proj_mat4(float res[][4], float fovy,
			   float a, float n, float f)
{
    mat4_identity(res);

    float e = 1 / tanf(fovy / 2.0f);

    res[0][0] = e / a;
    res[1][1] = e;
    res[2][2] = -(f + n) / (f - n);
    res[3][3] = 0;
    res[3][2] = -2 * f * n / (f - n);
    res[2][3] = -1.0;
}
