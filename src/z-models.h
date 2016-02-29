#ifndef Z_MODELS_H_INCLUDED
#define Z_MODELS_H_INCLUDED

#include "z-list.h"

enum model_enum { MODEL_NONE, MODEL_POINT, MODEL_CUBE, MODEL_SQUARE,
    MODEL_MAX
};

struct model_st {
    unsigned int id;
    char *name;

    GLint vbo_offset;
    GLint draw_mode;

    unsigned int vcount;

    struct vbuf_st {
	GLfloat v[4];
	GLfloat vt[2];
	GLfloat vn[3];
    } *vbuf;

    struct texture_st *tex;
};

extern void mdl_set_vbo_offset(struct model_st *, GLint);
extern GLint mdl_get_vbo_offset(struct model_st *);

extern struct model_st *mdl_get_std_model(int);
extern struct model_st *mdl_new_model(int);
extern void mdl_delete_model(struct model_st *);

extern struct model_st *mdl_create_square_model(int, int, GLfloat, GLfloat,
						GLfloat, GLfloat);

void mdl_init(void);

#endif
