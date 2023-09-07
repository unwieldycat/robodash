#include "unwieldy-ui/styles.hpp"

// ================================== Bar ================================== //

lv_style_t style_bar_button;
lv_style_t style_bar_button_pr;
lv_style_t style_bar_list;
lv_style_t style_bar_bg;

void _init_style_bar() {
	// Bottom bar button
	lv_style_init(&style_bar_button);
	lv_style_set_pad_all(&style_bar_button, 8);
	lv_style_set_bg_color(&style_bar_button, bar_color);
	lv_style_set_border_color(&style_bar_button, bar_outline_color);
	lv_style_set_border_side(&style_bar_button, LV_BORDER_SIDE_RIGHT);
	lv_style_set_border_width(&style_bar_button, 1);
	lv_style_set_text_color(&style_bar_button, text_color);
	lv_style_set_img_recolor(&style_bar_button, text_color);
	lv_style_set_radius(&style_bar_button, 0);

	// Bottom bar button pressed
	lv_style_init(&style_bar_button_pr);
	lv_style_set_bg_color(&style_bar_button_pr, bar_color_dark);

	// Bottom bar list
	lv_style_init(&style_bar_list);
	lv_style_set_text_color(&style_bar_list, text_color);
	lv_style_set_border_color(&style_bar_list, border_color);
	lv_style_set_border_width(&style_bar_list, 1);
	lv_style_set_bg_color(&style_bar_list, bar_color);
	lv_style_set_pad_all(&style_bar_list, 8);

	// Bottom bar background
	lv_style_init(&style_bar_bg);
	lv_style_set_border_width(&style_bar_bg, 0);
	lv_style_set_radius(&style_bar_bg, 0);
	lv_style_set_bg_color(&style_bar_bg, bar_color);
	lv_style_set_text_color(&style_bar_bg, text_color);
	lv_style_set_pad_all(&style_bar_bg, 0);
}