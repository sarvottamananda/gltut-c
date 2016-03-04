#include <stdlib.h>
#include <stdio.h>
#include "math.h"

#include "z-maths.h"
#include "z-pvm.h"

#include "z-eye.h"

void eye_init(struct scene_st *c)
{
    vec3_set(c->sceneblk.eye_position, 8.0f, -8.0f, 2.0f);
    vec3_set(c->sceneblk.eye_target, 0.0f, 0.0f, 0.0f);
    vec3_set(c->sceneblk.eye_up, 0.0f, 0.0f, 1.0f);

    c->eye_fovy = 30.0f * M_PI / 180.0f;
    c->eye_aspect = 4.0f / 3.0f;
    c->eye_znear = 1.0f;
    c->eye_zfar = 20.0f;

}

struct scene_st *eye_create_scene(void)
{
    struct scene_st *tmp;

    tmp = (struct scene_st *)malloc(sizeof(struct scene_st));
    if (tmp == NULL) {
	perror("Cannot allocate memory for scene_st");
    }
}

float eye_set_fovy(struct scene_st *sc, float val)
{
    float oldval;

    oldval = sc->eye_fovy;
    sc->eye_fovy = val;
    return oldval;
}

float eye_set_aspect(struct scene_st *sc, float val)
{
    float oldval;

    oldval = sc->eye_aspect;
    sc->eye_aspect = val;
    return oldval;
}

float eye_set_znear(struct scene_st *sc, float val)
{
    float oldval;

    oldval = sc->eye_znear;
    sc->eye_znear = val;
    return oldval;
}

float eye_set_zfar(struct scene_st *sc, float val)
{
    float oldval;

    oldval = sc->eye_zfar;
    sc->eye_zfar = val;
    return oldval;
}

void eye_set_position(struct scene_st *sc, float p[3])
{
    for (int i = 0; i < 3; i++)
	sc->sceneblk.eye_position[i] = p[i];
}

void eye_set_target(struct scene_st *sc, float p[3])
{
    for (int i = 0; i < 3; i++)
	sc->sceneblk.eye_target[i] = p[i];
}

void eye_set_up(struct scene_st *sc, float p[3])
{
    for (int i = 0; i < 3; i++)
	sc->sceneblk.eye_up[i] = p[i];
}

void eye_reset(struct scene_st *sc)
{
    sc->sceneblk.eye_up[0] = 0.0f;
    sc->sceneblk.eye_up[1] = 0.0f;
    sc->sceneblk.eye_up[2] = 1.0f;

    float front[3];
    float right[3];
    float target[3];

    vec3_sub(target, sc->sceneblk.eye_target, sc->sceneblk.eye_position);
    vec3_cross(right, target, sc->sceneblk.eye_up);
    vec3_cross(front, sc->sceneblk.eye_up, right);
    vec3_normalize(front);

    vec3_add(sc->sceneblk.eye_target, sc->sceneblk.eye_position, front);
}

void eye_compute_proj_mat4(struct scene_st *sc)
{
    pvm_compute_proj_mat4(sc->sceneblk.projmat, sc->eye_fovy,
			  sc->eye_aspect, sc->eye_znear, sc->eye_zfar);

}

void eye_compute_view_mat4(struct scene_st *sc)
{
    pvm_compute_view_mat4(sc->sceneblk.viewmat,
			  sc->sceneblk.eye_position,
			  sc->sceneblk.eye_target, sc->sceneblk.eye_up);
}
