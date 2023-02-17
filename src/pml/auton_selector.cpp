#include "auton_selector.hpp"

// =============================== Variables =============================== //

std::vector<pml::auton_selector::Routine> routines;
int selected_auton = -1; // Default -1 to do nothing
bool selection_done = false;
bool selection_running = false;

lv_style_t win_style;
lv_obj_t *select_win;

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

void pml::auton_selector::do_selection() {
	if (selection_running) return;
	selection_running = true;

	// TODO: Fix lvgl window padding and sizing issues

	// Style to remove padding from window background
	lv_style_copy(&win_style, &lv_style_transp);
	win_style.body.padding.ver = 0;

	select_win = lv_win_create(lv_scr_act(), NULL);
	lv_win_set_style(select_win, LV_WIN_STYLE_CONTENT_BG, &win_style);
	lv_win_set_btn_size(select_win, 12);
	lv_win_set_title(select_win, "Autonomous Selection");
	lv_win_set_layout(select_win, LV_LAYOUT_OFF);
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

	lv_obj_t *nothing_btn = lv_list_add(routine_list, NULL, "Nothing", r_select_act);
	lv_obj_set_free_num(nothing_btn, -1);
	lv_btn_set_action(nothing_btn, LV_BTN_ACTION_CLICK, &r_select_act);

	lv_obj_t *done_btn = lv_btn_create(select_win, NULL);
	lv_obj_set_pos(done_btn, 0, 184);
	lv_obj_set_size(done_btn, 232, 30);
	lv_btn_set_action(done_btn, LV_BTN_ACTION_CLICK, &done_act);
	lv_obj_t *done_label = lv_label_create(done_btn, NULL);
	lv_label_set_text(done_label, "Done");

	// Filter buttons
	// TODO: Implement filtering list

	lv_obj_t *b_filter_btn = lv_btn_create(select_win, NULL);
	lv_obj_set_size(b_filter_btn, 80, 32);
	lv_obj_set_pos(b_filter_btn, 304, 184);
	lv_obj_t *b_filter_label = lv_label_create(b_filter_btn, NULL);
	lv_label_set_text(b_filter_label, "Both");

	lv_obj_t *l_filter_btn = lv_btn_create(select_win, NULL);
	lv_obj_set_size(l_filter_btn, 32, 32);
	lv_obj_set_pos(l_filter_btn, 388, 184);
	lv_obj_t *l_filter_label = lv_label_create(l_filter_btn, NULL);
	lv_label_set_text(l_filter_label, "L");

	lv_obj_t *r_filter_btn = lv_btn_create(select_win, NULL);
	lv_obj_set_size(r_filter_btn, 32, 32);
	lv_obj_set_pos(r_filter_btn, 426, 184);
	lv_obj_t *r_filter_label = lv_label_create(r_filter_btn, NULL);
	lv_label_set_text(r_filter_label, "R");

	// Wait for user to be done
	while (!selection_done) {
		pros::delay(100);
	}

	lv_obj_del(select_win);
	selection_done = false; // Set back to false if want to re-select
	selection_running = false;
}

void pml::auton_selector::exit_selection() {
	if (!selection_running) return;
	lv_obj_del(select_win);
}

// ============================= Other Methods ============================= //

void pml::auton_selector::add_autons(std::vector<pml::auton_selector::Routine> new_routines) {
	routines.insert(routines.end(), new_routines.begin(), new_routines.end());
}

void pml::auton_selector::do_auton() {
	if (selected_auton == -1) return; // If commanded to do nothing then return
	pml::auton_selector::Routine routine = routines.at(selected_auton);
	routine.action();
}