#ifndef Z_MODELS_H_INCLUDED
#define Z_MODELS_H_INCLUDED


enum model_enum { MODEL_NONE, MODEL_POINT, MODEL_CUBE, MODEL_SQUARE,
    MODEL_MAX
};

struct model_st {
    unsigned int id;
    char *name;

    int vbo_offset;
    int *vbo_start;

    int draw_mode;
    int *start;
    int *count;
    int num;

    unsigned int vcount;

    struct vbuf_st {
	float v[4];
	float vt[2];
	float vn[3];
    } *vbuf;

};

extern void mdl_set_vbo_offset(struct model_st *, int);
extern void mdl_set_vbo_start(struct model_st *model, int offset);
extern int mdl_get_vbo_offset(struct model_st *);

extern struct model_st *mdl_get_std_model(int);

extern struct model_st *mdl_create_checker_triangulated(int, int, float,
							float, float,
							float);
extern struct model_st *mdl_create_checker_stripped(int xnum, int ynum,
						    float lx, float by,
						    float rx, float ty);
extern struct model_st *mdl_create_sphere_stripped(int cnum, int znum,
						   float lx, float rx,
						   float by, float ty);

struct geom_model_st;

extern struct model_st *mdl_create_model_from_geom(char *name, struct geom_model_st
						   *geom);

extern void mdl_init(void);

extern void mdl_print(struct model_st *mdl);

#endif
