#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>

#include "z-light.h"
#include "z-maths.h"

struct light_st *light_create_light(void)
{
    struct light_st *tmp;

    tmp = (struct light_st *)malloc(sizeof(struct light_st));
    if (tmp == NULL) {
	perror("Cannot allocate memory for light_st");
    }
    tmp->lightblk.num = 0;
    return tmp;
}

void light_destroy_light(struct light_st *lt)
{
    free(lt);
}

void light_set_ambience(struct light_st *lt, float a[3])
{
    vec3_copy(lt->lightblk.ambience, a);
}

void light_set_light(struct light_st *lt, int n, float lp[3], float e[3])
{
    if (lt->lightblk.num < n + 1)
	lt->lightblk.num = n + 1;
    vec3_copy(lt->lightblk.pos[n].xyz, lp);
    vec3_copy(lt->lightblk.emission[n].rgb, e);
}

void light_init(struct light_st *lt)
{
    vec3_set(lt->lightblk.ambience, 0.3f, 0.3f, 0.3f);
    vec3_set(lt->lightblk.emission[0].rgb, 0.5f, 0.5f, 0.5f);
    vec3_set(lt->lightblk.emission[1].rgb, 0.6f, 0.6f, 0.6f);
    vec3_set(lt->lightblk.emission[2].rgb, 0.7f, 0.7f, 0.7f);
    vec3_set(lt->lightblk.emission[3].rgb, 0.8f, 0.8f, 0.8f);
    vec3_set(lt->lightblk.pos[0].xyz, 0.0f, 0.0f, 2.5f);
    vec3_set(lt->lightblk.pos[1].xyz, 0.0f, 0.0f, 2.0f);
    vec3_set(lt->lightblk.pos[2].xyz, 2.0f, 0.0f, 2.0f);
    vec3_set(lt->lightblk.pos[3].xyz, 2.0f, 2.0f, 2.0f);
    lt->lightblk.num = 1;
}

void light_set_lightblk_offset(struct light_st *lt, int offset)
{
    lt->lightblk_offset = offset;
}

void light_set_lightblk_size(struct light_st *lt, int sz)
{
    lt->lightblk_size = sz;
}
