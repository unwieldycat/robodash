#include "robodash/apix.hpp"

// ============================= Core Functions ============================= //

rd::Image::Image(std::string path, std::string name) {
	if (!pros::usd::is_installed()) return;

	static rd::View image_view(name);

	lv_obj_t *image = lv_img_create(image_view.get_obj());
	lv_img_set_src(image, ("S:" + path).c_str());
	lv_obj_align(image, LV_ALIGN_CENTER, 0, 0);
}