#pragma once
#include "liblvgl/lvgl.h"

extern void _init_styles();

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

extern lv_color_t color_bar;
extern lv_color_t color_bar_dark;
extern lv_color_t color_bar_outline;

extern void _init_colors();

// ============================= Miscellaneous ============================= //

extern lv_style_t style_bg;
extern lv_style_t style_transp;

extern void _init_style_misc();

// ================================= Lists ================================= //

extern lv_style_t style_list;
extern lv_style_t style_list_btn;
extern lv_style_t style_list_btn_pr;

extern void _init_style_list();

// ================================= Buttons ================================= //

extern lv_style_t style_btn;
extern lv_style_t style_btn_primary;
extern lv_style_t style_btn_primary_pr;
extern lv_style_t style_btn_outline;
extern lv_style_t style_btn_outline_pr;

extern void _init_style_btn();

// ================================== Text ================================== //

extern lv_style_t style_text_mono;
extern lv_style_t style_text_small;
extern lv_style_t style_text_medium;
extern lv_style_t style_text_large;
extern lv_style_t style_text_centered;

extern void _init_style_text();

// ================================ Sidebar ================================ //

extern lv_style_t style_bar_button;
extern lv_style_t style_bar_button_pr;
extern lv_style_t style_bar_list;
extern lv_style_t style_bar_list_btn;
extern lv_style_t style_bar_bg;
extern lv_style_t style_bar_modal;

extern void _init_style_bar();