#pragma once
#include "../../display/lvgl.h"

extern lv_style_t bg_style;
extern lv_style_t cont_style;

extern lv_style_t list_style_bg;
extern lv_style_t list_btn_style_rel;
extern lv_style_t list_btn_style_pr;
extern lv_style_t list_btn_style_ina;

extern lv_style_t win_style_header;
extern lv_style_t win_style_content_bg;

extern lv_style_t btn_style_rel;
extern lv_style_t btn_style_pr;
extern lv_style_t btn_style_ina;

void init_styles();
