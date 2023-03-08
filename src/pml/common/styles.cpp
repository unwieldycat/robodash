#include "pml/common/styles.hpp"

// ================================= Styles ================================= //

lv_style_t bg_style;

lv_style_t list_style_bg;
lv_style_t list_btn_style_rel;
lv_style_t list_btn_style_pr;
lv_style_t list_btn_style_ina;

lv_style_t btn_style_rel;
lv_style_t btn_style_pr;
lv_style_t btn_style_ina;

// ============================= Initialization ============================= //

bool initialized = false;

void init_styles() {
	if (initialized) return;
	initialized = true;

	// Background
	lv_style_copy(&bg_style, &lv_style_plain);
	bg_style.body.border.width = 0;
	bg_style.body.radius = 0;
	bg_style.body.main_color = lv_color_hex(0x262626);
	bg_style.body.grad_color = lv_color_hex(0x262626);
	bg_style.text.color = LV_COLOR_WHITE;

	// List background
	lv_style_copy(&list_style_bg, &lv_style_transp);
	list_style_bg.body.radius = 4;

	//  List button released
	lv_style_copy(&list_btn_style_rel, &lv_style_plain);
	list_btn_style_rel.body.main_color = lv_color_hex(0x262626);
	list_btn_style_rel.body.grad_color = lv_color_hex(0x262626);
	list_btn_style_rel.text.color = LV_COLOR_WHITE;
	list_btn_style_rel.body.padding.hor = 16;
	list_btn_style_rel.body.padding.inner = 16;
	list_btn_style_rel.line.width = 2;
	list_btn_style_rel.line.color = lv_color_hex(0x595959);

	// Button released
	lv_style_copy(&btn_style_rel, &lv_style_plain);
	btn_style_rel.body.radius = 8;
	btn_style_rel.body.border.width = 2;
	btn_style_rel.body.border.color = lv_color_hex(0x404040);
	btn_style_rel.body.main_color = lv_color_hex(0x404040);
	btn_style_rel.body.grad_color = lv_color_hex(0x595959);
	btn_style_rel.text.color = LV_COLOR_WHITE;

	// Button pressed
	lv_style_copy(&btn_style_pr, &btn_style_rel);
	btn_style_pr.body.main_color = lv_color_hex(0x404040);
	btn_style_pr.body.grad_color = lv_color_hex(0x404040);
}