#include "uilib/dashboard.hpp"
#include "uilib/autonmanager.hpp"

lv_obj_t *dashboard;

lv_res_t auton_btn_action(lv_obj_t *obj) {
	uilib::auton_manager::run();
	return LV_RES_OK;
}

void create_dashboard() {
	dashboard = lv_obj_create(lv_scr_act(), NULL);

	// Actions list label
	lv_obj_t *actions_label = lv_label_create(lv_scr_act(), NULL);
	lv_obj_align(actions_label, NULL, LV_ALIGN_IN_TOP_RIGHT, -128, 32);
	lv_label_set_text(actions_label, "Quick Actions");

	// Actions
	lv_obj_t *actions_list = lv_list_create(lv_scr_act(), NULL);
	lv_obj_set_size(actions_list, 128, 130);
	lv_obj_align(actions_list, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -48, -32);

	lv_obj_t *auton_sel_btn = lv_list_add(actions_list, NULL, "Auton selection", auton_btn_action);
	lv_obj_set_free_num(auton_sel_btn, 0);
}

void uilib::dashboard::initialize() { create_dashboard(); }
