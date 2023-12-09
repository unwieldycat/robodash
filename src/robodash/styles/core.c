#include "robodash/apix.h"

// ================================== Core ================================== //

lv_style_t style_core_button;
lv_style_t style_core_button_pr;
lv_style_t style_core_list;
lv_style_t style_core_list_btn;
lv_style_t style_core_bg;
lv_style_t style_core_modal;

void _init_style_core() {
	// Sidebar button
	lv_style_init(&style_core_button);
	lv_style_set_pad_all(&style_core_button, 8);
	lv_style_set_bg_color(&style_core_button, color_bar);
	lv_style_set_radius(&style_core_button, 4);
	lv_style_set_border_color(&style_core_button, color_bar_outline);
	lv_style_set_border_width(&style_core_button, 0);
	lv_style_set_shadow_width(&style_core_button, 0);
	lv_style_set_text_color(&style_core_button, color_text);
	lv_style_set_img_recolor(&style_core_button, color_text);

	// Sidebar button pressed
	lv_style_init(&style_core_button_pr);
	lv_style_set_bg_color(&style_core_button_pr, color_bar_dark);

	// Sidebar list
	lv_style_init(&style_core_list);
	lv_style_set_text_color(&style_core_list, color_text);
	lv_style_set_border_color(&style_core_list, color_border);
	lv_style_set_border_width(&style_core_list, 0);
	lv_style_set_bg_color(&style_core_list, color_bar);
	lv_style_set_pad_all(&style_core_list, 8);

	// Sidebar list button
	lv_style_init(&style_core_list_btn);
	lv_style_set_border_color(&style_core_list_btn, color_bar_outline);
	lv_style_set_border_width(&style_core_list_btn, 1);
	lv_style_set_border_opa(&style_core_list_btn, LV_OPA_COVER);
	lv_style_set_border_side(&style_core_list_btn, LV_BORDER_SIDE_BOTTOM);
	lv_style_set_text_color(&style_core_list_btn, color_text);
	lv_style_set_radius(&style_core_list_btn, 0);
	lv_style_set_bg_color(&style_core_list_btn, color_bar);

	// Sidebar background
	lv_style_init(&style_core_bg);
	lv_style_set_border_width(&style_core_bg, 0);
	lv_style_set_radius(&style_core_bg, 0);
	lv_style_set_bg_color(&style_core_bg, color_bar);
	lv_style_set_text_color(&style_core_bg, color_text);
	lv_style_set_pad_all(&style_core_bg, 0);

	// Sidebar modal
	lv_style_init(&style_core_modal);
	lv_style_set_bg_opa(&style_core_modal, 144);
	lv_style_set_bg_color(&style_core_modal, lv_color_black());
	lv_style_set_radius(&style_core_modal, 0);
	lv_style_set_border_width(&style_core_modal, 0);
}