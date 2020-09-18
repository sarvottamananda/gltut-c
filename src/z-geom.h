#ifndef Z_GEOM_H_INCLUDED
#define Z_GEOM_H_INCLUDED

struct geom_model_st {
    char *name;
    unsigned int id;
    float min[3];
    float max[3];
    int v_cnt;
    float (*v)[4];

    int vt_cnt;
    float (*vt)[2];

    int vn_cnt;
    float (*vn)[3];

    int f_cnt;
    int *fn;
    int **fv;
    int **fvt;
    int **fvn;
};

extern struct geom_model_st *geom_make_square(void);
extern struct geom_model_st *geom_make_cube(void);

extern void geom_print(struct geom_model_st *g);

#endif
