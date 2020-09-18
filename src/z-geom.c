#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "z-geom.h"

static unsigned int id = 0;

static struct geom_model_st *create_geom_st(void)
{
    struct geom_model_st *tmp =
	(struct geom_model_st *)malloc(sizeof(struct geom_model_st));

    if (tmp == NULL) {
	perror("Cannot allocate memory for geom_model_st");
	exit(1);
    }

    tmp->v_cnt = tmp->f_cnt = 0;
    tmp->v = NULL;
    tmp->vt = NULL;
    tmp->vn = NULL;
    tmp->fv = NULL;
    tmp->fvt = NULL;
    tmp->fvn = NULL;
    tmp->id = id++;

    return tmp;

}

static const char *vsep = " ";
static const char *fsep = "/";

static void geom_set_v(struct geom_model_st *g, int vcnt, float v[][4])
{
    g->v_cnt = vcnt;
    g->v = (float (*)[4])malloc(sizeof(float) * 4 * vcnt);
    if (g->v == NULL) {
	perror("Cannot allocate memory for v");
	exit(1);
    }

    for (int i = 0; i < vcnt; i++) {
	g->v[i][0] = v[i][0];
	g->v[i][1] = v[i][1];
	g->v[i][2] = v[i][2];
	g->v[i][3] = v[i][3];
    }
}

static void geom_set_vt(struct geom_model_st *g, int vtcnt, float vt[][2])
{
    g->vt_cnt = vtcnt;
    g->vt = (float (*)[2])malloc(sizeof(float) * 2 * vtcnt);
    if (g->vt == NULL) {
	perror("Cannot allocate memory for vt");
	exit(1);
    }

    for (int i = 0; i < vtcnt; i++) {
	g->vt[i][0] = vt[i][0];
	g->vt[i][1] = vt[i][1];
    }
}

static void geom_set_vn(struct geom_model_st *g, int vncnt, float vn[][3])
{
    g->vn_cnt = vncnt;
    g->vn = (float (*)[3])malloc(sizeof(float) * 3 * vncnt);
    if (g->vn == NULL) {
	perror("Cannot allocate memory for vn");
	exit(1);
    }

    for (int i = 0; i < vncnt; i++) {
	g->vn[i][0] = vn[i][0];
	g->vn[i][1] = vn[i][1];
	g->vn[i][2] = vn[i][2];
    }
}

static void geom_set_min(struct geom_model_st *g, float xmin, float ymin,
			 float zmin)
{
    g->min[0] = xmin;
    g->min[1] = ymin;
    g->min[2] = zmin;
}

static void geom_set_max(struct geom_model_st *g, float xmax, float ymax,
			 float zmax)
{
    g->max[0] = xmax;
    g->max[1] = ymax;
    g->max[2] = zmax;
}

static void geom_set_faces(struct geom_model_st *g, int fcnt, char **fstr)
{
    g->f_cnt = fcnt;

    g->fn = (int *)malloc(sizeof(int) * fcnt);
    g->fv = (int **)malloc(sizeof(int *) * fcnt);
    g->fvt = (int **)malloc(sizeof(int *) * fcnt);
    g->fvn = (int **)malloc(sizeof(int *) * fcnt);

    if ((g->fn == NULL) || (g->fv == NULL) || (g->fvt == NULL)
	|| (g->fvn == NULL)) {
	perror("Cannot allocate memory for some of fn, fv, fvt, fvn");
	exit(1);
    }

    for (int i = 0; i < fcnt; i++) {
	char *vstr = strdup(fstr[i]);
	char *token = NULL;

	token = strtok(vstr, ":");
	int nv = atoi(token);

	g->fn[i] = nv;
	g->fv[i] = (int *)malloc(sizeof(int) * nv);
	g->fvt[i] = (int *)malloc(sizeof(int) * nv);
	g->fvn[i] = (int *)malloc(sizeof(int) * nv);

	if ((g->fv[i] == NULL)
	    || (g->fv[i] == NULL)
	    || (g->fv[i] == NULL)) {
	    perror("Cannot allocate memory for some of fv[i], fvt[i], fvn[i]");
	    exit(1);
	}

	for (int j = 0; j < nv; j++) {
	    token = strtok(NULL, fsep);
	    g->fv[i][j] = atoi(token);
	    token = strtok(NULL, fsep);
	    g->fvt[i][j] = atoi(token);
	    token = strtok(NULL, vsep);
	    g->fvn[i][j] = atoi(token);
	}
    }
}

