#include "robodash/apix.hpp"

// ============================= Core Functions ============================= //

gui::ImageView::ImageView(std::string name, std::string path) : View(name) {
	this->path = "S:" + path;
}
gui::ImageView::~ImageView() {}

void gui::ImageView::initialize() {
	lv_obj_t *image = lv_img_create(this->get_obj());
	lv_img_set_src(image, path.c_str());
	lv_obj_align(image, LV_ALIGN_CENTER, 0, 0);
}

void gui::ImageView::refresh() {}
