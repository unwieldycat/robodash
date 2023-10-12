#include "robodash/styles.hpp"

// ================================== Bar ================================== //

lv_style_t style_bar_button;
lv_style_t style_bar_button_pr;
lv_style_t style_bar_list;
lv_style_t style_bar_bg;

void _init_style_bar() {
	// Sidebar button
	lv_style_init(&style_bar_button);
	lv_style_set_pad_all(&style_bar_button, 8);
	lv_style_set_bg_color(&style_bar_button, color_bar);
	lv_style_set_radius(&style_bar_button, 4);
	lv_style_set_border_color(&style_bar_button, color_bar_outline);
	lv_style_set_border_width(&style_bar_button, 0);
	lv_style_set_shadow_width(&style_bar_button, 0);
	lv_style_set_text_color(&style_bar_button, color_text);
	lv_style_set_img_recolor(&style_bar_button, color_text);

	// Sidebar button pressed
	lv_style_init(&style_bar_button_pr);
	lv_style_set_bg_color(&style_bar_button_pr, color_bar_dark);

	// Sidebar list
	lv_style_init(&style_bar_list);
	lv_style_set_text_color(&style_bar_list, color_text);
	lv_style_set_border_color(&style_bar_list, color_border);
	lv_style_set_border_width(&style_bar_list, 0);
	lv_style_set_bg_color(&style_bar_list, color_bar);
	lv_style_set_pad_all(&style_bar_list, 8);

	// Sidebar background
	lv_style_init(&style_bar_bg);
	lv_style_set_border_width(&style_bar_bg, 0);
	lv_style_set_radius(&style_bar_bg, 0);
	lv_style_set_bg_color(&style_bar_bg, color_bar);
	lv_style_set_text_color(&style_bar_bg, color_text);
	lv_style_set_pad_all(&style_bar_bg, 0);
}