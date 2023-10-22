#include "robodash/apix.hpp"
#include <inttypes.h>

// ========================== Animation Callbacks ========================== //

void anim_x_cb(void *obj, int32_t x) { lv_obj_set_x((lv_obj_t *)obj, x); }

void anim_opa_cb(void *obj, int32_t opa) { lv_obj_set_style_bg_opa((lv_obj_t *)obj, opa, 0); }

void anim_text_opa_cb(void *obj, int32_t opa) {
	lv_obj_set_style_text_opa((lv_obj_t *)obj, opa, 0);
}

void anim_del_cb(lv_anim_t *anim) { lv_obj_add_flag((lv_obj_t *)anim->var, LV_OBJ_FLAG_HIDDEN); }