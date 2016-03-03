#include <stdio.h>
#include <GL/glew.h>
#include <math.h>

#include "z-main.h"
#include "z-shader.h"
#include "z-pvm.h"
#include "z-png.h"
#include "z-models.h"
#include "z-materials.h"
#include "z-camera.h"
#include "z-world.h"
#include "z-mat.h"
#include "z-light.h"
#include "z-geom.h"

#include "debug.h"

#define MAXLIGHTS 4

static GLuint plain_progid = 0;
static GLuint texture_progid = 0;

static GLuint position_loc = -1;
static GLuint normal_loc = -1;
static GLuint tc_loc = -1;

static GLuint vao[2] = { 0, 0 };

static struct dlist_hdr *list_objects = NULL;
static struct dlist_hdr *list_models = NULL;
static struct dlist_hdr *list_materials = NULL;

static struct object_st *cube = NULL;
static struct object_st *sphere1 = NULL;
static struct object_st *sphere2 = NULL;
static struct object_st *sphere3 = NULL;
static struct object_st *sphere4 = NULL;
static struct object_st *sphere5 = NULL;
static struct object_st *checker = NULL;
static struct object_st *light_obj[MAXLIGHTS];

static struct scene_st *sc = NULL;
static struct light_st *lights = NULL;

GLuint ubo_model = 0;
GLuint ubo_scene = 0;
GLuint ubo_material = 0;
GLuint ubo_light = 0;

GLint modelblk_sz = 0;
GLint sceneblk_sz = 0;
GLint materialblk_sz = 0;
GLint lightblk_sz = 0;

GLint modelblk_bpoint = 0;
GLint sceneblk_bpoint = 0;
GLint matblk_bpoint = 0;
GLint lightblk_bpoint = 0;

GLint UniformBufferOffset = 0;

void setshaders(void)
{
    GLuint shader[3];

    shader[0] =
	opengl_createshader(GL_VERTEX_SHADER, "shaders/tut5-plain.vert");
    shader[1] =
	opengl_createshader(GL_FRAGMENT_SHADER, "shaders/tut5-plain.frag");
    shader[2] =
	opengl_createshader(GL_FRAGMENT_SHADER, "shaders/tut5-texture.frag");
    shader[3] = 0;

    GLuint plain_shlist[] = { 0, 1, -1 };

    plain_progid = opengl_createprogram(shader, plain_shlist);

    GLuint texture_shlist[] = { 0, 2, -1 };

    texture_progid = opengl_createprogram(shader, texture_shlist);
}

#define BUFFER_OFFSET(off) ((void *)(NULL+off))

int checkattrlocs(int progid, int *loc, char **name)
{
    int okay = 1;
    int i = 0;
    while (loc[i] >= 0) {
	int lc = glGetAttribLocation(progid, name[i]);

	DBG_TRACE(0, "Attribute Loc: %d %s expect(%d)", lc, name[i], loc[i]);

	if ((lc != -1) && (lc != loc[i])) {
	    okay = 0;
	    break;
	}
	i++;
    };

    if (!okay) {
	perror("Attribute locations do not match in shaders and application.");
    }
    return okay;
}

