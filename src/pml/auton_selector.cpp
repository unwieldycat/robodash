#include "auton_selector.hpp"
#include "dashboard.hpp"

// =============================== Variables =============================== //

std::vector<pml::auton_selector::Routine> routines;
int selected_auton;

// =============================== Selection =============================== //

bool selection_done = false;

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

void pml::auton_selector::do_selection() {
	// Style to remove padding from window background
	lv_style_t win_style;
	lv_style_copy(&win_style, &lv_style_transp);
	win_style.body.padding.ver = 0;

	lv_obj_t *select_win = lv_win_create(lv_scr_act(), NULL);
	lv_win_set_style(select_win, LV_WIN_STYLE_CONTENT_BG, &win_style);
	lv_win_set_btn_size(select_win, 12);
	lv_win_set_title(select_win, "Autonomous Selection");
	lv_obj_t *win_close_btn = lv_win_add_btn(select_win, SYMBOL_CLOSE, done_act);

	lv_obj_t *title_label = lv_label_create(select_win, NULL);
	lv_label_set_text(title_label, "Select autonomous routine");
	lv_obj_align(title_label, NULL, LV_ALIGN_IN_TOP_MID, 0, 4);

	lv_obj_t *routine_list = lv_list_create(select_win, NULL);
	lv_obj_align(routine_list, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 48);
	lv_obj_set_size(routine_list, 458, 130);

	// Add routines to list
	for (auton_selector::Routine routine : routines) {
		// Store current position in vector
		static int r_index = 0;

		lv_obj_t *new_btn = lv_list_add(routine_list, NULL, routine.name.c_str(), r_select_act);
		lv_obj_set_free_num(new_btn, r_index); // Set lvgl button number to index
		lv_btn_set_action(new_btn, LV_BTN_ACTION_CLICK, &r_select_act);

		r_index++;
	}

	lv_obj_t *done_btn = lv_btn_create(select_win, NULL);
	lv_obj_align(done_btn, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 8, 8);
	lv_obj_set_pos(done_btn, 0, 176);
	lv_obj_set_size(done_btn, 232, 30);
	lv_btn_set_action(done_btn, LV_BTN_ACTION_CLICK, &done_act);
	lv_obj_t *done_label = lv_label_create(done_btn, NULL);
	lv_label_set_text(done_label, "Done");

	// Wait for user to be done or for match to start
	while (!selection_done) {
		if (pros::competition::is_connected() && !pros::competition::is_disabled()) break;
		pros::delay(100);
	}

	lv_obj_del(select_win);
}

// ============================= Other Methods ============================= //

void pml::auton_selector::add_autons(std::vector<pml::auton_selector::Routine> new_routines) {
	routines.insert(routines.end(), new_routines.begin(), new_routines.end());
}

void pml::auton_selector::do_auton() {
	pml::auton_selector::Routine routine = routines.at(selected_auton);
	routine.action();
}