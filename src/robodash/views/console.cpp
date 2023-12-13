#include "console.hpp"
#include "robodash/apix.h"
#include <sstream>

lv_obj_t *output;
lv_obj_t *output_cont;
std::ostringstream stream;

// ============================= Core Functions ============================= //

rd::Console::Console(std::string name) {
	this->view = rd_view_create(name.c_str());

	lv_obj_set_style_bg_color(view->obj, color_bg, 0);

	output_cont = lv_obj_create(view->obj);
	lv_obj_set_width(output_cont, 464);
	lv_obj_set_height(output_cont, LV_SIZE_CONTENT);
	lv_obj_align(output_cont, LV_ALIGN_TOP_LEFT, 0, 0);
	lv_obj_add_style(output_cont, &style_transp, 0);

	output = lv_label_create(output_cont);
	lv_obj_align(output, LV_ALIGN_TOP_LEFT, 0, 0);
	lv_obj_add_style(output, &style_transp, 0);
	lv_obj_add_style(output, &style_text_mono, 0);
	lv_label_set_recolor(output, true);
	lv_label_set_long_mode(output, LV_LABEL_LONG_WRAP);
}

// =========================== Console Functions =========================== //

void rd::Console::clear() {
	lv_label_set_text(output, "");
	stream.str("");
	stream.clear();
}

void rd::Console::print(std::string str) {
	stream << str;
	if (output) lv_label_set_text(output, stream.str().c_str());
	lv_obj_scroll_by(output_cont, 0, 8, LV_ANIM_OFF); // FIXME: Broken, doesn't do anything at all
}

void rd::Console::println(std::string str) { this->print(str + "\n"); }

void rd::Console::focus() { rd_view_focus(this->view); }
