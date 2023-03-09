#include "auton_selector.hpp"
#include "common/styles.hpp"

// =============================== Variables =============================== //

std::vector<pml::Routine> routines;
int selected_auton = -1; // Default -1 to do nothing
bool selection_done = false;
bool selection_running = false;

lv_style_t win_style;
lv_obj_t *select_cont;
lv_obj_t *selected_label;

// =============================== Selection =============================== //

lv_res_t r_select_act(lv_obj_t *obj) {
	int id = lv_obj_get_free_num(obj);

	if (id == -1) {
		lv_label_set_text(selected_label, "No routine\nselected");
		lv_obj_align(selected_label, NULL, LV_ALIGN_CENTER, 120, 0);
	} else {
		pml::Routine selected = routines.at(id);
		std::string routine_name = selected.name;
		char label_str[sizeof(routine_name) + 20];
		sprintf(label_str, "Selected routine:\n%s", routine_name.c_str());
		lv_label_set_text(selected_label, label_str);
		lv_obj_align(selected_label, NULL, LV_ALIGN_CENTER, 120, 0);
	}

	selected_auton = id;
	return LV_RES_OK;
}

lv_res_t done_act(lv_obj_t *obj) {
	selection_done = true;
	return LV_RES_OK;
}

lv_res_t save_act(lv_obj_t *obj) {
	if (!pros::usd::is_installed()) return LV_RES_OK; // silently fail

	if (selected_auton == -1) {
		remove("/usd/autoconf.txt");
		return LV_RES_OK;
	}

	pml::Routine selected = routines.at(selected_auton);
	std::string routine_name = selected.name;

	// File format:
	// [id] [name]
	char file_data[sizeof(routine_name) + sizeof(selected_auton) + 1];
	sprintf(file_data, "%d %s", selected_auton, routine_name.c_str());

	FILE *save_file;
	save_file = fopen("/usd/autoconf.txt", "w");
	fputs(file_data, save_file);
	fclose(save_file);

	return LV_RES_OK;
}

bool comp_started() {
	return (pros::competition::is_connected() && !pros::competition::is_disabled());
}

void pml::selector::do_selection() {
	if (selection_running || comp_started()) return;
	selection_running = true;

	init_styles();

	select_cont = lv_cont_create(lv_scr_act(), NULL);
	lv_obj_set_size(select_cont, 480, 240);
	lv_obj_set_style(select_cont, &bg_style);

	lv_obj_t *title_label = lv_label_create(select_cont, NULL);
	lv_label_set_text(title_label, "Select autonomous routine");
	lv_label_set_align(title_label, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_width(title_label, 232);
	lv_obj_align(title_label, NULL, LV_ALIGN_IN_TOP_LEFT, 8, 16);

	lv_obj_t *routine_list = lv_list_create(select_cont, NULL);
	lv_obj_set_size(routine_list, 228, 184);
	lv_obj_align(routine_list, NULL, LV_ALIGN_IN_TOP_LEFT, 8, 48);

	selected_label = lv_label_create(select_cont, NULL);
	lv_label_set_align(selected_label, LV_LABEL_ALIGN_CENTER);
	lv_label_set_text(selected_label, "No routine\nselected");
	lv_obj_align(selected_label, NULL, LV_ALIGN_CENTER, 120, 0);

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

	lv_obj_t *done_btn = lv_btn_create(select_cont, NULL);
	lv_obj_set_size(done_btn, 224, 32);
	lv_obj_align(done_btn, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -8, -8);
	lv_btn_set_action(done_btn, LV_BTN_ACTION_CLICK, &done_act);
	lv_obj_t *done_img = lv_img_create(done_btn, NULL);
	lv_img_set_src(done_img, SYMBOL_OK);

	if (pros::usd::is_installed()) {
		lv_obj_set_size(done_btn, 192, 32);
		lv_obj_align(done_btn, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -8, -8);

		lv_obj_t *save_btn = lv_btn_create(select_cont, NULL);
		lv_obj_set_size(save_btn, 32, 32);
		lv_obj_align(save_btn, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -204, -8);
		lv_btn_set_action(save_btn, LV_BTN_ACTION_CLICK, &save_act);
		lv_obj_t *save_img = lv_img_create(save_btn, NULL);
		lv_img_set_src(save_img, SYMBOL_SAVE);
	}

	// Wait for user to be done
	while (!selection_done || comp_started()) {
		pros::delay(100);
	}

	lv_obj_del(select_cont);

	selection_done = false; // Set back to false if want to re-select
	selection_running = false;
}

void pml::selector::exit_selection() {
	if (!selection_running) return;
	lv_obj_del(select_cont);
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