void setvaos(void)
{
    GLuint vbo = 0;

    GLint MaxVertexAttribs = 0;

    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &MaxVertexAttribs);

    DBG_TRACE(0, "Max vertex attribs: %d", MaxVertexAttribs);

    int locs[] = { 0, 1, 2, -1 };
    char *attrs[] = { "vposition", "vtcoord", "vnormal", NULL };

    checkattrlocs(plain_progid, locs, attrs);
    checkattrlocs(texture_progid, locs, attrs);

    position_loc = 0;
    tc_loc = 1;
    normal_loc = 2;

    glGenVertexArrays(1, vao);

    glBindVertexArray(vao[0]);

    // Generate 1 buffer, put the resulting identifier in vbid
    glGenBuffers(1, &vbo);
    // The following commands will talk about our 'vbid' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    struct dlist_st *mdl = NULL;
    GLint vcount = 0;

    for (mdl = list_models->first; mdl != NULL; mdl = mdl->next) {
	vcount += ((struct model_st *)mdl->data)->vcount;

    }

    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER,
		 sizeof(GLfloat) * (4 + 2 + 3) * vcount, NULL, GL_STATIC_DRAW);

    GLint offset = 0;
    GLint cnt = 0;
    struct vbuf_st *data = NULL;

    GLint num = 0;
    for (mdl = list_models->first; mdl != NULL; mdl = mdl->next) {
	cnt = ((struct model_st *)mdl->data)->vcount;
	data = ((struct model_st *)mdl->data)->vbuf;

	mdl_set_vbo_offset(mdl->data, num);
	mdl_set_vbo_start(mdl->data, num);
	DBG_TRACE(0, "Vcount: %d", cnt);
	DBG_TRACE(0, "Voffset: %d", offset);

	glBufferSubData(GL_ARRAY_BUFFER, offset,
			sizeof(struct vbuf_st) * cnt, data);

	offset += sizeof(struct vbuf_st) * cnt;
	num += cnt;
    }

    if (position_loc >= 0)
	glVertexAttribPointer(position_loc, 4, GL_FLOAT, GL_FALSE,
			      sizeof(struct vbuf_st), BUFFER_OFFSET(0));

    if (tc_loc >= 0)
	glVertexAttribPointer(tc_loc, 2, GL_FLOAT, GL_FALSE,
			      sizeof(struct vbuf_st),
			      BUFFER_OFFSET(4 * sizeof(GLfloat)));

    if (normal_loc >= 0)
	glVertexAttribPointer(normal_loc, 3, GL_FLOAT, GL_FALSE,
			      sizeof(struct vbuf_st),
			      BUFFER_OFFSET(6 * sizeof(GLfloat)));

    if (position_loc >= 0)
	glEnableVertexAttribArray(position_loc);
    if (tc_loc >= 0)
	glEnableVertexAttribArray(tc_loc);
    if (normal_loc >= 0)
	glEnableVertexAttribArray(normal_loc);

    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindVertexArray(0);
}

void setuniforms_modelblk(void)
{
    // Models specific
    glBindBuffer(GL_UNIFORM_BUFFER, ubo_model);

    modelblk_sz = sizeof(struct modelblk_st);

    GLint realblk_sz = modelblk_sz;

    if (modelblk_sz % UniformBufferOffset != 0) {
	realblk_sz =
	    modelblk_sz + UniformBufferOffset -
	    modelblk_sz % UniformBufferOffset;
    }

    int count = list_objects->size;
    glBufferData(GL_UNIFORM_BUFFER, realblk_sz * count, NULL, GL_DYNAMIC_DRAW);

    int modelblk_offset = 0;
    struct dlist_st *ol = NULL;
    for (ol = list_objects->first; ol != NULL; ol = ol->next) {
	struct object_st *obj = ol->data;

	calculate_model_mat4(obj);
	calculate_normal_mat4(obj);

	if (modelblk_offset % UniformBufferOffset != 0) {
	    modelblk_offset +=
		UniformBufferOffset - modelblk_offset % UniformBufferOffset;
	}
	obj_set_modelblk_offset(obj, modelblk_offset);
	obj_set_modelblk_size(obj, modelblk_sz);

	DBG_TRACE(0, "modelblk_offset: %d %d %d", modelblk_offset,
		  modelblk_sz, sizeof(obj->modelblk));

	glBufferSubData(GL_UNIFORM_BUFFER, modelblk_offset, modelblk_sz,
			&(obj->modelblk));
	modelblk_offset += realblk_sz;

    }

    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    GLuint bindex = 0;
    GLuint bpoint = 0;

    bpoint = modelblk_bpoint = 0;

    bindex = glGetUniformBlockIndex(plain_progid, "ModelBlock");
    glUniformBlockBinding(plain_progid, bindex, bpoint);

    bindex = glGetUniformBlockIndex(texture_progid, "ModelBlock");
    glUniformBlockBinding(texture_progid, bindex, bpoint);

}

void setuniforms_sceneblk(void)
{
    // Camera specific
    glBindBuffer(GL_UNIFORM_BUFFER, ubo_scene);

    calculate_view_mat4(sc);
    calculate_proj_mat4(sc);

    sceneblk_sz = sizeof(sc->sceneblk);
    GLint realblk_sz = sceneblk_sz;
    if (sceneblk_sz % UniformBufferOffset != 0) {
	realblk_sz =
	    sceneblk_sz + UniformBufferOffset -
	    sceneblk_sz % UniformBufferOffset;
    }
    GLint sz = realblk_sz;

    glBufferData(GL_UNIFORM_BUFFER, sz, NULL, GL_DYNAMIC_DRAW);

    GLint sceneblk_offset = 0;

    sc->sceneblk_size = sceneblk_sz;
    sc->sceneblk_offset = sceneblk_offset;

    print_mat4("View Mat4", sc->sceneblk.viewmat);
    print_mat4("Projection Mat4", sc->sceneblk.projmat);

    glBufferSubData(GL_UNIFORM_BUFFER, sceneblk_offset, sceneblk_sz,
		    &(sc->sceneblk));

    sceneblk_offset += realblk_sz;

    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    GLuint bindex = 0;
    GLuint bpoint = 0;

    bpoint = sceneblk_bpoint = 1;

    bindex = glGetUniformBlockIndex(plain_progid, "SceneBlock");
    glUniformBlockBinding(plain_progid, bindex, bpoint);

    bindex = glGetUniformBlockIndex(texture_progid, "SceneBlock");
    glUniformBlockBinding(texture_progid, bindex, bpoint);

}

