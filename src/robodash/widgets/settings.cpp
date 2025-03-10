#include "robodash/widgets/settings.hpp"
#include "liblvgl/extra/layouts/flex/lv_flex.h"
#include "liblvgl/lvgl.h"
#include "robodash/detail/styles.h"

rd::Settings::Settings(std::string name) : view(name) {
	lv_obj_set_style_bg_color(view, color_bg, 0);

	lv_obj_t *title_label = lv_label_create(view);
	lv_obj_add_style(title_label, &style_text_large, 0);
	lv_obj_add_style(title_label, &style_text_centered, 0);
	lv_label_set_text(title_label, name.c_str());
	lv_obj_align(title_label, LV_ALIGN_TOP_MID, 0, 12);

	// TODO: Display only when change occurs
	lv_obj_t *save_btn = lv_btn_create(view);
	lv_obj_set_size(save_btn, 64, 32);
	lv_obj_align(save_btn, LV_ALIGN_TOP_LEFT, 4, 4);
	lv_obj_add_style(save_btn, &style_core_button, 0);
	lv_obj_add_style(save_btn, &style_core_button_pr, LV_STATE_PRESSED);

	lv_obj_t *save_label = lv_label_create(save_btn);
	lv_label_set_text(save_label, "Save " LV_SYMBOL_SAVE);
	lv_obj_align(save_label, LV_ALIGN_CENTER, 0, 0);

	settings_cont = lv_obj_create(view);
	lv_obj_set_size(settings_cont, lv_pct(100), 192);
	lv_obj_align(settings_cont, LV_ALIGN_CENTER, 0, 0);
	lv_obj_add_style(settings_cont, &style_transp, 0);
	lv_obj_set_layout(settings_cont, LV_LAYOUT_FLEX);
	lv_obj_set_flex_flow(settings_cont, LV_FLEX_FLOW_COLUMN);
	lv_obj_set_flex_align(
	    settings_cont, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER
	);
}

lv_obj_t *rd::Settings::create_setting_cont(std::string key) {
	lv_obj_t *setting_cont = lv_obj_create(settings_cont);
	lv_obj_set_size(setting_cont, lv_pct(80), 32);
	lv_obj_add_style(setting_cont, &style_transp, 0);

	lv_obj_t *setting_label = lv_label_create(setting_cont);
	lv_obj_add_style(setting_label, &style_text_large, 0);
	lv_obj_align(setting_label, LV_ALIGN_LEFT_MID, 8, 0);
	lv_label_set_text(setting_label, key.c_str());

	return setting_cont;
}

void rd::Settings::toggle(std::string key, bool default_value, std::function<void(bool)> callback) {
	lv_obj_t *setting_cont = create_setting_cont(key);
	lv_obj_t *setting_toggle = lv_switch_create(setting_cont);
	lv_obj_set_size(setting_toggle, 48, 24);
	lv_obj_align(setting_toggle, LV_ALIGN_RIGHT_MID, -8, 0);
}

void rd::Settings::dropdown(
    std::string key, std::vector<std::string> values, std::string default_value,
    std::function<void(std::string &)> callback
) {
	lv_obj_t *setting_cont = create_setting_cont(key);
	lv_obj_t *setting_dropdown = lv_dropdown_create(setting_cont);
	lv_obj_set_size(setting_dropdown, 96, 24);
	lv_obj_align(setting_dropdown, LV_ALIGN_RIGHT_MID, -8, 0);
}

void rd::Settings::slider(
    std::string key, double min, double max, double step, double default_value,
    std::function<void(double)> callback
) {
	lv_obj_t *setting_cont = create_setting_cont(key);
	lv_obj_t *setting_slider = lv_slider_create(setting_cont);
	lv_obj_set_size(setting_slider, 96, 8);
	lv_obj_align(setting_slider, LV_ALIGN_RIGHT_MID, -8, 0);
}

void rd::Settings::increment(
    std::string key, int min, int max, int default_value, std::function<void(int)> callback
) {
	lv_obj_t *setting_cont = create_setting_cont(key);

	lv_obj_t *increment_cont = lv_obj_create(setting_cont);
	lv_obj_set_size(increment_cont, 96, 24);
	lv_obj_align(increment_cont, LV_ALIGN_RIGHT_MID, -8, 0);
	lv_obj_add_style(increment_cont, &style_transp, 0);

	lv_obj_t *down_btn = lv_btn_create(increment_cont);
	lv_obj_set_size(down_btn, 24, 24);
	lv_obj_align(down_btn, LV_ALIGN_LEFT_MID, 8, 0);
	lv_obj_add_style(down_btn, &style_btn_outline, 0);
	lv_obj_t *down_label = lv_label_create(down_btn);
	lv_label_set_text(down_label, LV_SYMBOL_MINUS);
	lv_obj_align(down_label, LV_ALIGN_CENTER, 0, 0);

	lv_obj_t *number = lv_label_create(increment_cont);
	lv_label_set_text_fmt(number, "%d", default_value);
	lv_obj_align(number, LV_ALIGN_CENTER, 0, 0);

	lv_obj_t *up_btn = lv_btn_create(increment_cont);
	lv_obj_set_size(up_btn, 24, 24);
	lv_obj_align(up_btn, LV_ALIGN_RIGHT_MID, -8, 0);
	lv_obj_add_style(up_btn, &style_btn_outline, 0);
	lv_obj_t *up_label = lv_label_create(up_btn);
	lv_label_set_text(up_label, LV_SYMBOL_PLUS);
	lv_obj_align(up_label, LV_ALIGN_CENTER, 0, 0);
}

void rd::Settings::focus() { view.focus(); }
