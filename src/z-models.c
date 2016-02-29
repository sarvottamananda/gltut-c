#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/glew.h>

#include "z-geom.h"
#include "z-models.h"
#include "z-mat.h"
#include "debug.h"

// Data for a cube

int cube_vcount = 36;

GLfloat cube_vertices[] = {
    0.0f, 0.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 1.0f, 1.0f,

    0.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,

    1.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,

    1.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 0.0f, 1.0f,

    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 1.0f, 1.0f,

    0.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,

    0.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f,

    1.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 1.0f,

    1.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 1.0f,

    1.0f, 0.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,

    0.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,

    0.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 1.0f, 1.0f,
};

GLfloat cube_normals[] = {
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,

    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,

    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,

    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,

    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,

    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,

    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,

    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,

    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,

    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,

    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,

    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
};

GLfloat cube_tcoords[] = {
    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,

    0.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,

    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,

    0.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,

    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,

    0.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,

    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,

    0.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,

    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,

    0.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,

    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,

    0.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
};

GLint square_vcount = 6;

GLfloat square_vertices[] = {
    0.0f, 0.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 1.0f, 1.0f,

    0.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
};

GLfloat square_normals[] = {
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,

    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
};

GLfloat square_tcoords[] = {
    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,

    0.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
};

GLfloat point_vertices[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat point_normals[] = { 0.0f, 0.0f, 1.0f };
GLfloat point_tcoords[] = { 0.0f, 0.0f };

struct model_st *std_model = NULL;

int num_std_models = 0;

static int id = 0;

static struct vbuf_st *vbuf_alloc(int vcnt)
{
    struct vbuf_st *tmp;

    tmp = (struct vbuf_st *)malloc(vcnt * sizeof(struct vbuf_st));
    if (tmp == NULL) {
	perror("Cannot allocate memory for vbuf");
	exit(1);
    }
    return tmp;

}

struct vbuf_st *mdl_create_vbuf(int vcnt, GLfloat * v, GLfloat * vt,
				GLfloat * vn)
{
    struct vbuf_st *tmp = vbuf_alloc(vcnt);

    for (int i = 0; i < vcnt; i++) {
	copy_vec4(tmp[i].v, &(v[4 * i]));
	copy_vec2(tmp[i].vt, &(vt[2 * i]));
	copy_vec3(tmp[i].vn, &(vn[3 * i]));
    }
    return tmp;
}

static struct model_st *mdl_new_model(int num)
{
    struct model_st *tmp = (struct model_st *)
	malloc(sizeof(struct model_st) * num);
    if (tmp == NULL) {
	perror("Cannot allocate memory for new_model.");
	exit(EXIT_FAILURE);
    }
    for (int i = 0; i < num; i++) {
	tmp[i].vcount = 0;
	tmp[i].vbuf = NULL;
	tmp[i].id = id++;
	tmp[i].name = NULL;
	tmp[i].vbo_offset = 0;
	tmp[i].draw_mode = GL_POINTS;
	tmp[i].start = NULL;
	tmp[i].count = NULL;
	tmp[i].num = 0;
    }
    return tmp;
}

static void mdl_delete_model(struct model_st *p)
{
    free(p);
}

void set_primitive_count(struct model_st *model, int num)
{
    model->vbo_start = (GLint *) malloc(sizeof(GLint) * num);
    model->start = (GLint *) malloc(sizeof(GLint) * num);
    model->count = (GLint *) malloc(sizeof(GLint) * num);
    model->num = num;

    if ((model->start == NULL) || (model->count == NULL)) {
	perror("Cannot allocate memory for model->start and model->count");
	exit(1);
    }

}

void mdl_init(void)
{
    num_std_models = 4;

    std_model = mdl_new_model(num_std_models);

    std_model[MODEL_NONE].id = (int)(MODEL_NONE);
    std_model[MODEL_NONE].name = strdup("nil_model");
    std_model[MODEL_NONE].vcount = 0;
    std_model[MODEL_NONE].vbuf = NULL;
    std_model[MODEL_NONE].vbo_offset = 0;
    std_model[MODEL_NONE].draw_mode = GL_POINTS;
    std_model[MODEL_NONE].start = NULL;
    std_model[MODEL_NONE].count = NULL;
    std_model[MODEL_NONE].num = 0;

    std_model[MODEL_POINT].id = (int)(MODEL_POINT);
    std_model[MODEL_POINT].name = strdup("point_model");
    std_model[MODEL_POINT].vcount = 1;
    std_model[MODEL_POINT].vbuf =
	mdl_create_vbuf(1, point_vertices, point_tcoords, point_normals);
    std_model[MODEL_POINT].vbo_offset = 0;
    std_model[MODEL_POINT].draw_mode = GL_POINTS;
    set_primitive_count(&std_model[MODEL_POINT], 1);
    std_model[MODEL_POINT].start[0] = 0;
    std_model[MODEL_POINT].count[0] = std_model[MODEL_POINT].vcount;

    std_model[MODEL_CUBE].id = (int)(MODEL_CUBE);
    std_model[MODEL_CUBE].name = strdup("cube_model");
    std_model[MODEL_CUBE].vcount = cube_vcount;
    std_model[MODEL_CUBE].vbuf =
	mdl_create_vbuf(cube_vcount, cube_vertices, cube_tcoords, cube_normals);
    std_model[MODEL_CUBE].vbo_offset = 0;
    std_model[MODEL_CUBE].draw_mode = GL_TRIANGLES;
    set_primitive_count(&std_model[MODEL_CUBE], 1);
    std_model[MODEL_CUBE].start[0] = 0;
    std_model[MODEL_CUBE].count[0] = std_model[MODEL_CUBE].vcount;

    std_model[MODEL_SQUARE].id = (int)(MODEL_SQUARE);
    std_model[MODEL_SQUARE].name = strdup("square_model");
    std_model[MODEL_SQUARE].vcount = square_vcount;
    std_model[MODEL_SQUARE].vbuf =
	mdl_create_vbuf(square_vcount, square_vertices, square_tcoords,
			square_normals);
    std_model[MODEL_SQUARE].vbo_offset = 0;
    std_model[MODEL_SQUARE].draw_mode = GL_TRIANGLES;
    set_primitive_count(&std_model[MODEL_SQUARE], 1);
    std_model[MODEL_SQUARE].start[0] = 0;
    std_model[MODEL_SQUARE].count[0] = std_model[MODEL_SQUARE].vcount;

    id = MODEL_MAX;
}

GLint mdl_get_vbo_offset(struct model_st *model)
{
    return model->vbo_offset;
}

void mdl_set_vbo_offset(struct model_st *model, GLint offset)
{
    model->vbo_offset = offset;
}

void mdl_set_vbo_start(struct model_st *model, GLint offset)
{
    for (int i = 0; i < model->num; i++)
	model->vbo_start[i] = model->start[i] + offset;
}

struct model_st *mdl_get_std_model(int m)
{
    return &(std_model[m]);
}

void subdivide(GLfloat u1[2], GLfloat u2[2], GLfloat u3[2],
	       GLfloat cutoff, int depth,
	       GLfloat(*curv) (GLfloat[2]),
	       void (*surf) (GLfloat[2], GLfloat *, GLfloat *, GLfloat *)
    )
{
    GLfloat v1[3], v2[3], v3[3];
    GLfloat n1[3], n2[3], n3[3];
    GLfloat t1[2], t2[2], t3[2];
    GLfloat u12[2], u23[2], u31[2];
    GLint i;

    if (depth == 0 || ((*curv) (u1) < cutoff &&
		       (*curv) (u2) < cutoff && (*curv) (u3) < cutoff)) {
	(*surf) (u1, v1, n1, t1);
	(*surf) (u2, v2, n2, t2);
	(*surf) (u3, v3, n3, t3);
	return;
    }
    for (i = 0; i < 2; i++) {
	u12[i] = (u1[i] + u2[i]) / 2.0;
	u23[i] = (u2[i] + u3[i]) / 2.0;
	u31[i] = (u3[i] + u1[i]) / 2.0;
    }
    subdivide(u1, u12, u31, cutoff, depth - 1, curv, surf);
    subdivide(u2, u23, u12, cutoff, depth - 1, curv, surf);
    subdivide(u3, u31, u23, cutoff, depth - 1, curv, surf);
    subdivide(u12, u23, u31, cutoff, depth - 1, curv, surf);
}

struct model_st *mdl_create_checker_with_triangles(int xnum, int ynum,
						   GLfloat lx, GLfloat by,
						   GLfloat rx, GLfloat ty)
{
    struct model_st *tmp;

    tmp = mdl_new_model(1);

    tmp->name = strdup("checker_model");

    int vcount = 6 * xnum * ynum;

    GLfloat dx = 1.0f / xnum;
    GLfloat dy = 1.0f / ynum;

    GLfloat(*vertices)[4] =
	(GLfloat(*)[4]) malloc(sizeof(GLfloat) * 4 * vcount);
    GLfloat(*tcoords)[2] = (GLfloat(*)[2]) malloc(sizeof(GLfloat) * 2 * vcount);
    GLfloat(*normals)[3] = (GLfloat(*)[3]) malloc(sizeof(GLfloat) * 3 * vcount);

    int k = 0;
    for (int i = 0; i < xnum; i++) {
	for (int j = 0; j < ynum; j++) {
	    set_vec4(vertices[k], i * dx, j * dy, 0.0, 1.0);
	    set_vec4(vertices[k + 1], (i + 1) * dx, j * dy, 0.0, 1.0);
	    set_vec4(vertices[k + 2], i * dx, (j + 1) * dy, 0.0, 1.0);

	    set_vec4(vertices[k + 3], i * dx, (j + 1) * dy, 0.0, 1.0);
	    set_vec4(vertices[k + 4], (i + 1) * dx, j * dy, 0.0, 1.0);
	    set_vec4(vertices[k + 5], (i + 1) * dx, (j + 1) * dy, 0.0, 1.0);

	    set_vec2(tcoords[k], lx, by);
	    set_vec2(tcoords[k + 1], rx, by);
	    set_vec2(tcoords[k + 2], lx, ty);

	    set_vec2(tcoords[k + 3], lx, ty);
	    set_vec2(tcoords[k + 4], rx, by);
	    set_vec2(tcoords[k + 5], rx, ty);

	    set_vec3(normals[k], 0.0, 0.0, 1.0);
	    set_vec3(normals[k + 1], 0.0, 0.0, 1.0);
	    set_vec3(normals[k + 2], 0.0, 0.0, 1.0);

	    set_vec3(normals[k + 3], 0.0, 0.0, 1.0);
	    set_vec3(normals[k + 4], 0.0, 0.0, 1.0);
	    set_vec3(normals[k + 5], 0.0, 0.0, 1.0);

	    k += 6;
	}
    }

    tmp->vcount = vcount;
    tmp->vbuf =
	mdl_create_vbuf(vcount, (GLfloat *) vertices, (GLfloat *) tcoords,
			(GLfloat *) normals);
    tmp->draw_mode = GL_TRIANGLES;
    set_primitive_count(tmp, 1);
    tmp->start[0] = 0;
    tmp->count[0] = vcount;

    return tmp;
}

struct model_st *mdl_create_checker_with_strips(int xnum, int ynum,
						GLfloat lx, GLfloat by,
						GLfloat rx, GLfloat ty)
{
    struct model_st *tmp;

    tmp = mdl_new_model(1);

    tmp->name = strdup("checker_strips");

    int vcount = 2 * (xnum + 1) * ynum;

    tmp->draw_mode = GL_TRIANGLE_STRIP;
    set_primitive_count(tmp, ynum);
    for (int i = 0; i < ynum; i++) {
	tmp->start[i] = i * 2 * (xnum + 1);
	tmp->count[i] = 2 * (xnum + 1);
    }

    GLfloat dx = 1.0f / xnum;
    GLfloat dy = 1.0f / ynum;

    GLfloat(*vertices)[4] =
	(GLfloat(*)[4]) malloc(sizeof(GLfloat) * 4 * vcount);
    GLfloat(*tcoords)[2] = (GLfloat(*)[2]) malloc(sizeof(GLfloat) * 2 * vcount);
    GLfloat(*normals)[3] = (GLfloat(*)[3]) malloc(sizeof(GLfloat) * 3 * vcount);

    int k = 0;
    for (int j = 0; j < ynum; j++) {
	for (int i = 0; i < xnum + 1; i++) {
	    set_vec4(vertices[k], i * dx, j * dy, 0.0, 1.0);
	    set_vec4(vertices[k + 1], i * dx, (j + 1) * dy, 0.0, 1.0);

	    set_vec2(tcoords[k], lx + i * (rx - lx), by + j * (ty - by));
	    set_vec2(tcoords[k + 1], lx + i * (rx - lx),
		     by + (j + 1) * (ty - by));

	    set_vec3(normals[k], 0.0, 0.0, 1.0);
	    set_vec3(normals[k + 1], 0.0, 0.0, 1.0);

	    k += 2;
	}
    }

    tmp->vcount = vcount;
    tmp->vbuf =
	mdl_create_vbuf(vcount, (GLfloat *) vertices, (GLfloat *) tcoords,
			(GLfloat *) normals);

    return tmp;
}

struct model_st *mdl_create_model_from_geom(char *name,
					    struct geom_model_st *geom)
{
    struct model_st *tmp;

    tmp = mdl_new_model(1);

    tmp->name = strdup(name);

    int vcount = 0;

    for (int f = 0; f < geom->f_cnt; f++)
	vcount = vcount + geom->fn[f];

    struct vbuf_st *vbuf = vbuf_alloc(vcount);

    tmp->draw_mode = GL_TRIANGLE_FAN;
    set_primitive_count(tmp, geom->f_cnt);
    int off = 0;
    for (int f = 0; f < geom->f_cnt; f++) {
	tmp->start[f] = off;
	tmp->count[f] = vcount;

	for (int v = 0; v < geom->fn[f]; v++) {
	    copy_vec4(vbuf[off + v].v, geom->v[geom->fv[f][v]]);
	    copy_vec2(vbuf[off + v].vt, geom->vt[geom->fvt[f][v]]);
	    copy_vec3(vbuf[off + v].vn, geom->vn[geom->fvn[f][v]]);
	}

	off += geom->fn[f];
    }

    tmp->vcount = vcount;
    tmp->vbuf = vbuf;
    return tmp;
}

void mdl_print(struct model_st *mdl)
{
    printf("Model : %s [%d]\n", mdl->name, mdl->id);
    printf("\tVcount : %d\n", mdl->vcount);
    for (int i = 0; i < mdl->vcount; i++) {
	printf("\t\tV: ");
	for (int j = 0; j < 4; j++)
	    printf("%6.2f ", mdl->vbuf[i].v[j]);
	printf("Vt : ");
	for (int j = 0; j < 2; j++)
	    printf("%6.2f ", mdl->vbuf[i].vt[j]);
	printf("Vn : ");
	for (int j = 0; j < 3; j++)
	    printf("%6.2f ", mdl->vbuf[i].vn[j]);
	printf("\n");
    }
    printf("\tVBO offset : %d\n", mdl->vbo_offset);
    printf("\tDraw mode : %d\n", mdl->draw_mode);
    for (int i = 0; i < mdl->num; i++) {
	printf("\t\tStart : %d (%d), Count : %d\n", mdl->start[i],
	       mdl->vbo_start[i], mdl->count[i]);
    }

}
