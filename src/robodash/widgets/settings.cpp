#include "robodash/widgets/settings.hpp"
#include "liblvgl/extra/layouts/flex/lv_flex.h"
#include "liblvgl/lvgl.h"
#include "robodash/detail/styles.h"

rd::Settings::Settings(std::string name) : view(name) {
	settings_cont = lv_obj_create(view);
	lv_obj_set_size(settings_cont, lv_pct(100), lv_pct(100));
	lv_obj_align(settings_cont, LV_ALIGN_CENTER, 0, 0);
	lv_obj_add_style(settings_cont, &style_transp, 0);
	lv_obj_set_layout(settings_cont, LV_LAYOUT_FLEX);
}

bool &rd::Settings::toggle(std::string key, bool default_value) {
	lv_obj_t *setting_cont = lv_obj_create(view);
	lv_obj_set_size(setting_cont, lv_pct(100), 30);
	lv_obj_add_style(setting_cont, &style_transp, 0);
}

std::string &rd::Settings::dropdown(
    std::string key, std::vector<std::string> values, std::string default_value
) {
	return default_value;
}

double &
rd::Settings::slider(std::string key, double min, double max, double step, double default_value) {
	return default_value;
}

int &rd::Settings::increment(std::string key, int min, int max, int default_value) {
	return default_value;
}

void rd::Settings::focus() { view.focus(); }
