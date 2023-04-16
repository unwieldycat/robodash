#include "common/styles.hpp"
#include "common/init.hpp"
#include "misc.hpp"

// ================================= Colors ================================= //

int hue = 200;

lv_color_t bg_color;
lv_color_t border_color;
lv_color_t shade_color;
lv_color_t primary_color;
lv_color_t primary_color_dark;
lv_color_t text_color;

// ================================= Styles ================================= //

lv_style_t bg_style;
lv_style_t list_style;
lv_style_t list_btn_style_rel;
lv_style_t list_btn_style_pr;
lv_style_t round_btn_style_rel;
lv_style_t round_btn_style_pr;
lv_style_t outline_round_btn_style_rel;
lv_style_t outline_round_btn_style_pr;
lv_style_t small_text;

void init_styles() {
	// Colors
	bg_color = lv_color_hsv_to_rgb(hue, 50, 10);
	border_color = lv_color_hsv_to_rgb(hue, 25, 50);
	shade_color = lv_color_hsv_to_rgb(hue, 50, 25);
	primary_color = lv_color_hsv_to_rgb(hue, 75, 100);
	primary_color_dark = lv_color_hsv_to_rgb(hue, 75, 50);
	text_color = lv_color_hsv_to_rgb(hue, 10, 100);

	// Background style
	lv_style_copy(&bg_style, &lv_style_plain);
	bg_style.body.border.width = 0;
	bg_style.body.radius = 0;
	bg_style.body.main_color = bg_color;
	bg_style.body.grad_color = bg_color;
	bg_style.text.color = text_color;

	// List style
	lv_style_copy(&list_style, &lv_style_pretty);
	list_style.body.border.color = border_color;
	list_style.body.border.width = 1;
	list_style.body.border.opa = LV_OPA_COVER;
	list_style.body.radius = 2;
	list_style.body.grad_color = bg_color;
	list_style.body.main_color = bg_color;
	list_style.body.padding.ver = 0;
	list_style.body.padding.hor = 8;
	list_style.body.padding.inner = 0;

	// List button released style
	lv_style_copy(&list_btn_style_rel, &lv_style_plain);
	list_btn_style_rel.body.border.width = 1;
	list_btn_style_rel.body.border.color = border_color;
	list_btn_style_rel.body.border.part = LV_BORDER_BOTTOM;
	list_btn_style_rel.body.radius = 0;
	list_btn_style_rel.body.main_color = bg_color;
	list_btn_style_rel.body.grad_color = bg_color;
	list_btn_style_rel.body.padding.ver = 16;
	list_btn_style_rel.text.color = text_color;

	// List button pressed style
	lv_style_copy(&list_btn_style_pr, &list_btn_style_rel);
	list_btn_style_pr.body.main_color = shade_color;
	list_btn_style_pr.body.grad_color = shade_color;
	list_btn_style_pr.body.radius = 0;
	list_btn_style_pr.body.padding.ver = 16;
	list_btn_style_pr.text.color = text_color;

	// Released rounded button style
	lv_style_copy(&round_btn_style_rel, &lv_style_plain);
	round_btn_style_rel.body.main_color = primary_color;
	round_btn_style_rel.body.grad_color = primary_color;
	round_btn_style_rel.body.radius = 16;
	round_btn_style_rel.image.color.full = bg_color.full;

	// Pressed rounded button style
	lv_style_copy(&round_btn_style_pr, &lv_style_plain);
	round_btn_style_pr.body.main_color = primary_color_dark;
	round_btn_style_pr.body.grad_color = primary_color_dark;
	round_btn_style_pr.body.radius = 16;
	round_btn_style_pr.image.color.full = bg_color.full;

	// Released outline rounded button style
	lv_style_copy(&outline_round_btn_style_rel, &lv_style_plain);
	outline_round_btn_style_rel.body.border.color = border_color;
	outline_round_btn_style_rel.body.border.opa = LV_OPA_COVER;
	outline_round_btn_style_rel.body.border.width = 1;
	outline_round_btn_style_rel.body.main_color = bg_color;
	outline_round_btn_style_rel.body.grad_color = bg_color;
	outline_round_btn_style_rel.body.radius = 16;
	outline_round_btn_style_rel.image.color.full = text_color.full;

	// Pressed outline rounded button style
	lv_style_copy(&outline_round_btn_style_pr, &outline_round_btn_style_rel);
	outline_round_btn_style_pr.body.main_color = shade_color;
	outline_round_btn_style_pr.body.grad_color = shade_color;

	// Small text style
	small_text.text.color = text_color;
	small_text.text.opa = LV_OPA_COVER;
	small_text.text.font = &lv_font_dejavu_10;
	small_text.text.letter_space = 1;
}

// ============================ Public Functions ============================ //

void sl::theme::set_hue(int new_hue) {
	hue = new_hue;
	init_styles();
}