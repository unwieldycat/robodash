#include "robodash/apix.h"

// ============================= Miscellaneous ============================= //

lv_style_t style_bg;
lv_style_t style_transp;
lv_style_t style_alert;

void _init_style_misc() {
	// Background
	lv_style_init(&style_bg);
	lv_style_set_border_width(&style_bg, 0);
	lv_style_set_radius(&style_bg, 0);
	lv_style_set_bg_color(&style_bg, lv_color_black());
	lv_style_set_text_color(&style_bg, color_text);
	lv_style_set_pad_all(&style_bg, 0);

	// Transparent
	lv_style_init(&style_transp);
	lv_style_set_bg_opa(&style_transp, LV_OPA_TRANSP);
	lv_style_set_border_opa(&style_transp, LV_OPA_TRANSP);
	lv_style_set_radius(&style_transp, 0);
	lv_style_set_pad_all(&style_transp, 0);
	lv_style_set_shadow_width(&style_transp, 0);

	// Alert style
	lv_style_init(&style_alert);
	lv_style_set_radius(&style_alert, 4);
	lv_style_set_bg_color(&style_alert, color_red);
	lv_style_set_border_width(&style_alert, 0);
	lv_style_set_pad_all(&style_alert, 8);
	lv_style_set_img_recolor(&style_alert, color_bg);
	lv_style_set_text_color(&style_alert, color_text);
	lv_style_set_shadow_opa(&style_alert, LV_OPA_TRANSP);
}