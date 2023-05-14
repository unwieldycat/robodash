#include "common/styles.hpp"
#include "common/init.hpp"
#include "liblvgl/misc/lv_area.h"
#include "misc.hpp"

// ================================= Colors ================================= //

int hue = 200;

lv_color_t bg_color;
lv_color_t border_color;
lv_color_t shade_color;
lv_color_t primary_color;
lv_color_t primary_color_dark;
lv_color_t text_color;

// ================================= Styles ================================= //

lv_style_t style_bg;

lv_style_t style_list;
lv_style_t style_list_btn;
lv_style_t style_list_btn_pr;

lv_style_t style_btn;
lv_style_t style_btn_primary;
lv_style_t style_btn_primary_pr;
lv_style_t style_btn_outline;
lv_style_t style_btn_outline_pr;

lv_style_t style_text_small;
lv_style_t style_text_medium;
lv_style_t style_text_large;
lv_style_t style_text_centered;

void init_styles() {
	// Colors
	bg_color = lv_color_hsv_to_rgb(hue, 50, 10);
	border_color = lv_color_hsv_to_rgb(hue, 25, 50);
	shade_color = lv_color_hsv_to_rgb(hue, 50, 25);
	primary_color = lv_color_hsv_to_rgb(hue, 75, 100);
	primary_color_dark = lv_color_hsv_to_rgb(hue, 75, 50);
	text_color = lv_color_hsv_to_rgb(hue, 10, 100);

	// Background
	lv_style_init(&style_bg);
	lv_style_set_border_width(&style_bg, 0);
	lv_style_set_radius(&style_bg, 0);
	lv_style_set_bg_color(&style_bg, bg_color);
	lv_style_set_text_color(&style_bg, text_color);

	// List
	lv_style_init(&style_list);
	lv_style_set_border_color(&style_list, border_color);
	lv_style_set_border_width(&style_list, 1);
	lv_style_set_border_opa(&style_list, LV_OPA_COVER);
	lv_style_set_bg_color(&style_list, bg_color);
	lv_style_set_pad_ver(&style_list, 0);
	lv_style_set_pad_hor(&style_list, 8);
	lv_style_set_pad_gap(&style_list, 0);

	// List button
	lv_style_init(&style_list_btn);
	lv_style_set_border_color(&style_list_btn, border_color);
	lv_style_set_border_width(&style_list_btn, 1);
	lv_style_set_border_opa(&style_list_btn, LV_OPA_COVER);
	lv_style_set_border_side(&style_list_btn, LV_BORDER_SIDE_BOTTOM);
	lv_style_set_text_color(&style_list_btn, text_color);
	lv_style_set_radius(&style_list_btn, 0);
	lv_style_set_bg_color(&style_list_btn, bg_color);
	lv_style_set_pad_ver(&style_list_btn, 16);

	// List button pressed
	lv_style_init(&style_list_btn_pr);
	lv_style_set_bg_color(&style_list_btn_pr, shade_color);

	// Base button
	lv_style_init(&style_btn);
	lv_style_set_radius(&style_btn, 16);
	lv_style_set_img_recolor(&style_btn, bg_color);
	lv_style_set_text_color(&style_btn, text_color);

	// Primary button
	lv_style_init(&style_btn_primary);
	lv_style_set_bg_color(&style_btn_primary, primary_color);

	// Pressed primary button
	lv_style_init(&style_btn_primary_pr);
	lv_style_set_bg_color(&style_btn_primary_pr, primary_color_dark);

	// Outline button
	lv_style_init(&style_btn_outline);
	lv_style_set_border_color(&style_btn_outline, border_color);
	lv_style_set_border_width(&style_btn_outline, 1);
	lv_style_set_border_opa(&style_btn_outline, LV_OPA_COVER);
	lv_style_set_bg_color(&style_btn_outline, bg_color);
	lv_style_set_img_recolor(&style_btn_outline, text_color);
	lv_style_set_text_color(&style_btn_outline, text_color);

	// Pressed outline button
	lv_style_init(&style_btn_outline_pr);
	lv_style_set_bg_color(&style_btn_outline_pr, shade_color);

	// Small text
	lv_style_init(&style_text_small);
	lv_style_set_text_color(&style_text_small, text_color);
	lv_style_set_text_opa(&style_text_small, LV_OPA_COVER);
	lv_style_set_text_font(&style_text_small, &lv_font_montserrat_10);
	lv_style_set_text_letter_space(&style_text_small, 1);

	// Medium text
	lv_style_init(&style_text_medium);
	lv_style_set_text_color(&style_text_small, text_color);
	lv_style_set_text_opa(&style_text_small, LV_OPA_COVER);
	lv_style_set_text_font(&style_text_small, &lv_font_montserrat_14);
	lv_style_set_text_letter_space(&style_text_small, 1);

	// Large text
	lv_style_init(&style_text_large);
	lv_style_set_text_color(&style_text_small, text_color);
	lv_style_set_text_opa(&style_text_small, LV_OPA_COVER);
	lv_style_set_text_font(&style_text_small, &lv_font_montserrat_20);
	lv_style_set_text_letter_space(&style_text_small, 1);

	// Text align
	lv_style_init(&style_text_centered);
	lv_style_set_text_align(&style_text_centered, LV_ALIGN_CENTER);
}

// ============================ Public Functions ============================ //

void gui::theme::set_hue(int new_hue) {
	hue = new_hue;

	// Rebuild styles and notify lvgl to refresh all objects
	init_styles();
	lv_obj_report_style_change(NULL);
}