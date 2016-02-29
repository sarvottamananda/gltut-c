#ifndef Z_PVM_H_INCLUDED
#define Z_PVM_H_INCLUDED

extern void pvm_calculate_model_mat4(GLfloat[][4], GLfloat[3], GLfloat[3],
				     GLfloat[3], GLfloat);
extern void pvm_calculate_view_mat4(GLfloat[][4], GLfloat[3], GLfloat[3],
				    GLfloat[3]);
extern void pvm_calculate_proj_mat4(GLfloat[][4], GLfloat, GLfloat,
				    GLfloat, GLfloat);

extern GLfloat degtorad(GLfloat);
extern GLfloat radtodeg(GLfloat);

#endif
