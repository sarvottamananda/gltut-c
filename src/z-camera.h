#ifndef Z_CAMERA_H_INCLUDED
#define Z_CAMERA_H_INCLUDED

struct scene_st {
    int id;
    char *name;
    struct sceneblk_st {
	GLfloat viewmat[4][4];
	GLfloat projmat[4][4];
	GLfloat cam_position[3];
	GLfloat cam_target[3];
	GLfloat cam_up[3];
    } sceneblk;

    float cam_fovy;
    float cam_aspect;
    float cam_znear;
    float cam_zfar;

    int sceneblk_offset;
    int sceneblk_size;
};

extern void cam_init(struct scene_st *);

extern struct scene_st *cam_create_scene(void);
extern void cam_destroy_scene(struct scene_st *);

extern float cam_set_fovy(struct scene_st *, float);
extern float cam_set_aspect(struct scene_st *, float);
extern float cam_set_znear(struct scene_st *, float);
extern float cam_set_zfar(struct scene_st *, float);
extern void cam_set_position(struct scene_st *, float[3]);
extern void cam_set_target(struct scene_st *, float[3]);
extern void cam_set_up(struct scene_st *, float[3]);
extern void cam_reset(struct scene_st *);

void cam_compute_proj_mat4(struct scene_st *);
void cam_compute_view_mat4(struct scene_st *);

#endif
