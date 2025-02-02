#include "api.h"
#include "robodash/apix.h"

// ============================= Core Functions ============================= //

rd::Image::Image(const lv_img_dsc_t *image_dsc, std::string name) {
	this->view = rd_view_create(name.c_str());
	lv_obj_t *image = lv_img_create(view->obj);
	lv_img_set_src(image, image_dsc);
	lv_obj_align(image, LV_ALIGN_CENTER, 0, 0);
	rd_view_set_anims(this->view, RD_ANIM_OFF);
}

rd::Image::Image(lv_img_dsc_t *image_dsc, std::string name)
    : Image(const_cast<const lv_img_dsc_t *>(image_dsc), name) {}

rd::Image::Image(std::string path, std::string name) {
	if (!pros::usd::is_installed()) return;

	this->view = rd_view_create(name.c_str());
	lv_obj_t *image = lv_img_create(view->obj);
	lv_img_set_src(image, ("S:" + path).c_str());
	lv_obj_align(image, LV_ALIGN_CENTER, 0, 0);
	rd_view_set_anims(this->view, RD_ANIM_OFF);
}

void rd::Image::focus() { rd_view_focus(this->view); }