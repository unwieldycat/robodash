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

// TODO: Take advantage of cascading styles, seperate text styles from object styles

lv_style_t bg_style;
lv_style_t list_style;
lv_style_t list_btn_style_rel;
lv_style_t list_btn_style_pr;
lv_style_t round_btn_style_rel;
lv_style_t round_btn_style_pr;
lv_style_t outline_round_btn_style_rel;
lv_style_t outline_round_btn_style_pr;
lv_style_t small_text;
lv_style_t transp_style;

lv_style_t text_centered;

void init_styles() {
	// Colors
	bg_color = lv_color_hsv_to_rgb(hue, 50, 10);
	border_color = lv_color_hsv_to_rgb(hue, 25, 50);
	shade_color = lv_color_hsv_to_rgb(hue, 50, 25);
	primary_color = lv_color_hsv_to_rgb(hue, 75, 100);
	primary_color_dark = lv_color_hsv_to_rgb(hue, 75, 50);
	text_color = lv_color_hsv_to_rgb(hue, 10, 100);

	// Background style
	lv_style_init(&bg_style);
	lv_style_set_border_width(&bg_style, 0);
	lv_style_set_radius(&bg_style, 0);
	lv_style_set_bg_color(&bg_style, bg_color);
	lv_style_set_text_color(&bg_style, text_color);

	// List style
	lv_style_init(&list_style);
	lv_style_set_border_color(&list_style, border_color);
	lv_style_set_border_width(&list_style, 1);
	lv_style_set_border_opa(&list_style, LV_OPA_COVER);
	lv_style_set_bg_color(&bg_style, bg_color);
	lv_style_set_pad_ver(&bg_style, 0);
	lv_style_set_pad_hor(&bg_style, 8);
	lv_style_set_pad_gap(&bg_style, 0);

	// List button released style
	lv_style_init(&list_btn_style_rel);
	lv_style_set_border_color(&list_btn_style_rel, border_color);
	lv_style_set_border_width(&list_btn_style_rel, 1);
	lv_style_set_border_opa(&list_btn_style_rel, LV_OPA_COVER);
	lv_style_set_border_side(&list_btn_style_rel, LV_BORDER_SIDE_BOTTOM);
	lv_style_set_text_color(&list_btn_style_rel, text_color);
	lv_style_set_radius(&list_btn_style_rel, 0);
	lv_style_set_bg_color(&list_btn_style_rel, bg_color);
	lv_style_set_pad_ver(&list_btn_style_rel, 16);

	// List button pressed style
	lv_style_init(&list_btn_style_pr);
	lv_style_set_bg_color(&list_btn_style_pr, shade_color);
	lv_style_set_pad_ver(&list_btn_style_pr, 16);
	lv_style_set_radius(&list_btn_style_pr, 0);
	lv_style_set_text_color(&list_btn_style_pr, text_color);

	// Released rounded button style
	lv_style_init(&round_btn_style_rel);
	lv_style_set_bg_color(&round_btn_style_rel, primary_color);
	lv_style_set_radius(&round_btn_style_rel, 16);
	lv_style_set_img_recolor(&round_btn_style_rel, bg_color);
	lv_style_set_text_color(&round_btn_style_rel, text_color);

	// Pressed rounded button style
	lv_style_init(&round_btn_style_pr);
	lv_style_set_bg_color(&round_btn_style_pr, primary_color_dark);

	// Released outline rounded button style
	lv_style_init(&outline_round_btn_style_rel);
	lv_style_set_border_color(&list_btn_style_rel, border_color);
	lv_style_set_border_width(&list_btn_style_rel, 1);
	lv_style_set_border_opa(&list_btn_style_rel, LV_OPA_COVER);
	lv_style_set_bg_color(&round_btn_style_rel, bg_color);
	lv_style_set_img_recolor(&outline_round_btn_style_rel, text_color);
	lv_style_set_text_color(&outline_round_btn_style_rel, text_color);

	// Pressed outline rounded button style
	lv_style_init(&outline_round_btn_style_pr);
	lv_style_set_bg_color(&round_btn_style_pr, shade_color);

	// Small text style
	lv_style_init(&small_text);
	lv_style_set_text_color(&small_text, text_color);
	lv_style_set_text_opa(&small_text, LV_OPA_COVER);
	lv_style_set_text_font(&small_text, &lv_font_montserrat_14);
	lv_style_set_text_letter_space(&small_text, 1);

	// Transparent style
	lv_style_init(&transp_style);
	lv_style_set_text_color(&transp_style, text_color);
	lv_style_set_text_opa(&transp_style, LV_OPA_COVER);
	lv_style_set_img_recolor(&transp_style, text_color);

	// Text align
	lv_style_init(&text_centered);
	lv_style_set_text_align(&text_centered, LV_ALIGN_CENTER);
}

// ============================ Public Functions ============================ //

void gui::theme::set_hue(int new_hue) {
	hue = new_hue;

	// Rebuild styles and notify lvgl to refresh all objects
	init_styles();
	lv_obj_report_style_change(NULL);
}