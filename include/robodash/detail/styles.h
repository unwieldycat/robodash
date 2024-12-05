#pragma once
#include "liblvgl/lvgl.h"

#ifdef __cplusplus
extern "C" {
#endif

void create_styles();

// ========================== Animation Callbacks ========================== //

void anim_x_cb(void *obj, int32_t x);
void anim_opa_cb(void *obj, int32_t opa);
void anim_text_opa_cb(void *obj, int32_t opa);
void anim_del_cb(lv_anim_t *anim);

// ================================= Colors ================================= //

extern lv_color_t color_bg;
extern lv_color_t color_border;
extern lv_color_t color_shade;
extern lv_color_t color_primary;
extern lv_color_t color_primary_dark;
extern lv_color_t color_text;
extern lv_color_t color_red;

extern lv_color_t color_bar;
extern lv_color_t color_bar_dark;
extern lv_color_t color_bar_outline;

// ============================= Miscellaneous ============================= //

extern lv_style_t style_bg;
extern lv_style_t style_transp;
extern lv_style_t style_alert;

// ================================= Lists ================================= //

extern lv_style_t style_list;
extern lv_style_t style_list_btn;
extern lv_style_t style_list_btn_pr;

// ================================= Buttons ================================= //

extern lv_style_t style_btn;
extern lv_style_t style_btn_primary;
extern lv_style_t style_btn_primary_pr;
extern lv_style_t style_btn_outline;
extern lv_style_t style_btn_outline_pr;

// ================================== Text ================================== //

extern lv_style_t style_text_mono;
extern lv_style_t style_text_small;
extern lv_style_t style_text_medium;
extern lv_style_t style_text_large;
extern lv_style_t style_text_centered;

// ================================== Core ================================== //

extern lv_style_t style_core_button;
extern lv_style_t style_core_button_pr;
extern lv_style_t style_core_list;
extern lv_style_t style_core_list_btn;
extern lv_style_t style_core_bg;
extern lv_style_t style_core_shade;

#ifdef __cplusplus
}
#endif