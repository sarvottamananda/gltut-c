#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/glew.h>

#include "z-materials.h"
#include "z-maths.h"
#include "z-tex.h"

struct material_st *std_material = NULL;
int num_std_materials = 0;

static float **std_color = NULL;
int num_std_colors = 0;

static int id = 0;

static struct material_st black_mat = {
    MATERIAL_NONE, "nil",
    {
     {0.0f, 0.0f, 0.0f}, 0.0f,
     {0.0f, 0.0f, 0.0f}, 0.0f,
     {0.0f, 0.0f, 0.0f}, 0.0f,
     {0.0f, 0.0f},
     {0.0f, 0.0f},
     1.0f,
     1.0f,
     },
    NULL,
    0, 0
};

void mtrl_copy(struct material_st *dst, struct material_st *src)
{
    vec3_copy(dst->matblk.ambient, src->matblk.ambient);
    vec3_copy(dst->matblk.diffuse, src->matblk.diffuse);
    vec3_copy(dst->matblk.specular, src->matblk.specular);
    dst->matblk.shininess = src->matblk.shininess;
    dst->matblk.opacity = src->matblk.opacity;
    dst->tex = src->tex;
}

void mtrl_set_matblk_offset(struct material_st *m, int offset)
{
    m->matblk_offset = offset;
}

void mtrl_set_matblk_size(struct material_st *m, int sz)
{
    m->matblk_size = sz;
}

void mtrl_get_std_color(float c[], int color)
{
    vec4_copy(c, std_color[color]);
}

struct material_st *mtrl_new_material(int num)
{
    struct material_st *tmp =
	(struct material_st *)malloc(sizeof(struct material_st) * num);

    if (tmp == NULL) {
	perror("Cannot allocate memory for mtrl_create_material.\n");
	exit(EXIT_FAILURE);
    }

    for (int i = 0; i < num; i++) {
	tmp[i].id = id++;
	tmp[i].name = NULL;
	mtrl_copy(&tmp[i], &black_mat);
    }

    mtrl_print(tmp);

    return tmp;
}

void mtrl_delete_material(struct material_st *m)
{
    free(m);
}

void mtrl_set_name(struct material_st *m, char *name)
{
    m->name = strdup(name);
}

void mtrl_set_ambient(struct material_st *m, float r, float g, float b, float a)
{
    m->matblk.ambient[0] = r;
    m->matblk.ambient[1] = g;
    m->matblk.ambient[2] = b;
    m->matblk.ambient[3] = a;
}

void mtrl_set_diffuse(struct material_st *m, float r, float g, float b, float a)
{
    m->matblk.diffuse[0] = r;
    m->matblk.diffuse[1] = g;
    m->matblk.diffuse[2] = b;
    m->matblk.diffuse[3] = a;
}

void mtrl_set_specular(struct material_st *m, float r, float g, float b,
		       float a)
{
    m->matblk.specular[0] = r;
    m->matblk.specular[1] = g;
    m->matblk.specular[2] = b;
    m->matblk.specular[3] = a;
}

void mtrl_set_shininess(struct material_st *m, float s)
{
    m->matblk.shininess = s;
}

void color_set(float res[], float r, float g, float b, float a)
{
    res[0] = r;
    res[1] = g;
    res[2] = b;
    res[3] = a;
}

