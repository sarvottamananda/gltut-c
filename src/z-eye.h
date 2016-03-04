#ifndef Z_EYE_H_INCLUDED
#define Z_EYE_H_INCLUDED

struct scene_st {
    int id;
    char *name;
    struct sceneblk_st {
	float viewmat[4][4];
	float projmat[4][4];
	float eye_position[3];
	float eye_target[3];
	float eye_up[3];
    } sceneblk;

    float eye_fovy;
    float eye_aspect;
    float eye_znear;
    float eye_zfar;

    int sceneblk_offset;
    int sceneblk_size;
};

extern void eye_init(struct scene_st *);

extern struct scene_st *eye_create_scene(void);
extern void eye_destroy_scene(struct scene_st *);

extern float eye_set_fovy(struct scene_st *, float);
extern float eye_set_aspect(struct scene_st *, float);
extern float eye_set_znear(struct scene_st *, float);
extern float eye_set_zfar(struct scene_st *, float);
extern void eye_set_position(struct scene_st *, float[3]);
extern void eye_set_target(struct scene_st *, float[3]);
extern void eye_set_up(struct scene_st *, float[3]);
extern void eye_reset(struct scene_st *);

void eye_compute_proj_mat4(struct scene_st *);
void eye_compute_view_mat4(struct scene_st *);

#endif
