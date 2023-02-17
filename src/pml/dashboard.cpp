#include "dashboard.hpp"

// =============================== Variables =============================== //

std::vector<std::function<void()>> actions;

lv_obj_t *console;
lv_obj_t *actions_list;

// =============================== Dashboard =============================== //

void pml::init() {
	actions_list = lv_list_create(lv_scr_act(), NULL);
	lv_obj_set_size(actions_list, 128, 224);
	lv_obj_align(actions_list, NULL, LV_ALIGN_IN_TOP_RIGHT, -8, 8);
}

lv_res_t act_btn_action(_lv_obj_t *obj) {
	int act_id = lv_obj_get_free_num(obj);
	actions[act_id]();
	return LV_RES_OK;
}

void pml::add_action_btn(std::string label, std::function<void()> action) {
	actions.push_back(action);
	lv_obj_t *new_btn = lv_list_add(actions_list, NULL, label.c_str(), act_btn_action);
	lv_obj_set_free_num(new_btn, actions.size() - 1);
}