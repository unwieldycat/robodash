#include "view.hpp"
#include "apix.hpp"

int global_id = 0;

gui::View::View(std::string name) : name(name) {
	this->id = global_id;
	global_id++;

	this->obj = lv_obj_create(lv_scr_act());
	lv_obj_set_size(this->obj, lv_pct(100), lv_pct(100));
	lv_obj_add_flag(this->obj, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_style(this->obj, &style_bg, 0);
}

gui::View::~View() { lv_obj_del(this->obj); }