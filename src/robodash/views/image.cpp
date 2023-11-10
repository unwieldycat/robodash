#include "robodash/apix.hpp"

// ============================= Core Functions ============================= //

rd::Image::Image(std::string path, std::string name) : view(name) {
	if (!pros::usd::is_installed()) return;

	lv_obj_t *image = lv_img_create(view.get_obj());
	lv_img_set_src(image, ("S:" + path).c_str());
	lv_obj_align(image, LV_ALIGN_CENTER, 0, 0);
}

void rd::Image::focus() { this->view.focus(); }