void setuniforms_materialsblk(void)
{
    // Materials specific
    glBindBuffer(GL_UNIFORM_BUFFER, ubo_material);

    struct dlist_st *ml = NULL;

    materialblk_sz = sizeof(struct matblk_st);
    GLint realblk_sz = materialblk_sz;
    if (materialblk_sz % UniformBufferOffset != 0) {
	realblk_sz =
	    materialblk_sz + UniformBufferOffset -
	    materialblk_sz % UniformBufferOffset;
    }

    GLint sz = 0;

    for (ml = list_materials->first; ml != NULL; ml = ml->next) {
	sz += realblk_sz;
    }
    glBufferData(GL_UNIFORM_BUFFER, sz, NULL, GL_DYNAMIC_DRAW);

    int matblk_offset = 0;

    for (ml = list_materials->first; ml != NULL; ml = ml->next) {
	struct material_st *mat;

	mat = (struct material_st *)ml->data;

	if (matblk_offset % UniformBufferOffset != 0) {
	    matblk_offset +=
		UniformBufferOffset - matblk_offset % UniformBufferOffset;
	}
	mtrl_set_matblk_offset(mat, matblk_offset);
	mtrl_set_matblk_size(mat, materialblk_sz);

	glBufferSubData(GL_UNIFORM_BUFFER, matblk_offset, materialblk_sz,
			&(mat->matblk));
	matblk_offset += realblk_sz;
    }

    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    GLuint bindex = 0;
    GLuint bpoint = 0;

    bpoint = matblk_bpoint = 2;
    bindex = glGetUniformBlockIndex(plain_progid, "MaterialBlock");
    glUniformBlockBinding(plain_progid, bindex, bpoint);

    bindex = glGetUniformBlockIndex(texture_progid, "MaterialBlock");
    glUniformBlockBinding(texture_progid, bindex, bpoint);

}

void setuniforms_lightblk(void)
{
    // Lighting specific
    glBindBuffer(GL_UNIFORM_BUFFER, ubo_light);

    lightblk_sz = sizeof(struct lightblk_st);
    GLint realblk_sz = lightblk_sz;
    if (lightblk_sz % UniformBufferOffset != 0) {
	realblk_sz =
	    lightblk_sz + UniformBufferOffset -
	    lightblk_sz % UniformBufferOffset;
    }
    GLint sz = realblk_sz;
    glBufferData(GL_UNIFORM_BUFFER, sz, NULL, GL_DYNAMIC_DRAW);

    int lightblk_offset = 0;

    struct lightblk_st *lblk = &(lights->lightblk);
    print_vec3("Amb", lblk->ambience);
    for (int i = 0; i < MAXLIGHTS; i++) {
	print_vec3("Lt_pos", lblk->pos[i]);
    }
    for (int i = 0; i < MAXLIGHTS; i++) {
	print_vec3("Lt_em", lblk->emission[i]);
    }
    printf("N:%d\n", lblk->num);

    DBG_TRACE(0, "Lightblk_st: %d,%d", lightblk_offset, lightblk_sz);

    light_set_lightblk_offset(lights, lightblk_offset);
    light_set_lightblk_size(lights, lightblk_sz);

    glBufferSubData(GL_UNIFORM_BUFFER, lightblk_offset, lightblk_sz,
		    &(lights->lightblk));
    lightblk_offset += realblk_sz;

    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    GLuint bindex = 0;
    GLuint bpoint = 0;

    bpoint = lightblk_bpoint = 3;
    bindex = glGetUniformBlockIndex(plain_progid, "LightBlock");
    glUniformBlockBinding(plain_progid, bindex, bpoint);

    bindex = glGetUniformBlockIndex(texture_progid, "LightBlock");
    glUniformBlockBinding(texture_progid, bindex, bpoint);

}

