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
	bg_style.text.color = LV_COLOR_WHITE;

	lv_style_copy(&cont_style, &lv_style_plain);
	cont_style.body.radius = 4;
	cont_style.body.main_color = lv_color_hex(0x1a1a1a);
	cont_style.body.grad_color = lv_color_hex(0x1a1a1a);
	cont_style.body.border.color = lv_color_hex(0x404040);
	cont_style.body.border.width = 2;
	cont_style.text.color = LV_COLOR_WHITE;
}

// ============================== List Styles ============================== //

lv_style_t list_style_bg;

lv_style_t list_btn_style_rel;
lv_style_t list_btn_style_pr;
lv_style_t list_btn_style_ina;

void init_list_styles() {
	lv_style_copy(&list_style_bg, &lv_style_transp);
	list_style_bg.body.radius = 4;

	lv_style_copy(&list_btn_style_rel, &lv_style_plain);
	list_btn_style_rel.body.main_color = lv_color_hex(0x262626);
	list_btn_style_rel.body.grad_color = lv_color_hex(0x262626);
	list_btn_style_rel.text.color = LV_COLOR_WHITE;
	list_btn_style_rel.body.padding.hor = 16;
	list_btn_style_rel.body.padding.inner = 16;
	list_btn_style_rel.line.width = 2;
	list_btn_style_rel.line.color = lv_color_hex(0x595959);
}

// ============================= Window Styles ============================= //

lv_style_t win_style_content_bg;
lv_style_t win_style_header;

void init_win_styles() {
	lv_style_copy(&win_style_content_bg, &bg_style);
	win_style_content_bg.body.padding.ver = 0;
	win_style_content_bg.body.padding.hor = 0;

	lv_style_copy(&win_style_header, &lv_style_plain);
	win_style_header.body.main_color = lv_color_hex(0x4d4d4d);
	win_style_header.body.grad_color = lv_color_hex(0x4d4d4d);
	win_style_header.text.color = LV_COLOR_WHITE;
	win_style_header.body.padding.ver = 4;
	win_style_header.body.padding.hor = 4;
}

// ============================= Button Styles ============================= //

lv_style_t btn_style_rel;
lv_style_t btn_style_pr;
lv_style_t btn_style_ina;

void init_btn_styles() {
	lv_style_copy(&btn_style_rel, &lv_style_plain);
	btn_style_rel.body.radius = 8;
	btn_style_rel.body.border.width = 2;
	btn_style_rel.body.border.color = lv_color_hex(0x404040);
	btn_style_rel.body.main_color = lv_color_hex(0x404040);
	btn_style_rel.body.grad_color = lv_color_hex(0x595959);
	btn_style_rel.text.color = LV_COLOR_WHITE;

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
	init_list_styles();
	init_win_styles();
	init_btn_styles();
}