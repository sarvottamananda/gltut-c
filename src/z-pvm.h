#ifndef Z_PVM_H_INCLUDED
#define Z_PVM_H_INCLUDED

extern void pvm_compute_translate_mat4(float res[4][4], float sc[3]);
extern void pvm_compute_scale_mat4(float res[4][4], float sc[3]);
extern void pvm_compute_rotate_mat4(float res[4][4], float rot[3], float th);

extern void pvm_compute_model_mat4(float res[4][4], float tr[3], float sc[3],
				     float rot[3], float ang);
extern void pvm_compute_view_mat4(float res[4][4], float eye[3], float target[3],
				    float up[3]);
extern void pvm_compute_proj_mat4(float[4][4], float a, float th,
				    float zn, float zf);

#endif
