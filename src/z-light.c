#include <stdlib.h>
#include <stdio.h>

#include "z-light.h"
#include "z-mat.h"

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

void light_set_ambience(struct light_st *lt, GLfloat a[3])
{
    copy_vec3(lt->lightblk.ambience, a);
}

void light_set_light(struct light_st *lt, int n, GLfloat lp[3], GLfloat e[3])
{
    if (lt->lightblk.num < n + 1)
	lt->lightblk.num = n + 1;
    copy_vec3(lt->lightblk.pos[n].xyz, lp);
    copy_vec3(lt->lightblk.emission[n].rgb, e);
}

void light_init(struct light_st *lt)
{
    set_vec3(lt->lightblk.ambience, 0.3f, 0.3f, 0.3f);
    set_vec3(lt->lightblk.emission[0].rgb, 0.5f, 0.5f, 0.5f);
    set_vec3(lt->lightblk.emission[1].rgb, 0.6f, 0.6f, 0.6f);
    set_vec3(lt->lightblk.emission[2].rgb, 0.7f, 0.7f, 0.7f);
    set_vec3(lt->lightblk.emission[3].rgb, 0.8f, 0.8f, 0.8f);
    set_vec3(lt->lightblk.pos[0].xyz, 0.0f, 0.0f, 2.5f);
    set_vec3(lt->lightblk.pos[1].xyz, 0.0f, 0.0f, 2.0f);
    set_vec3(lt->lightblk.pos[2].xyz, 2.0f, 0.0f, 2.0f);
    set_vec3(lt->lightblk.pos[3].xyz, 2.0f, 2.0f, 2.0f);
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
