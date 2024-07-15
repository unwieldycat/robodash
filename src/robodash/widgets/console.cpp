#include "robodash/widgets/console.hpp"
#include "robodash/detail/styles.h"

// ============================= Core Functions ============================= //

rd::Console::Console(std::string name) : view(name) {
	lv_obj_set_style_bg_color(view, color_bg, 0);

	this->output_cont = lv_obj_create(view);
	lv_obj_set_width(output_cont, lv_pct(100));
	lv_obj_set_height(output_cont, lv_pct(100));
	lv_obj_align(output_cont, LV_ALIGN_CENTER, 0, 0);
	lv_obj_add_style(output_cont, &style_transp, 0);

	this->output = lv_label_create(output_cont);
	lv_obj_set_height(output, LV_SIZE_CONTENT);
	lv_obj_add_style(output, &style_transp, 0);
	lv_obj_add_style(output, &style_text_mono, 0);
	lv_label_set_recolor(output, true);
	lv_label_set_long_mode(output, LV_LABEL_LONG_WRAP);
}

// =========================== Console Functions =========================== //

void rd::Console::clear() {
	lv_label_set_text(this->output, "");
	this->stream.str("");
	this->stream.clear();
}

void rd::Console::print(std::string str) {
	this->stream << str;
	if (this->output) lv_label_set_text(this->output, this->stream.str().c_str());
	lv_obj_scroll_to_y(this->output_cont, LV_COORD_MAX, LV_ANIM_OFF);
}

void rd::Console::println(std::string str) { this->print(str + "\n"); }

void rd::Console::focus() { view.focus(); }
