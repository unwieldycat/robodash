#include "robodash/widgets/image.hpp"
#include "robodash/detail/platform.h"
#include "robodash/detail/styles.h"
#include "robodash/view.hpp"

// ============================= Core Functions ============================= //

rd::Image::Image(const lv_img_dsc_t *image_dsc, std::string name) : view(name) {
	lv_obj_t *image = lv_img_create(view);
	lv_img_set_src(image, image_dsc);
	lv_obj_align(image, LV_ALIGN_CENTER, 0, 0);

	view.add_flag(ViewFlag::NoAnimation);
}

rd::Image::Image(lv_img_dsc_t *image_dsc, std::string name)
    : Image(const_cast<const lv_img_dsc_t *>(image_dsc), name) {}

rd::Image::Image(std::string path, std::string name) : view(name) {
	if (!rd::detail::platform::sd_installed()) return;

	lv_obj_t *image = lv_img_create(view);
	lv_img_set_src(image, ("S:" + path).c_str());
	lv_obj_align(image, LV_ALIGN_CENTER, 0, 0);

	view.add_flag(ViewFlag::NoAnimation);
}

void rd::Image::focus() { view.focus(); }
