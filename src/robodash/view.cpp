#include "view.hpp"
#include "apix.hpp"

int generate_id() {
	static int global_id = 0;
	return global_id++;
}

// ========================= Constructor/Destructor ========================= //

rd::View::View(std::string name) : name(name) {
	this->id = generate_id();

	this->obj = lv_obj_create(lv_scr_act());
	lv_obj_set_size(this->obj, lv_pct(100), lv_pct(100));
	lv_obj_add_flag(this->obj, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_style(this->obj, &style_bg, 0);
}

rd::View::~View() { lv_obj_del(this->obj); }

// ================================ Methods ================================ //

int rd::View::get_id() { return this->id; }

std::string rd::View::get_name() { return this->name; }

lv_obj_t *rd::View::get_obj() { return this->obj; }