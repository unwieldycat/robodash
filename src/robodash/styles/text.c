#include "robodash/detail/assets.h"
#include "robodash/detail/styles.h"

// ================================== Text ================================== //

lv_style_t style_text_mono;
lv_style_t style_text_small;
lv_style_t style_text_medium;
lv_style_t style_text_large;
lv_style_t style_text_centered;

void create_text_styles() {
	// Monospaced text
	lv_style_init(&style_text_mono);
	lv_style_set_text_color(&style_text_mono, color_text);
	lv_style_set_text_opa(&style_text_mono, LV_OPA_COVER);
	lv_style_set_text_font(&style_text_mono, &source_code_pro_16);
	lv_style_set_text_letter_space(&style_text_mono, 1);

	// Small text
	lv_style_init(&style_text_small);
	lv_style_set_text_color(&style_text_small, color_text);
	lv_style_set_text_opa(&style_text_small, LV_OPA_COVER);
	lv_style_set_text_font(&style_text_small, &lv_font_montserrat_12);

	// Medium text
	lv_style_init(&style_text_medium);
	lv_style_set_text_color(&style_text_medium, color_text);
	lv_style_set_text_opa(&style_text_medium, LV_OPA_COVER);
	lv_style_set_text_font(&style_text_medium, &lv_font_montserrat_14);

	// Large text
	lv_style_init(&style_text_large);
	lv_style_set_text_color(&style_text_large, color_text);
	lv_style_set_text_opa(&style_text_large, LV_OPA_COVER);
	lv_style_set_text_font(&style_text_large, &lv_font_montserrat_16);

	// Text align
	lv_style_init(&style_text_centered);
	lv_style_set_text_align(&style_text_centered, LV_TEXT_ALIGN_CENTER);
}