void color_init(void)
{
    num_std_colors = COLOR_MAX;

    std_color = (float **)malloc(sizeof(float *) * num_std_colors);
    if (std_color == NULL) {
	perror("Cannot allocate memory for std_color");
	exit(EXIT_FAILURE);
    }
    for (int i = 0; i < num_std_colors; i++) {
	std_color[i] = (float *)malloc(sizeof(float) * 4);
	if (std_color[i] == NULL) {
	    perror("Cannot allocate memory for std_color[i]");
	    exit(EXIT_FAILURE);
	}
    }

    color_set(std_color[COLOR_NONE], 0.0, 0.0, 0.0, 0.0);
    color_set(std_color[COLOR_WHITE], 1.0, 1.0, 1.0, 1.0);
    color_set(std_color[COLOR_BLACK], 0.0, 0.0, 0.0, 1.0);

    color_set(std_color[COLOR_1000], 1.0, 0.0, 0.0, 0.0);
    color_set(std_color[COLOR_0100], 0.0, 1.0, 0.0, 0.0);
    color_set(std_color[COLOR_0010], 0.0, 0.0, 1.0, 0.0);
    color_set(std_color[COLOR_0001], 0.0, 0.0, 0.0, 1.0);

    color_set(std_color[COLOR_RED], 1.0, 0.0, 0.0, 1.0);
    color_set(std_color[COLOR_GREEN], 0.0, 1.0, 0.0, 1.0);
    color_set(std_color[COLOR_BLUE], 0.0, 0.0, 1.0, 1.0);

    color_set(std_color[COLOR_YELLOW], 1.0, 1.0, 0.0, 1.0);
    color_set(std_color[COLOR_MAGENTA], 1.0, 0.0, 1.0, 1.0);
    color_set(std_color[COLOR_CYAN], 0.0, 1.0, 1.0, 1.0);

    color_set(std_color[COLOR_ORANGE], 1.0, 0.5, 0.0, 1.0);
    color_set(std_color[COLOR_PINK], 1.0, 0.0, 0.5, 1.0);
    color_set(std_color[COLOR_LEMON_YELLOW], 0.5, 1.0, 0.0, 1.0);
    color_set(std_color[COLOR_LEMON_GREEN], 0.0, 1.0, 0.5, 1.0);
    color_set(std_color[COLOR_PURPLE], 0.5, 0.0, 1.0, 1.0);
    color_set(std_color[COLOR_SEABLUE], 0.0, 0.5, 1.0, 1.0);

    color_set(std_color[COLOR_DARKRED], 0.5, 0.0, 0.0, 1.0);
    color_set(std_color[COLOR_DARKGREEN], 0.0, 0.5, 0.0, 1.0);
    color_set(std_color[COLOR_DARKBLUE], 0.0, 0.0, 0.5, 1.0);

    color_set(std_color[COLOR_DARKYELLOW], 0.5, 0.5, 0.0, 1.0);
    color_set(std_color[COLOR_DARKMAGENTA], 0.5, 0.0, 0.5, 1.0);
    color_set(std_color[COLOR_DARKCYAN], 0.0, 0.5, 0.5, 1.0);

    color_set(std_color[COLOR_GRAY], 0.5, 0.5, 0.5, 1.0);

    color_set(std_color[COLOR_LIGHTRED], 1.0, 0.5, 0.5, 1.0);
    color_set(std_color[COLOR_LIGHTGREEN], 0.5, 1.0, 0.5, 1.0);
    color_set(std_color[COLOR_LIGHTBLUE], 0.5, 0.5, 1.0, 1.0);

    color_set(std_color[COLOR_LIGHTYELLOW], 1.0, 1.0, 0.5, 1.0);
    color_set(std_color[COLOR_LIGHTMAGENTA], 1.0, 0.5, 1.0, 1.0);
    color_set(std_color[COLOR_LIGHTCYAN], 0.5, 1.0, 1.0, 1.0);

}

