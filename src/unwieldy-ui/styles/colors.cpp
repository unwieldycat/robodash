#include "unwieldy-ui/styles.hpp"

// ================================= Colors ================================= //

int hue = 200;

lv_color_t bg_color;
lv_color_t border_color;
lv_color_t shade_color;
lv_color_t primary_color;
lv_color_t primary_color_dark;
lv_color_t text_color;

lv_color_t bar_color;
lv_color_t bar_color_dark;
lv_color_t bar_outline_color;

void _init_colors() {
	bg_color = lv_color_hsv_to_rgb(hue, 50, 10);
	border_color = lv_color_hsv_to_rgb(hue, 25, 50);
	shade_color = lv_color_hsv_to_rgb(hue, 50, 25);
	primary_color = lv_color_hsv_to_rgb(hue, 75, 100);
	primary_color_dark = lv_color_hsv_to_rgb(hue, 75, 50);
	text_color = lv_color_hsv_to_rgb(hue, 10, 100);
	bar_color = lv_color_hsv_to_rgb(hue, 50, 25);
	bar_color_dark = lv_color_hsv_to_rgb(hue, 50, 15);
	bar_outline_color = lv_color_hsv_to_rgb(hue, 10, 50);
}

// ============================= User Functions ============================= //

void gui::theme::set_hue(int new_hue) {
	hue = new_hue;

	// Rebuild styles and notify lvgl to refresh all objects
	_initialize();
	lv_obj_report_style_change(NULL);
}