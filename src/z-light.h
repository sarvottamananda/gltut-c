#ifndef Z_LIGHT_H_INCLUDED
#define Z_LIGHT_H_INCLUDED

#define MAXLIGHTS 4

struct light_st {
    struct lightblk_st {
	GLfloat ambience[3];
	GLfloat _pad;
	struct emission_st {
	    GLfloat rgb[3];
	    GLfloat _pad;
	} emission[MAXLIGHTS];
	struct pos_st {
	    GLfloat xyz[3];
	    GLfloat _pad;
	} pos[MAXLIGHTS];
	GLuint num;
    } lightblk;

    int lightblk_offset;
    int lightblk_size;
};

extern void light_init(struct light_st *);

extern struct light_st *light_create_light(void);
extern void light_set_light(struct light_st *, int, float[3], float[3]);
extern void light_set_ambience(struct light_st *, float[3]);

extern void light_set_lightblk_offset(struct light_st *, int);
extern void light_set_lightblk_size(struct light_st *, int);

#endif
