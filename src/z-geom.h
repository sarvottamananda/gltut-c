#ifndef Z_GEOM_H_INCLUDED
#define Z_GEOM_H_INCLUDED

struct geom_model_st {
    float min[3];
    float max[3];
    int v_cnt;
    float (*v)[4];

    int vt_cnt;
    float (*vt)[3];

    int vn_cnt;
    float (*vn)[3];

    int f_cnt;
    int *fn;
    int **fv;
    int **fvt;
    int **fvn;
};

#endif
