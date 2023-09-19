#include "robodash/styles.hpp"

// ================================== Bar ================================== //

lv_style_t style_bar_button;
lv_style_t style_bar_button_pr;
lv_style_t style_bar_list;
lv_style_t style_bar_bg;

void _init_style_bar() {
	// Bottom bar button
	lv_style_init(&style_bar_button);
	lv_style_set_pad_all(&style_bar_button, 8);
	lv_style_set_bg_color(&style_bar_button, color_bar);
	lv_style_set_border_color(&style_bar_button, color_bar_outline);
	lv_style_set_border_side(&style_bar_button, LV_BORDER_SIDE_RIGHT);
	lv_style_set_border_width(&style_bar_button, 1);
	lv_style_set_text_color(&style_bar_button, color_text);
	lv_style_set_img_recolor(&style_bar_button, color_text);
	lv_style_set_radius(&style_bar_button, 0);

	// Bottom bar button pressed
	lv_style_init(&style_bar_button_pr);
	lv_style_set_bg_color(&style_bar_button_pr, color_bar_dark);

	// Bottom bar list
	lv_style_init(&style_bar_list);
	lv_style_set_text_color(&style_bar_list, color_text);
	lv_style_set_border_color(&style_bar_list, color_border);
	lv_style_set_border_width(&style_bar_list, 1);
	lv_style_set_bg_color(&style_bar_list, color_bar);
	lv_style_set_pad_all(&style_bar_list, 8);

	// Bottom bar background
	lv_style_init(&style_bar_bg);
	lv_style_set_border_width(&style_bar_bg, 0);
	lv_style_set_radius(&style_bar_bg, 0);
	lv_style_set_bg_color(&style_bar_bg, color_bar);
	lv_style_set_text_color(&style_bar_bg, color_text);
	lv_style_set_pad_all(&style_bar_bg, 0);
}