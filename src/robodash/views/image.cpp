#include "robodash/apix.hpp"

// ============================= Core Functions ============================= //

rd::ImageView::ImageView(std::string name, std::string path) : View(name) {
	this->path = "S:" + path;
}
rd::ImageView::~ImageView() {}

void rd::ImageView::initialize() {
	lv_obj_t *image = lv_img_create(this->get_obj());
	lv_img_set_src(image, path.c_str());
	lv_obj_align(image, LV_ALIGN_CENTER, 0, 0);
}

void rd::ImageView::refresh() {}
