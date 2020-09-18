#ifndef Z_MATHS_H_INCLUDED
#define Z_MATHS_H_INCLUDED

#include <math.h>

extern void vec2_sub(float res[2], float[2], float[2]);
extern void vec3_sub(float res[3], float[3], float[3]);
extern void vec4_sub(float res[4], float[4], float[4]);
extern void mat3_sub(float res[3][3], float[3][3], float[3][3]);
extern void mat4_sub(float res[4][4], float[4][4], float[4][4]);

extern void vec3_add(float res[2], float[2], float[2]);
extern void vec3_add(float res[3], float[3], float[3]);
extern void vec3_add(float res[4], float[4], float[4]);
extern void mat3_add(float res[3][3], float[3][3], float[3][3]);
extern void mat4_add(float res[4][4], float[4][4], float[4][4]);

extern void mat4_mult(float res[4][4], float[4][4], float[4][4]);
extern void mat3_mult(float res[3][3], float[3][3], float[3][3]);

extern void vec3_cross(float res[3], float[3], float[3]);

extern float vec2_dot(float[2], float[2]);
extern float vec3_dot(float[3], float[3]);
extern float vec4_dot(float[4], float[4]);

extern void vec2_normalize(float v[2]);
extern void vec3_normalize(float v[3]);
extern void vec4_normalize(float v[4]);

extern void mat3_identity(float m[3][3]);
extern void mat4_identity(float m[4][4]);

extern void vec2_zero(float v[2]);
extern void vec3_zero(float v[3]);
extern void vec4_zero(float v[4]);

extern void vec2_set_1f(float v[2], float c);
extern void vec3_set_1f(float v[3], float c);
extern void vec4_set_1f(float v[4], float c);

extern void vec2_set(float v[2], float, float);
extern void vec3_set(float v[3], float, float, float);
extern void vec4_set(float v[4], float, float, float, float);

extern void vec2_copy(float[2], float[2]);
extern void vec3_copy(float[3], float[3]);
extern void vec4_copy(float[4], float[4]);

extern void mat3_copy(float[3][3], float[3][3]);
extern void mat4_copy(float[4][4], float[4][4]);

extern void mat3_copy_mat4(float[3][3], float[4][4]);
extern void mat4_copy_mat3(float[4][4], float[3][3]);

extern void mat3_transpose(float[3][3], float[3][3]);
extern void mat4_transpose(float[4][4], float[4][4]);

extern void mat2_print(char *, float[2][2]);
extern void mat3_print(char *, float[3][3]);
extern void mat4_print(char *, float[4][4]);

extern void vec2_print(char *, float[2]);
extern void vec3_print(char *, float[3]);
extern void vec4_print(char *, float[4]);

extern void mat2_inverse(float[2][2], float[2][2]);
extern void mat3_inverse(float[3][3], float[3][3]);
extern void mat4_inverse(float[4][4], float[4][4]);

static inline float degtorad(float deg)
{
    return deg * M_PI / 180.0f;
}

static inline float radtodeg(float rad)
{
    return rad * 180.0f / M_PI;
}

#endif
