#ifndef Z_MODELS_H_INCLUDED
#define Z_MODELS_H_INCLUDED

#include "z-geom.h"
#include "z-list.h"

enum model_enum { MODEL_NONE, MODEL_POINT, MODEL_CUBE, MODEL_SQUARE,
    MODEL_MAX
};

struct model_st {
    unsigned int id;
    char *name;

    GLint vbo_offset;
    GLint *vbo_start;

    GLint draw_mode;
    GLint *start;
    GLint *count;
    GLint num;

    unsigned int vcount;

    struct vbuf_st {
	GLfloat v[4];
	GLfloat vt[2];
	GLfloat vn[3];
    } *vbuf;

};

extern void mdl_set_vbo_offset(struct model_st *, GLint);
extern void mdl_set_vbo_start(struct model_st *model, GLint offset);
extern GLint mdl_get_vbo_offset(struct model_st *);

extern struct model_st *mdl_get_std_model(int);

extern struct model_st *mdl_create_checker_triangulated(int, int, GLfloat,
							GLfloat, GLfloat,
							GLfloat);
extern struct model_st *mdl_create_checker_stripped(int xnum, int ynum,
						    GLfloat lx, GLfloat by,
						    GLfloat rx, GLfloat ty);
extern struct model_st *mdl_create_sphere_stripped(int cnum, int znum,
						   GLfloat lx, GLfloat rx,
						   GLfloat by, GLfloat ty);

extern struct model_st *mdl_create_model_from_geom(char *name, struct geom_model_st
						   *geom);

extern void mdl_init(void);

extern void mdl_print(struct model_st *mdl);

#endif
