#include "robodash/view.hpp"
#include <algorithm>

rd::View::View(std::string name) {
	// TODO: Implement
}

rd::View::~View() {
	// TODO: Implement
}

void rd::View::focus() {
	// TODO: Implement
}

void rd::View::add_flag(rd::ViewFlag flag) { flags.push_back(flag); }

bool rd::View::has_flag(rd::ViewFlag flag) {
	return std::find(flags.begin(), flags.end(), flag) != flags.end();
}

void rd::View::remove_flag(rd::ViewFlag flag) {
	flags.erase(std::remove(flags.begin(), flags.end(), flag), flags.end());
}

lv_obj_t *rd::View::get_lv_obj() { return scr_obj; }

rd::View::operator lv_obj_t *() { return scr_obj; }
