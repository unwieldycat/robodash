#include "pml/internal/styles.hpp"

// ========================== Miscellaneous Styles ========================== //

lv_style_t bg_style;
lv_style_t cont_style;

void init_misc_styles() {
	lv_style_copy(&bg_style, &lv_style_plain);
	bg_style.body.border.width = 0;
	bg_style.body.radius = 0;
	bg_style.body.main_color = lv_color_hex(0x262626);
	bg_style.body.grad_color = lv_color_hex(0x262626);

	lv_style_copy(&cont_style, &lv_style_plain);
	cont_style.body.radius = 4;
	cont_style.body.main_color = lv_color_hex(0x1a1a1a);
	cont_style.body.grad_color = lv_color_hex(0x1a1a1a);
	cont_style.body.border.color = lv_color_hex(0x404040);
	cont_style.body.border.width = 2;
	cont_style.text.color = lv_color_hex(0xffffff);
}

// ============================= Button Styles ============================= //

lv_style_t btn_style_rel;
lv_style_t btn_style_pr;
lv_style_t btn_style_ina;

void init_btn_styles() {
	lv_style_copy(&btn_style_rel, &lv_style_plain);
	btn_style_rel.body.radius = 4;
	btn_style_rel.body.border.width = 2;
	btn_style_rel.body.border.color = lv_color_hex(0x404040);
	btn_style_rel.body.main_color = lv_color_hex(0x404040);
	btn_style_rel.body.grad_color = lv_color_hex(0x595959);
	btn_style_rel.text.color = lv_color_hex(0xffffff);

	lv_style_copy(&btn_style_pr, &btn_style_rel);
	btn_style_pr.body.main_color = lv_color_hex(0x404040);
	btn_style_pr.body.grad_color = lv_color_hex(0x404040);
}

// ============================= Initialization ============================= //

bool initialized = false;

void init_styles() {
	if (initialized) return;
	initialized = true;

	init_misc_styles();
	init_btn_styles();
}