#include "robodash/view.hpp"
#include "robodash/detail/gui.hpp"
#include "robodash/detail/styles.h"
#include <algorithm>

rd::View::View(std::string name) {
	initialize();

	this->scr_obj = lv_obj_create(lv_scr_act());
	lv_obj_set_size(this->scr_obj, lv_pct(100), lv_pct(100));
	lv_obj_add_flag(this->scr_obj, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_style(this->scr_obj, &style_bg, 0);
	lv_obj_set_parent(this->scr_obj, view_cont);

	this->btn_obj = lv_list_add_btn(view_list, NULL, name.c_str());
	lv_obj_add_style(this->btn_obj, &style_core_list_btn, 0);
	lv_obj_add_style(this->btn_obj, &style_list_btn_pr, LV_STATE_PRESSED);
	lv_obj_set_user_data(this->btn_obj, this);
	lv_obj_add_event_cb(this->btn_obj, view_focus_cb, LV_EVENT_PRESSED, this);
	lv_obj_add_event_cb(this->btn_obj, close_cb, LV_EVENT_PRESSED, NULL);

	this->name = name;

	if (!current_view) this->focus();
}

rd::View::~View() {
	lv_obj_del(this->btn_obj);
	lv_obj_del(this->scr_obj);
	if (current_view == this) current_view = NULL;
}

void rd::View::focus() {
	if (current_view != NULL) lv_obj_add_flag(*current_view, LV_OBJ_FLAG_HIDDEN);
	current_view = this;
	lv_obj_clear_flag(this->scr_obj, LV_OBJ_FLAG_HIDDEN);

	if (this->has_flag(ViewFlag::NoAnimation))
		lv_obj_add_flag(anim_label, LV_OBJ_FLAG_HIDDEN);
	else
		lv_obj_clear_flag(anim_label, LV_OBJ_FLAG_HIDDEN);
}

void rd::View::add_flag(rd::ViewFlag flag) {
	flags.push_back(flag);
	refresh();
}

bool rd::View::has_flag(rd::ViewFlag flag) {
	return std::find(flags.begin(), flags.end(), flag) != flags.end();
}

void rd::View::remove_flag(rd::ViewFlag flag) {
	flags.erase(std::remove(flags.begin(), flags.end(), flag), flags.end());
	refresh();
}

void refresh() {}

std::string rd::View::get_name() { return name; }

lv_obj_t *rd::View::get_lv_obj() { return scr_obj; }

rd::View::operator lv_obj_t *() { return scr_obj; }