void mtrl_init(void)
{
    num_std_materials = MATERIAL_MAX;

    color_init();

    std_material = mtrl_new_material(num_std_materials);

    int mat = 0;
    float color[4];

    mat = MATERIAL_NONE;
    mtrl_get_std_color(color, COLOR_NONE);
    mtrl_copy(&(std_material[mat]), &black_mat);
    vec3_copy(std_material[mat].matblk.ambient, color);
    vec3_copy(std_material[mat].matblk.diffuse, color);
    std_material[mat].id = mat;
    std_material[mat].name = strdup("none");

    mat = MATERIAL_WHITE;
    mtrl_get_std_color(color, COLOR_WHITE);
    mtrl_copy(&std_material[mat], &black_mat);
    vec3_copy(std_material[mat].matblk.ambient, color);
    vec3_copy(std_material[mat].matblk.diffuse, color);
    std_material[mat].id = mat;
    std_material[mat].name = strdup("white");

    mat = MATERIAL_BLACK;
    mtrl_get_std_color(color, COLOR_BLACK);
    mtrl_copy(&std_material[mat], &black_mat);
    vec3_copy(std_material[mat].matblk.ambient, color);
    vec3_copy(std_material[mat].matblk.diffuse, color);
    std_material[mat].id = mat;
    std_material[mat].name = strdup("black");

    mat = MATERIAL_RED;
    mtrl_get_std_color(color, COLOR_RED);
    mtrl_copy(&std_material[mat], &black_mat);
    vec3_copy(std_material[mat].matblk.ambient, color);
    vec3_copy(std_material[mat].matblk.diffuse, color);
    std_material[mat].id = mat;
    std_material[mat].name = strdup("red");

    mat = MATERIAL_BLUE;
    mtrl_get_std_color(color, COLOR_BLUE);
    mtrl_copy(&std_material[mat], &black_mat);
    vec3_copy(std_material[mat].matblk.ambient, color);
    vec3_copy(std_material[mat].matblk.diffuse, color);
    std_material[mat].id = mat;
    std_material[mat].name = strdup("blue");

    mat = MATERIAL_GREEN;
    mtrl_get_std_color(color, COLOR_GREEN);
    mtrl_copy(&std_material[mat], &black_mat);
    vec3_copy(std_material[mat].matblk.ambient, color);
    vec3_copy(std_material[mat].matblk.diffuse, color);
    std_material[mat].id = mat;
    std_material[mat].name = strdup("green");

    mat = MATERIAL_YELLOW;
    mtrl_get_std_color(color, COLOR_YELLOW);
    mtrl_copy(&std_material[mat], &black_mat);
    vec3_copy(std_material[mat].matblk.ambient, color);
    vec3_copy(std_material[mat].matblk.diffuse, color);
    std_material[mat].id = mat;
    std_material[mat].name = strdup("yellow");

    mat = MATERIAL_MAGENTA;
    mtrl_get_std_color(color, COLOR_MAGENTA);
    mtrl_copy(&std_material[mat], &black_mat);
    vec3_copy(std_material[mat].matblk.ambient, color);
    vec3_copy(std_material[mat].matblk.diffuse, color);
    std_material[mat].id = mat;
    std_material[mat].name = strdup("magenta");

    mat = MATERIAL_CYAN;
    mtrl_get_std_color(color, COLOR_CYAN);
    mtrl_copy(&std_material[mat], &black_mat);
    vec3_copy(std_material[mat].matblk.ambient, color);
    vec3_copy(std_material[mat].matblk.diffuse, color);
    std_material[mat].id = mat;
    std_material[mat].name = strdup("cyan");

    id = MATERIAL_MAX;

}

struct material_st *mtrl_get_std_material(int material)
{
    return &(std_material[material]);
};

void mtrl_set_texcoords(struct material_st *m, float ox, float oy,
			float sx, float sy)
{

    // m->matblk.dummy_1[0] = 1.0;
    // m->matblk.dummy_1[1] = 0.0;
    m->matblk.texorigin[0] = ox;
    m->matblk.texorigin[1] = oy;
    // m->matblk.texorigin[0] = 0.0;
    // m->matblk.texorigin[1] = 0.0;
    m->matblk.texsize[0] = sx;
    m->matblk.texsize[1] = sy;
    // m->matblk.texsize[0] = 1.0;
    // m->matblk.texsize[1] = 0.0;
}

void mtrl_print(struct material_st *mat)
{
    printf("Material: %s [%d]\n", mat->name, mat->id);
    printf("\tAmbient: ");
    for (int i = 0; i < 3; i++)
	printf("%f ", mat->matblk.ambient[i]);
    printf("\n");
    printf("\tDiffuse: ");
    for (int i = 0; i < 3; i++)
	printf("%f ", mat->matblk.diffuse[i]);
    printf("\n");
    printf("\tSpecular: ");
    for (int i = 0; i < 3; i++)
	printf("%f ", mat->matblk.specular[i]);
    printf("\n");
    printf("\tShininess: ");
    printf("%f ", mat->matblk.shininess);
    printf("\n");
    printf("\tOpacity: ");
    printf("%f ", mat->matblk.opacity);
    printf("\n");
    printf("\tTex origin: ");
    for (int i = 0; i < 2; i++)
	printf("%f ", mat->matblk.texorigin[i]);
    printf("\n");
    printf("\tTex size: ");
    for (int i = 0; i < 2; i++)
	printf("%f ", mat->matblk.texsize[i]);
    printf("\n");
    printf("\tMatblk offset: ");
    printf("%d ", mat->matblk_offset);
    printf("\tMatblk size: ");
    printf("%d ", mat->matblk_size);
    if (mat->tex != NULL) {
	printf("\tTexture: ");
	printf("%s [%d] ", mat->tex->name, mat->tex->id);
	printf("\n");
    } else
	printf("\tTexture: Nil\n");
}
