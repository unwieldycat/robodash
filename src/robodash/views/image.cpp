#include "robodash/apix.hpp"

// ============================= Core Functions ============================= //

rd::ImageView::ImageView(std::string path, std::string name) : View(name) {
	this->path = "S:" + path;
}

void rd::ImageView::initialize() {
	if (!pros::usd::is_installed()) return;
	lv_obj_t *image = lv_img_create(this->get_obj());
	lv_img_set_src(image, path.c_str());
	lv_obj_align(image, LV_ALIGN_CENTER, 0, 0);
}

void rd::ImageView::refresh() {}
