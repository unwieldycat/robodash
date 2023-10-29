#include "console.hpp"
#include <sstream>

lv_obj_t *output;
std::ostringstream stream;

// ============================= Core Functions ============================= //

rd::ConsoleView::ConsoleView(std::string name) : View(name) {}

void rd::ConsoleView::refresh() {}

void rd::ConsoleView::initialize() {
	lv_obj_set_style_bg_color(this->get_obj(), color_bg, 0);

	output = lv_label_create(this->get_obj());
	lv_obj_set_size(output, 464, 224);
	lv_obj_align(output, LV_ALIGN_CENTER, 0, 0);
	lv_obj_add_style(output, &style_transp, 0);
	lv_obj_add_style(output, &style_text_mono, 0);
	lv_label_set_recolor(output, true);
}

// =========================== Console Functions =========================== //

void rd::ConsoleView::clear() {
	lv_label_set_text(output, "");
	stream.str("");
	stream.clear();
}

void rd::ConsoleView::print(std::string str) {
	stream << str;
	if (output) lv_label_set_text(output, stream.str().c_str());
}

void rd::ConsoleView::println(std::string str) { this->print(str + "\n"); }
