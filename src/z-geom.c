#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "z-geom.h"


static struct geom_model_st * create_geom_st(void)
{
    struct geom_model_st * tmp = (struct geom_model_st *)malloc(sizeof(struct geom_model_st));

    if(tmp == NULL){
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

    return tmp;

}


static const char * vsep = "/";


static void geom_set_v(struct geom_model_st * g, int vcnt, float v[][4])
{
    g->v_cnt = vcnt;
    g->v = (float (*)[4])malloc(sizeof(float)* 4 * vcnt);
    if (g->v==NULL){
	perror("Cannot allocate memory for v");
	exit(1);
    }

    for(int i=0;i<vcnt;i++){
	g->v[i][0] = v[i][0];
	g->v[i][1] = v[i][1];
	g->v[i][2] = v[i][2];
	g->v[i][3] = v[i][3];
    }
}

static void geom_set_vt(struct geom_model_st * g, int vtcnt, float vt[][3])
{
    g->vt_cnt = vtcnt;
    g->vt = (float (*)[3])malloc(sizeof(float)* 3 * vtcnt);
    if (g->vt==NULL){
	perror("Cannot allocate memory for vt");
	exit(1);
    }

    for(int i=0;i<vtcnt;i++){
	g->vt[i][0] = vt[i][0];
	g->vt[i][1] = vt[i][1];
	g->vt[i][2] = vt[i][2];
    }
}

static void geom_set_vn(struct geom_model_st * g, int vncnt, float vn[][3])
{
    g->vn_cnt = vncnt;
    g->vn = (float (*)[3])malloc(sizeof(float)* 3 * vncnt);
    if (g->vn==NULL){
	perror("Cannot allocate memory for vn");
	exit(1);
    }

    for(int i=0;i<vncnt;i++){
	g->vn[i][0] = vn[i][0];
	g->vn[i][1] = vn[i][1];
	g->vn[i][2] = vn[i][2];
    }
}

static void geom_set_min(struct geom_model_st * g, float xmin, float ymin, float zmin)
{
    g->min[0] = xmin;
    g->min[1] = ymin;
    g->min[2] = zmin;
}

static void geom_set_max(struct geom_model_st * g, float xmax, float ymax, float zmax)
{
    g->max[0] = xmax;
    g->max[1] = ymax;
    g->max[2] = zmax;
}

static void geom_set_faces(struct geom_model_st *g, int f, char **fstr)
{
    g->f_cnt = fcnt;

    g->fn = (int *)malloc(sizeof(int)  * fcnt);
    g->fv = (int **)malloc(sizeof(int *)  * fcnt);
    g->fvt = (int **)malloc(sizeof(int *)  * fcnt);
    g->fvn = (int **)malloc(sizeof(int *)  * fcnt);

    if( (g->v==NULL) || (g->vt==NULL) || (g->vn==NULL) 
	    || (g->fn==NULL) || (g->fv==NULL) || (g->fvt==NULL) || (g->fvn==NULL) ) {
	perror("Cannot allocate memory for some of v, vt, vn, fv, fvt, fvn");
	exit(1);
    }

    g->fn[f] = 1;
    g->fv[f] = (int *)malloc(sizeof(int)); 
    g->fvt[f] = (int *)malloc(sizeof(int)); 
    g->fvn[f] = (int *)malloc(sizeof(int)); 

    if (( g->fv[f] == NULL)
	    ||( g->fv[f] == NULL)
	    ||( g->fv[f] == NULL)){
	perror("Cannot allocate memory for some of fv[f], fvt[f], fvn[f]");
	exit(1);
    }
    char * token;

    token = strtok(vstr,vsep);
    g->fv[f][0] = atoi(token);
    token = strtok(NULL,vsep);
    g->fvt[f][0] = atoi(token);
    token = strtok(NULL,vsep);
    g->fvn[f][0] = atoi(token);
}

struct geom_model_st * geom_make_cube(void)
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

    float vt[][3] = {
	{0.0, 0.0, 0.0},
	{1.0, 0.0, 0.0},
	{0.0, 1.0, 0.0},
	{1.0, 1.0, 0.0}
    };

    float vn[][3] = {
	{1.0, 0.0, 0.0},
	{-1.0, 0.0, 0.0},
	{0.0, 1.0, 0.0},
	{0.0, -1.0, 0.0},
	{0.0, 0.0, 1.0},
	{0.0, 0.0, -1.0}
    };

    char * finf[] = {
	"0 2 3 1",
	"4 5 7 6",
	"0 4 5 1",
	"2 6 7 3",
	"0 2 6 4",
	"1 3 7 5"
    };

    struct geom_model_st * cube;

    cube = create_geom_st();

    geom_set_v(cube,8,v);
    geom_set_vt(cube,4,vt);
    geom_set_vn(cube,4,vn);
    geom_set_faces(cube,6,finf);

    geom_set_min(cube,0.0, 0.0, 0.0);
    geom_set_max(cube,1.0, 1.0, 1.0);

    return cube;
}