void setuniforms(void)
{
    GLuint ubo[4];

    glGenBuffers(4, ubo);

    ubo_model = ubo[0];
    ubo_scene = ubo[1];
    ubo_material = ubo[2];
    ubo_light = ubo[3];

    glGetIntegerv(GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT, &UniformBufferOffset);

    DBG_TRACE(0, "Align: %d", UniformBufferOffset);

    // Models specific
    setuniforms_modelblk();

    // Camera specific
    setuniforms_sceneblk();

    // Materials specific
    setuniforms_materialsblk();

    // Lighting specific
    setuniforms_lightblk();
}

void settextures(void)
{
    GLuint tid[2];

    glGenTextures(2, tid);

    GLuint tid_base = tid[0];
    GLuint tid_text = tid[1];

    struct image_st image_txt;
    struct image_st image_grass;
    int width = 0;
    int height = 0;
    int num_mipmaps = 8;
    void *gpixels, *tpixels;

    png_read_file("textures/grass2.png", &image_grass);
    png_read_file("textures/abcd1234.png", &image_txt);

    width = image_grass.width;
    height = image_grass.height;
    gpixels = image_grass.pixels;

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tid_base);

    glTexStorage2D(GL_TEXTURE_2D, num_mipmaps, GL_RGBA8, width, height);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_BGRA,
		    GL_UNSIGNED_BYTE, gpixels);
    // Generate num_mipmaps number of mipmaps here.
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		    GL_LINEAR_MIPMAP_LINEAR);

    width = image_txt.width;
    height = image_txt.height;
    tpixels = image_txt.pixels;

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, tid_text);

    glTexStorage2D(GL_TEXTURE_2D, num_mipmaps, GL_RGBA8, width, height);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_BGRA,
		    GL_UNSIGNED_BYTE, tpixels);
    // Generate num_mipmaps number of mipmaps here.
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		    GL_LINEAR_MIPMAP_LINEAR);

    glActiveTexture(GL_TEXTURE0);

    DBG_TRACE(0, "Setting Textures");
    glUseProgram(texture_progid);

    GLuint baseloc = glGetUniformLocation(texture_progid, "basetex");
    GLuint textloc = glGetUniformLocation(texture_progid, "texttex");

    DBG_TRACE(0, "Texlocs %d %d\n", baseloc, textloc);

    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D, tid_base);

    // glActiveTexture(GL_TEXTURE1);
    // glBindTexture(GL_TEXTURE_2D, tid_text);

    glUniform1i(baseloc, 0);
    glUniform1i(textloc, 1);

    png_free_image(&image_grass);
    png_free_image(&image_txt);
}

