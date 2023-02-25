#include "auton_selector.hpp"

// =============================== Variables =============================== //

std::vector<pml::Routine> routines;
int selected_auton = -1; // Default -1 to do nothing
bool selection_done = false;
bool selection_running = false;

lv_style_t win_style;
lv_obj_t *main_scr;
lv_obj_t *select_scr;

// =============================== Selection =============================== //

lv_res_t r_select_act(lv_obj_t *obj) {
	int id = lv_obj_get_free_num(obj);
	lv_obj_t *window = lv_obj_get_parent(obj);
	selected_auton = id;
	return LV_RES_OK;
}

lv_res_t done_act(lv_obj_t *obj) {
	selection_done = true;
	return LV_RES_OK;
}

void pml::selector::do_selection() {
	if (selection_running || !pros::competition::is_disabled()) return;
	selection_running = true;

	main_scr = lv_scr_act();
	select_scr = lv_obj_create(NULL, NULL);
	lv_scr_load(select_scr);

	lv_obj_t *title_label = lv_label_create(select_scr, NULL);
	lv_label_set_text(title_label, "Select autonomous routine");
	lv_label_set_align(title_label, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_width(title_label, 232);
	lv_obj_align(title_label, NULL, LV_ALIGN_IN_TOP_LEFT, 8, 16);

	lv_obj_t *routine_list = lv_list_create(select_scr, NULL);
	lv_obj_set_size(routine_list, 232, 144);
	lv_obj_align(routine_list, NULL, LV_ALIGN_IN_TOP_LEFT, 8, 48);

	// Add routines to list
	for (pml::Routine routine : routines) {
		// Store current position in vector
		static int r_index = 0;

		lv_obj_t *new_btn = lv_list_add(routine_list, NULL, routine.name.c_str(), r_select_act);
		lv_obj_set_free_num(new_btn, r_index); // Set lvgl button number to index
		lv_btn_set_action(new_btn, LV_BTN_ACTION_CLICK, &r_select_act);

		r_index++;
	}

	lv_obj_t *nothing_btn = lv_list_add(routine_list, NULL, "Nothing", r_select_act);
	lv_obj_set_free_num(nothing_btn, -1);
	lv_btn_set_action(nothing_btn, LV_BTN_ACTION_CLICK, &r_select_act);

	lv_obj_t *done_btn = lv_btn_create(select_scr, NULL);
	lv_obj_set_size(done_btn, 232, 32);
	lv_obj_align(done_btn, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 8, -8);
	lv_btn_set_action(done_btn, LV_BTN_ACTION_CLICK, &done_act);
	lv_obj_t *done_label = lv_label_create(done_btn, NULL);
	lv_label_set_text(done_label, "Done");

	// Wait for user to be done
	while (!selection_done || !pros::competition::is_disabled()) {
		pros::delay(100);
	}

	lv_scr_load(main_scr);
	lv_obj_del(select_scr);

	selection_done = false; // Set back to false if want to re-select
	selection_running = false;
}

void pml::selector::exit_selection() {
	if (!selection_running) return;
	lv_scr_load(main_scr);
	lv_obj_del(select_scr);
}

// ============================= Other Methods ============================= //

void pml::selector::add_autons(std::vector<pml::Routine> new_routines) {
	routines.insert(routines.end(), new_routines.begin(), new_routines.end());
}

void pml::selector::do_auton() {
	if (selected_auton == -1) return; // If commanded to do nothing then return
	pml::Routine routine = routines.at(selected_auton);
	routine.action();
}