#pragma once
#include "liblvgl/lvgl.h"
#include "robodash/view.hpp"

extern lv_obj_t *view_cont;
extern lv_obj_t *view_list;
extern lv_obj_t *alert_cont;

extern lv_obj_t *anim_label;
extern lv_obj_t *shade;

extern lv_anim_t anim_shade_show;
extern lv_anim_t anim_shade_hide;

extern rd::View *current_view;

void view_focus_cb(lv_event_t *event);
void close_cb(lv_event_t *event);

void hide_menu();
void show_menu();

void hide_shade();
void show_shade();

bool valid_view(rd::View *view);
void initialize();
