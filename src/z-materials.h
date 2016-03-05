#ifndef Z_MATERIALS_H_INCLUDED
#define Z_MATERIALS_H_INCLUDED

enum material_enum {
    MATERIAL_NONE, MATERIAL_WHITE, MATERIAL_BLACK,
    MATERIAL_RED, MATERIAL_GREEN, MATERIAL_BLUE,
    MATERIAL_YELLOW, MATERIAL_MAGENTA, MATERIAL_CYAN,
    MATERIAL_MAX
};

enum color_en {
    COLOR_NONE,
    COLOR_WHITE, COLOR_BLACK,
    COLOR_RED, COLOR_GREEN, COLOR_BLUE,
    COLOR_1000, COLOR_0100, COLOR_0010, COLOR_0001,
    COLOR_YELLOW, COLOR_MAGENTA, COLOR_CYAN,
    COLOR_ORANGE, COLOR_PINK, COLOR_LEMON_YELLOW,
    COLOR_LEMON_GREEN, COLOR_PURPLE, COLOR_SEABLUE,

    COLOR_DARKRED, COLOR_DARKGREEN, COLOR_DARKBLUE,
    COLOR_DARKYELLOW, COLOR_DARKMAGENTA, COLOR_DARKCYAN,

    COLOR_GRAY,

    COLOR_LIGHTRED, COLOR_LIGHTGREEN, COLOR_LIGHTBLUE,
    COLOR_LIGHTYELLOW, COLOR_LIGHTMAGENTA, COLOR_LIGHTCYAN,

    COLOR_MAX
};

enum color_type_en {
    COLOR_TYPE_NONE,
    COLOR_TYPE_SIMPLE,
    COLOR_TYPE_TEXTURE,
    COLOR_TYPE_TEXTURE_COMPLEX,
    COLOR_TYPE_TEXTURE_TEXTURE,
    COLOR_TYPE_TEXTURE_TEXTURE_COMPLEX,
    COLOR_TYPE_MAX
};

struct texture_st;

struct material_st {
    int id;
    char *name;
    struct matblk_st {
	GLfloat ambient[3];
	GLfloat _pad1;
	GLfloat diffuse[3];
	GLfloat _pad2;
	GLfloat specular[3];
	GLfloat _pad3;
	GLfloat texorigin[2];
	GLfloat texsize[2];
	GLfloat shininess;
	GLfloat opacity;
    } matblk;

    struct texture_st *tex;

    int matblk_offset;
    int matblk_size;
};

extern struct material_st *mtrl_get_std_material(int);
extern void mtrl_set_matblk_offset(struct material_st *, int);
extern void mtrl_set_matblk_size(struct material_st *, int);
extern void mtrl_get_std_color(float[], int);

extern struct material_st *mtrl_new_material(int);
extern void mtrl_delete_material(struct material_st *);
extern void mtrl_set_texcoords(struct material_st *, float, float,
			       float, float);
extern void mtrl_set_name(struct material_st *m, char *name);

extern void mtrl_copy(struct material_st *dst, struct material_st *src);
extern void mtrl_set_ambient(struct material_st *m, float r, float g,
			     float b, float a);
extern void mtrl_set_diffuse(struct material_st *m, float r, float g,
			     float b, float a);
extern void mtrl_set_specular(struct material_st *m, float r, float g,
			      float b, float a);
extern void mtrl_set_shininess(struct material_st *m, float s);

extern void mtrl_init(void);

extern void mtrl_print(struct material_st *mat);

#endif
