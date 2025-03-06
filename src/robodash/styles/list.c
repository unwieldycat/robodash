#include "robodash/detail/styles.h"

// ================================== List ================================== //

lv_style_t style_list;
lv_style_t style_list_btn;
lv_style_t style_list_btn_pr;
lv_style_t style_list_btn_ch;

void create_list_styles() {
	// List
	lv_style_init(&style_list);
	lv_style_set_border_color(&style_list, color_border);
	lv_style_set_border_width(&style_list, 1);
	lv_style_set_border_opa(&style_list, LV_OPA_COVER);
	lv_style_set_bg_color(&style_list, color_bg);
	lv_style_set_pad_hor(&style_list, 0);

	// List button
	lv_style_init(&style_list_btn);
	lv_style_set_border_color(&style_list_btn, color_border);
	lv_style_set_border_width(&style_list_btn, 1);
	lv_style_set_border_opa(&style_list_btn, LV_OPA_COVER);
	lv_style_set_border_side(&style_list_btn, LV_BORDER_SIDE_BOTTOM);
	lv_style_set_text_color(&style_list_btn, color_text);
	lv_style_set_radius(&style_list_btn, 0);
	lv_style_set_bg_color(&style_list_btn, color_bg);
	lv_style_set_pad_ver(&style_list_btn, 12);

	// List button pressed
	lv_style_init(&style_list_btn_pr);
	lv_style_set_bg_color(&style_list_btn_pr, color_shade);

	// List button checked
	lv_style_init(&style_list_btn_ch);
	lv_style_set_bg_color(&style_list_btn_ch, lv_color_darken(color_shade, 64));
	lv_style_set_transform_width(&style_list_btn_ch, 0);
}