struct geom_model_st *geom_make_cube(void)
{
    float v[][4] = {
	{0.0, 0.0, 0.0, 1.0},
	{1.0, 0.0, 0.0, 1.0},
	{0.0, 1.0, 0.0, 1.0},
	{1.0, 1.0, 0.0, 1.0},
	{0.0, 0.0, 1.0, 1.0},
	{1.0, 0.0, 1.0, 1.0},
	{0.0, 1.0, 1.0, 1.0},
	{1.0, 1.0, 1.0, 1.0}
    };

    float vt[][2] = {
	{0.0, 0.0},
	{1.0, 0.0},
	{0.0, 1.0},
	{1.0, 1.0}
    };

    float vn[][3] = {
	{-1.0, 0.0, 0.0},
	{1.0, 0.0, 0.0},
	{0.0, -1.0, 0.0},
	{0.0, 1.0, 0.0},
	{0.0, 0.0, -1.0},
	{0.0, 0.0, 1.0},
    };

    char *finf[] = {
	"4:0/0/4 2/2/4 3/3/4 1/1/4",
	"4:4/0/5 5/2/5 7/3/5 6/1/5",
	"4:0/0/2 1/2/2 5/3/2 4/1/2",
	"4:3/0/3 2/2/3 6/3/3 7/1/3",
	"4:2/0/0 0/2/0 4/3/0 6/1/0",
	"4:1/0/1 3/2/1 7/3/1 5/1/1"
    };

    struct geom_model_st *cube;

    cube = create_geom_st();

    cube->name = strdup("cube");

    geom_set_v(cube, 8, v);
    geom_set_vt(cube, 4, vt);
    geom_set_vn(cube, 4, vn);
    geom_set_faces(cube, 6, finf);

    geom_set_min(cube, 0.0, 0.0, 0.0);
    geom_set_max(cube, 1.0, 1.0, 1.0);

    return cube;
}

struct geom_model_st *geom_make_square(void)
{
    float v[][4] = {
	{0.0, 0.0, 0.0, 1.0},
	{1.0, 0.0, 0.0, 1.0},
	{0.0, 1.0, 0.0, 1.0},
	{1.0, 1.0, 0.0, 1.0}
    };

    float vt[][2] = {
	{0.0, 0.0},
	{1.0, 0.0},
	{0.0, 1.0},
	{1.0, 1.0}
    };

    float vn[][3] = {
	{0.0, 0.0, 1.0}
    };

    char *finf[] = {
	"4:0/0/0 2/2/0 3/3/0 1/1/0",
    };

    struct geom_model_st *sq;

    sq = create_geom_st();

    sq->name = strdup("square");

    geom_set_v(sq, 4, v);
    geom_set_vt(sq, 4, vt);
    geom_set_vn(sq, 1, vn);
    geom_set_faces(sq, 1, finf);

    geom_set_min(sq, 0.0, 0.0, 0.0);
    geom_set_max(sq, 1.0, 1.0, 0.0);

    geom_print(sq);

    return sq;
}

void geom_print(struct geom_model_st *g)
{
    printf("Geometry : %s [%d]\n", g->name, g->id);
    printf("\tMin : ");
    for (int i = 0; i < 3; i++)
	printf(" %f", g->min[i]);
    printf("\n");
    printf("\tMax : ");
    for (int i = 0; i < 3; i++)
	printf(" %f", g->max[i]);
    printf("\n");
    for (int j = 0; j < g->v_cnt; j++) {
	printf("\t\tV : ");
	for (int i = 0; i < 4; i++)
	    printf(" %f", g->v[j][i]);
	printf("\n");
    }
    for (int j = 0; j < g->vt_cnt; j++) {
	printf("\t\tVT : ");
	for (int i = 0; i < 2; i++)
	    printf(" %f", g->vt[j][i]);
	printf("\n");
    }
    for (int j = 0; j < g->vn_cnt; j++) {
	printf("\t\tVN : ");
	for (int i = 0; i < 3; i++)
	    printf(" %f", g->vn[j][i]);
	printf("\n");
    }
    for (int j = 0; j < g->f_cnt; j++) {
	printf("\t\tF : ");
	for (int i = 0; i < g->fn[j]; i++) {
	    printf("%d/", g->fv[j][i]);
	    printf("%d/", g->fvt[j][i]);
	    printf("%d ", g->fvn[j][i]);
	}
	printf("\n");
    }
}