void objects_init(void)
{
    cube = obj_create_object("red cube", mdl_get_std_model(MODEL_CUBE),
			     mtrl_get_std_material(MATERIAL_RED)
	);

    obj_abs_translate(cube, 0.0f, 0.0f, 0.0f);
    obj_abs_scale(cube, 0.5f, 0.5f, 0.5f);
    obj_abs_rotate(cube, 1.0f, 1.0f, 1.0f, degtorad(0.0f));

    dl_search_and_insert(list_models, cube->model);
    dl_search_and_insert(list_materials, cube->material);
    dl_search_and_insert(list_objects, cube);

    struct model_st *sp_model = mdl_create_sphere_stripped(40, 40, 0.0,
							   4.0, 0.0, 4.0);
    struct material_st *sp_material = mtrl_new_material(5);
    struct material_st *cyan_material = mtrl_get_std_material(MATERIAL_GREEN);

    for (int i = 0; i < 5; i++) {
	double a = 0.5;
	double b = 0.1;
	mtrl_copy(&sp_material[i], cyan_material);
	mtrl_set_specular(&sp_material[i], a + i * b, a + i * b, a + i * b,
			  a + i * b);
	//mtrl_set_specular(&sp_material[i], 1.0, 1.0, 1.0, 1.0);
	mtrl_set_shininess(&sp_material[i], i * 4.0);
    }

    sphere1 = obj_create_object("sphere1", sp_model, &sp_material[0]);
    obj_abs_scale(sphere1, 0.5f, 0.5f, 0.5f);
    obj_abs_translate(sphere1, -3.0f, -1.0f, 1.0f);

    sphere2 = obj_create_object("sphere2", sp_model, &sp_material[1]);
    obj_abs_scale(sphere2, 0.5f, 0.5f, 0.5f);
    obj_abs_translate(sphere2, -2.0f, 0.0f, 1.0f);

    sphere3 = obj_create_object("sphere3", sp_model, &sp_material[2]);
    obj_abs_scale(sphere3, 0.5f, 0.5f, 0.5f);
    obj_abs_translate(sphere3, -1.0f, 1.0f, 1.0f);

    sphere4 = obj_create_object("sphere4", sp_model, &sp_material[3]);
    obj_abs_scale(sphere4, 0.5f, 0.5f, 0.5f);
    obj_abs_translate(sphere4, 0.0f, 2.0f, 1.0f);

    sphere5 = obj_create_object("sphere5", sp_model, &sp_material[4]);
    obj_abs_scale(sphere5, 0.5f, 0.5f, 0.5f);
    obj_abs_translate(sphere5, 1.0f, 3.0f, 1.0f);

    dl_search_and_insert(list_models, sp_model);
    for (int i = 0; i < 5; i++) {
	dl_search_and_insert(list_materials, &sp_material[i]);
    }
    dl_search_and_insert(list_objects, sphere1);
    dl_search_and_insert(list_objects, sphere2);
    dl_search_and_insert(list_objects, sphere3);
    dl_search_and_insert(list_objects, sphere4);
    dl_search_and_insert(list_objects, sphere5);

    struct material_st *ggrass = mtrl_new_material(1);
    mtrl_set_name(ggrass, "green grass");
    mtrl_set_texcoords(ggrass, 0.0, 0.0, 0.5, 1.0);

    struct model_st *model = mdl_create_checker_stripped(16, 16, 0.0,
							 4.0, 0.0, 4.0);
    checker = obj_create_object("checker", model, ggrass);

    DBG_TRACE(0, "Texture coords: %f %f %f %f",
	      ggrass->matblk.texorigin[0],
	      ggrass->matblk.texorigin[1],
	      ggrass->matblk.texsize[0], ggrass->matblk.texsize[1]);

    obj_abs_translate(checker, -32.0f, -32.0f, 0.0f);
    obj_abs_scale(checker, 64.0f, 64.0f, 64.0f);
    obj_abs_rotate(checker, 1.0f, 1.0f, 1.0f, degtorad(0.0f));

    dl_search_and_insert(list_models, checker->model);
    dl_search_and_insert(list_materials, checker->material);
    dl_search_and_insert(list_objects, checker);

    for (int i = 0; i < lights->lightblk.num; i++) {
	light_obj[i] = obj_create_object("light obj",
					 mdl_get_std_model(MODEL_POINT),
					 mtrl_get_std_material(MATERIAL_WHITE));
	dl_search_and_insert(list_objects, light_obj[i]);

	obj_abs_translate(light_obj[i],
			  lights->lightblk.pos[i][0],
			  lights->lightblk.pos[i][1],
			  lights->lightblk.pos[i][2] - 0.01);
	obj_abs_scale(light_obj[i], 1.0, 1.0, 1.0);
	obj_abs_rotate(light_obj[i], 1.0f, 1.0f, 1.0f, degtorad(0.0f));
    }
    dl_search_and_insert(list_models, mdl_get_std_model(MODEL_POINT));
    dl_search_and_insert(list_materials, mtrl_get_std_material(MATERIAL_WHITE));

}

void main_init(void)
{

    list_objects = dl_create();
    list_models = dl_create();
    list_materials = dl_create();

    world_init(1024.0f, 1024.0f, 1024.0f);
    mdl_init();
    mtrl_init();

    sc = camera_create_scene();
    camera_init(sc);

    lights = light_create_light();
    light_init(lights);
    objects_init();

    setshaders();
    setvaos();

    setuniforms();
    settextures();

    glBindBufferRange(GL_UNIFORM_BUFFER, sceneblk_bpoint, ubo_scene, 0,
		      sceneblk_sz);
    glBindBufferRange(GL_UNIFORM_BUFFER, lightblk_bpoint, ubo_light, 0,
		      lightblk_sz);

    DBG_TRACE(0, "Model %d %d", checker->model->vbo_offset,
	      checker->model->vcount);
    DBG_TRACE(0, "Model %d %d", light_obj[0]->model->vbo_offset,
	      light_obj[0]->model->vcount);
}

