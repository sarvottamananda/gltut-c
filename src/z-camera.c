#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>

#include "z-maths.h"
#include "z-pvm.h"

#include "z-camera.h"

void cam_init(struct scene_st *c)
{
    vec3_set(c->sceneblk.cam_position, 8.0f, -8.0f, 2.0f);
    vec3_set(c->sceneblk.cam_target, 0.0f, 0.0f, 0.0f);
    vec3_set(c->sceneblk.cam_up, 0.0f, 0.0f, 1.0f);

    c->cam_fovy = 30.0f * M_PI / 180.0f;
    c->cam_aspect = 4.0f / 3.0f;
    c->cam_znear = 1.0f;
    c->cam_zfar = 20.0f;

}

struct scene_st *cam_create_scene(void)
{
    struct scene_st *tmp;

    tmp = (struct scene_st *)malloc(sizeof(struct scene_st));
    if (tmp == NULL) {
	perror("Cannot allocate memory for scene_st");
    }
}

float cam_set_fovy(struct scene_st *sc, float val)
{
    float oldval;

    oldval = sc->cam_fovy;
    sc->cam_fovy = val;
    return oldval;
}

float cam_set_aspect(struct scene_st *sc, float val)
{
    float oldval;

    oldval = sc->cam_aspect;
    sc->cam_aspect = val;
    return oldval;
}

float cam_set_znear(struct scene_st *sc, float val)
{
    float oldval;

    oldval = sc->cam_znear;
    sc->cam_znear = val;
    return oldval;
}

float cam_set_zfar(struct scene_st *sc, float val)
{
    float oldval;

    oldval = sc->cam_zfar;
    sc->cam_zfar = val;
    return oldval;
}

void cam_set_position(struct scene_st *sc, float p[3])
{
    for (int i = 0; i < 3; i++)
	sc->sceneblk.cam_position[i] = p[i];
}

void cam_set_target(struct scene_st *sc, float p[3])
{
    for (int i = 0; i < 3; i++)
	sc->sceneblk.cam_target[i] = p[i];
}

void cam_set_up(struct scene_st *sc, float p[3])
{
    for (int i = 0; i < 3; i++)
	sc->sceneblk.cam_up[i] = p[i];
}

void cam_reset(struct scene_st *sc)
{
    sc->sceneblk.cam_up[0] = 0.0f;
    sc->sceneblk.cam_up[1] = 0.0f;
    sc->sceneblk.cam_up[2] = 1.0f;

    float front[3];
    float right[3];
    float target[3];

    vec3_sub(target, sc->sceneblk.cam_target, sc->sceneblk.cam_position);
    vec3_cross(right, target, sc->sceneblk.cam_up);
    vec3_cross(front, sc->sceneblk.cam_up, right);
    vec3_normalize(front);

    vec3_add(sc->sceneblk.cam_target, sc->sceneblk.cam_position, front);
}

void cam_compute_proj_mat4(struct scene_st *sc)
{
    pvm_compute_proj_mat4(sc->sceneblk.projmat, sc->cam_fovy,
			  sc->cam_aspect, sc->cam_znear, sc->cam_zfar);

}

void cam_compute_view_mat4(struct scene_st *sc)
{
    pvm_compute_view_mat4(sc->sceneblk.viewmat,
			  sc->sceneblk.cam_position,
			  sc->sceneblk.cam_target, sc->sceneblk.cam_up);
}
