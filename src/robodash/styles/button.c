#include "robodash/detail/styles.h"

// ================================= Button ================================= //

lv_style_t style_btn;
lv_style_t style_btn_primary;
lv_style_t style_btn_primary_pr;
lv_style_t style_btn_outline;
lv_style_t style_btn_outline_pr;

void _init_style_btn() {
	// Base button
	lv_style_init(&style_btn);
	lv_style_set_radius(&style_btn, 16);
	lv_style_set_img_recolor(&style_btn, color_bg);
	lv_style_set_text_color(&style_btn, color_text);
	lv_style_set_shadow_opa(&style_btn, LV_OPA_TRANSP);

	// Primary button
	lv_style_init(&style_btn_primary);
	lv_style_set_bg_color(&style_btn_primary, color_primary);
	lv_style_set_img_recolor(&style_btn_primary, color_bg);

	// Pressed primary button
	lv_style_init(&style_btn_primary_pr);
	lv_style_set_bg_color(&style_btn_primary_pr, color_primary_dark);

	// Outline button
	lv_style_init(&style_btn_outline);
	lv_style_set_border_color(&style_btn_outline, color_border);
	lv_style_set_border_width(&style_btn_outline, 1);
	lv_style_set_border_opa(&style_btn_outline, LV_OPA_COVER);
	lv_style_set_bg_color(&style_btn_outline, color_bg);
	lv_style_set_img_recolor(&style_btn_outline, color_text);
	lv_style_set_text_color(&style_btn_outline, color_text);

	// Pressed outline button
	lv_style_init(&style_btn_outline_pr);
	lv_style_set_bg_color(&style_btn_outline_pr, color_shade);
}