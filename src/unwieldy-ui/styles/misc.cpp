#include "unwieldy-ui/styles.hpp"

// ============================= Miscellaneous ============================= //

lv_style_t style_bg;
lv_style_t style_transp;

void _init_style_misc() {
	// Background
	lv_style_init(&style_bg);
	lv_style_set_border_width(&style_bg, 0);
	lv_style_set_radius(&style_bg, 0);
	lv_style_set_bg_color(&style_bg, bg_color);
	lv_style_set_text_color(&style_bg, text_color);
	lv_style_set_pad_all(&style_bg, 0);

	// Transparent
	lv_style_init(&style_transp);
	lv_style_set_bg_opa(&style_transp, LV_OPA_TRANSP);
	lv_style_set_border_opa(&style_transp, LV_OPA_TRANSP);
	lv_style_set_radius(&style_transp, 0);
	lv_style_set_pad_all(&style_transp, 0);
}