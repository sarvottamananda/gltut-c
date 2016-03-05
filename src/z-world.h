#ifndef Z_WORLD_H_INCLUDED
#define Z_WORLD_H_INCLUDED

struct model_st;
struct material_st;

struct object_st {
    int id;
    char *name;

    struct model_st *model;
    struct material_st *material;

    struct modelblk_st {
	GLfloat modelmat[4][4];
	GLfloat normalmat[4][4];
    } modelblk;

    int modelblk_offset;
    int modelblk_size;

    float translate[3];
    float scale[3];
    float rotate_axis[3];
    float rotate_angle;

};

extern void world_init(float, float, float);

extern void obj_abs_translate(struct object_st *, float, float, float);
extern void obj_abs_scale(struct object_st *, float, float, float);
extern void obj_abs_rotate(struct object_st *, float, float, float, float);
extern void obj_set_material(struct object_st *, int);

extern void obj_set_modelblk_offset(struct object_st *, int);
extern void obj_set_modelblk_size(struct object_st *, int);

extern void obj_compute_model_mat4(struct object_st *);
extern void obj_compute_normal_mat4(struct object_st *);

extern struct object_st *obj_create_object(char *, struct model_st *,
					   struct material_st *);

extern void obj_print(struct object_st *obj);

#endif
