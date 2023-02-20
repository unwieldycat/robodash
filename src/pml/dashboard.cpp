#include "dashboard.hpp"
#include "display/lv_core/lv_obj.h"

// =============================== Variables =============================== //

std::vector<std::function<void()>> actions;

lv_obj_t *dashboard;
lv_obj_t *actions_list;

// =============================== Dashboard =============================== //

void pml::init() {
	dashboard = lv_cont_create(lv_scr_act(), NULL);
	lv_obj_set_size(dashboard, 480, 240);
	lv_obj_align(dashboard, NULL, LV_ALIGN_CENTER, 0, 0);

	// FIXME: Children dont have same width or expand as much as possible
	actions_list = lv_cont_create(dashboard, NULL);
	lv_obj_set_height(actions_list, 32);
	lv_cont_set_layout(actions_list, LV_LAYOUT_ROW_M);
	lv_cont_set_fit(actions_list, true, false);
	lv_obj_align(actions_list, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, -8);
}

lv_res_t act_btn_action(_lv_obj_t *obj) {
	int act_id = lv_obj_get_free_num(obj);
	actions[act_id]();
	return LV_RES_OK;
}

void pml::add_action_btn(std::string label, std::function<void()> action) {
	actions.push_back(action);
	lv_obj_t *new_btn = lv_btn_create(actions_list, NULL);
	lv_obj_set_size(new_btn, 96, 32);
	lv_obj_set_free_num(new_btn, actions.size() - 1);
	lv_btn_set_action(new_btn, LV_BTN_ACTION_CLICK, act_btn_action);
	lv_btn_set_fit(new_btn, true, false);
	lv_obj_t *btn_label = lv_label_create(new_btn, NULL);
	lv_label_set_text(btn_label, label.c_str());
	lv_obj_align(actions_list, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, -8);
}