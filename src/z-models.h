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

    GLint vcount;

    struct vbuf_st{
        GLfloat[4] v;
        GLfloat[3] vt;
        GLfloat[3] vn;
    } * vbuf;

    struct texture_st *tex;
};

extern GLint mdl_get_vcount(struct model_st *);
extern GLfloat *mdl_get_vertices(struct model_st *);
extern GLfloat *mdl_get_normals(struct model_st *);
extern GLfloat *mdl_get_tcoords(struct model_st *);

extern void mdl_set_vbo_offset(struct model_st *, GLint);
extern GLint mdl_get_vbo_offset(struct model_st *);

extern struct model_st *mdl_get_std_model(int);
extern struct model_st *mdl_new_model(int);
extern void mdl_delete_model(struct model_st *);

extern struct model_st *mdl_create_square_model(int, int, GLfloat, GLfloat,
						GLfloat, GLfloat);

void mdl_init(void);

#endif