void main_draw(void)
{

    // Draw the triangle 1 !
    glBindVertexArray(vao[0]);

    // glDrawArrays(GL_TRIANGLES, 0, 6);
    // glDrawArrays(GL_TRIANGLES, 6, 6);
    // glDrawArrays(GL_TRIANGLES, 12, 6);
    // glDrawArrays(GL_TRIANGLES, 18, 6);
    // glDrawArrays(GL_TRIANGLES, 24, 6);
    // glDrawArrays(GL_TRIANGLES, 30, 6);

    struct object_st *obj = NULL;
    struct model_st *model = NULL;
    struct material_st *material = NULL;

    glUseProgram(plain_progid);

    obj = cube;
    model = obj->model;
    glBindBufferRange(GL_UNIFORM_BUFFER, modelblk_bpoint, ubo_model,
		      obj->modelblk_offset, modelblk_sz);
    material = obj->material;
    glBindBufferRange(GL_UNIFORM_BUFFER, matblk_bpoint, ubo_material,
		      material->matblk_offset, materialblk_sz);
    glMultiDrawArrays(model->draw_mode, model->vbo_start, model->count,
		      model->num);

    obj = sphere1;
    model = obj->model;
    glBindBufferRange(GL_UNIFORM_BUFFER, modelblk_bpoint, ubo_model,
		      obj->modelblk_offset, modelblk_sz);
    material = obj->material;
    glBindBufferRange(GL_UNIFORM_BUFFER, matblk_bpoint, ubo_material,
		      material->matblk_offset, materialblk_sz);
    glMultiDrawArrays(model->draw_mode, model->vbo_start, model->count,
		      model->num);

    obj = sphere2;
    model = obj->model;
    glBindBufferRange(GL_UNIFORM_BUFFER, modelblk_bpoint, ubo_model,
		      obj->modelblk_offset, modelblk_sz);
    material = obj->material;
    glBindBufferRange(GL_UNIFORM_BUFFER, matblk_bpoint, ubo_material,
		      material->matblk_offset, materialblk_sz);
    glMultiDrawArrays(model->draw_mode, model->vbo_start, model->count,
		      model->num);

    obj = sphere3;
    model = obj->model;
    glBindBufferRange(GL_UNIFORM_BUFFER, modelblk_bpoint, ubo_model,
		      obj->modelblk_offset, modelblk_sz);
    material = obj->material;
    glBindBufferRange(GL_UNIFORM_BUFFER, matblk_bpoint, ubo_material,
		      material->matblk_offset, materialblk_sz);
    glMultiDrawArrays(model->draw_mode, model->vbo_start, model->count,
		      model->num);

    obj = sphere4;
    model = obj->model;
    glBindBufferRange(GL_UNIFORM_BUFFER, modelblk_bpoint, ubo_model,
		      obj->modelblk_offset, modelblk_sz);
    material = obj->material;
    glBindBufferRange(GL_UNIFORM_BUFFER, matblk_bpoint, ubo_material,
		      material->matblk_offset, materialblk_sz);
    glMultiDrawArrays(model->draw_mode, model->vbo_start, model->count,
		      model->num);

    obj = sphere5;
    model = obj->model;
    glBindBufferRange(GL_UNIFORM_BUFFER, modelblk_bpoint, ubo_model,
		      obj->modelblk_offset, modelblk_sz);
    material = obj->material;
    glBindBufferRange(GL_UNIFORM_BUFFER, matblk_bpoint, ubo_material,
		      material->matblk_offset, materialblk_sz);
    glMultiDrawArrays(model->draw_mode, model->vbo_start, model->count,
		      model->num);

    for (int i = 0; i < lights->lightblk.num; i++) {
	obj = light_obj[i];
	model = obj->model;
	material = obj->material;
	glBindBufferRange(GL_UNIFORM_BUFFER, modelblk_bpoint, ubo_model,
			  obj->modelblk_offset, modelblk_sz);
	glBindBufferRange(GL_UNIFORM_BUFFER, matblk_bpoint, ubo_material,
			  material->matblk_offset, materialblk_sz);
	glMultiDrawArrays(model->draw_mode, model->vbo_start, model->count,
			  model->num);
    }

    glUseProgram(texture_progid);

    obj = checker;
    model = obj->model;
    glBindBufferRange(GL_UNIFORM_BUFFER, modelblk_bpoint, ubo_model,
		      obj->modelblk_offset, modelblk_sz);
    material = obj->material;
    glBindBufferRange(GL_UNIFORM_BUFFER, matblk_bpoint, ubo_material,
		      material->matblk_offset, materialblk_sz);
    glMultiDrawArrays(model->draw_mode, model->vbo_start, model->count,
		      model->num);

    glBindVertexArray(0);
}
