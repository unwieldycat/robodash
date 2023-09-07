#include "console.hpp"
#include "unwieldy-ui/internal/styles.hpp"
#include <sstream>

lv_obj_t *output;
std::ostringstream stream;

// ============================= Core Functions ============================= //

gui::ConsoleView::ConsoleView(std::string name) : View(name) {}

void gui::ConsoleView::refresh() {}

void gui::ConsoleView::initialize() {
	output = lv_label_create(this->obj);
	lv_obj_set_size(output, 464, 192);
	lv_obj_align(output, LV_ALIGN_CENTER, 0, 0);
	lv_obj_add_style(output, &style_transp, 0);
	lv_obj_add_style(output, &style_text_mono, 0);
	lv_label_set_recolor(output, true);
}

// =========================== Console Functions =========================== //

void gui::ConsoleView::clear() {
	lv_label_set_text(output, "");
	stream.str("");
	stream.clear();
}

void gui::ConsoleView::print(std::string str) {
	stream << str;
	lv_label_set_text(output, stream.str().c_str());
}
