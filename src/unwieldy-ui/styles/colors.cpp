#include "unwieldy-ui/styles.hpp"

// ================================= Colors ================================= //

int hue = 200;

lv_color_t color_bg;
lv_color_t color_border;
lv_color_t color_shade;
lv_color_t color_primary;
lv_color_t color_primary_dark;
lv_color_t color_text;

lv_color_t color_bar;
lv_color_t color_bar_dark;
lv_color_t color_bar_outline;

void _init_colors() {
	color_bg = lv_color_hsv_to_rgb(hue, 50, 10);
	color_border = lv_color_hsv_to_rgb(hue, 25, 50);
	color_shade = lv_color_hsv_to_rgb(hue, 50, 25);
	color_primary = lv_color_hsv_to_rgb(hue, 75, 100);
	color_primary_dark = lv_color_hsv_to_rgb(hue, 75, 50);
	color_text = lv_color_hsv_to_rgb(hue, 10, 100);
	color_bar = lv_color_hsv_to_rgb(hue, 50, 25);
	color_bar_dark = lv_color_hsv_to_rgb(hue, 50, 15);
	color_bar_outline = lv_color_hsv_to_rgb(hue, 10, 50);
}

// ============================= User Functions ============================= //

void gui::theme::set_hue(int new_hue) {
	hue = new_hue;

	// Rebuild styles and notify lvgl to refresh all objects
	_initialize();
	lv_obj_report_style_change(NULL);
}