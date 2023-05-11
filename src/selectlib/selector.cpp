#include "selector.hpp"
#include "common/styles.hpp"

// =============================== Variables =============================== //

std::vector<gui::selector::routine_t> routines;
int selected_auton = -1; // Default -1 to do nothing
bool selection_done = false;
bool selection_running = false;

lv_obj_t *select_cont;
lv_obj_t *selected_label;
lv_obj_t *saved_toast;

// ============================= SD Card Saving ============================= //

void sdconf_save() {
	FILE *save_file;
	save_file = fopen("/usd/autoconf.txt", "w");

	if (selected_auton == -1) {
		fputs("-1", save_file);
	} else {
		gui::selector::routine_t selected = routines.at(selected_auton);
		std::string routine_name = selected.first;

		// File format:
		// [id] [name]
		char file_data[sizeof(routine_name) + sizeof(selected_auton) + 1];
		sprintf(file_data, "%d %s", selected_auton, routine_name.c_str());

		fputs(file_data, save_file);
	}

	fclose(save_file);
}

void sdconf_load() {
	FILE *save_file;
	save_file = fopen("/usd/autoconf.txt", "r");
	if (!save_file) return;

	// Get file size
	fseek(save_file, 0L, SEEK_END);
	int file_size = ftell(save_file);
	rewind(save_file);

	// Read contents
	int saved_id;
	char saved_name[1000];
	fscanf(save_file, "%d %[^\n]", &saved_id, saved_name);
	fclose(save_file);

	if (saved_id == -1) {
		lv_label_set_text(selected_label, "No routine\nselected");
		lv_obj_align(selected_label, LV_ALIGN_CENTER, 120, 0);
	} else {
		gui::selector::routine_t selected = routines.at(saved_id);
		std::string routine_name = selected.first;

		// Exit if routine name does not match
		if (saved_name != routine_name) return;

		// Update routine label
		char label_str[sizeof(routine_name) + 20];
		sprintf(label_str, "Selected routine:\n%s", routine_name.c_str());
		lv_label_set_text(selected_label, label_str);
		lv_obj_align(selected_label, LV_ALIGN_CENTER, 120, 0);
	}

	selected_auton = saved_id;
}

// =============================== Selection =============================== //

// FIXME: Obj free num is not a thin anymore

lv_res_t r_select_act(lv_obj_t *obj) {
	/*
	int id = lv_obj_get_free_num(obj);

	   if (id == -1) {
	       lv_label_set_text(selected_label, "No routine\nselected");
	       lv_obj_align(selected_label, NULL, LV_ALIGN_CENTER, 120, 0);
	   } else {
	       gui::selector::routine_t selected = routines.at(id);
	       std::string routine_name = selected.first;
	       char label_str[sizeof(routine_name) + 20];
	       sprintf(label_str, "Selected routine:\n%s", routine_name.c_str());
	       lv_label_set_text(selected_label, label_str);
	       lv_obj_align(selected_label, NULL, LV_ALIGN_CENTER, 120, 0);
	   }

	   selected_auton = id;
	   return LV_RES_OK;
   */
}

lv_res_t done_act(lv_obj_t *obj) {
	selection_done = true;
	return LV_RES_OK;
}

lv_res_t save_act(lv_obj_t *obj) {
	sdconf_save();
	// lv_obj_set_hidden(saved_toast, false);
	return LV_RES_OK;
}

bool comp_started() {
	return (pros::competition::is_connected() && !pros::competition::is_disabled());
}

void gui::selector::do_selection() {
	if (selection_running || comp_started()) return;
	selection_running = true;

	select_cont = lv_obj_create(lv_scr_act());
	lv_obj_set_size(select_cont, 480, 240);
	// lv_obj_set_style(select_cont, &bg_style);

	lv_obj_t *title_label = lv_label_create(select_cont);
	lv_label_set_text(title_label, "Select autonomous routine");
	// lv_label_set_align(title_label, LV_ALIGN_CENTER);
	lv_obj_set_width(title_label, 232);
	lv_obj_align(title_label, LV_ALIGN_TOP_LEFT, 8, 16);

	lv_obj_t *routine_list = lv_list_create(select_cont);
	lv_obj_set_size(routine_list, 228, 184);
	lv_obj_align(routine_list, LV_ALIGN_TOP_LEFT, 8, 48);
	// FIXME:
	// lv_list_set_style(routine_list, LV_LIST_STYLE_BG, &list_style);
	// lv_list_set_style(routine_list, LV_LIST_STYLE_BTN_REL, &list_btn_style_rel);
	// lv_list_set_style(routine_list, LV_LIST_STYLE_BTN_PR, &list_btn_style_pr);

	selected_label = lv_label_create(select_cont);
	// lv_label_set_align(selected_label, LV_LABEL_ALIGN_CENTER);
	lv_label_set_text(selected_label, "No routine\nselected");
	lv_obj_align(selected_label, LV_ALIGN_CENTER, 120, 0);

	// Add routines to list
	for (gui::selector::routine_t routine : routines) {
		// Store current position in vector
		static int r_index = 0;

		// FIXME: LVGL list
		/*
		lv_obj_t *new_btn = lv_list_add(routine_list, NULL, routine.first.c_str(), r_select_act);
		lv_obj_set_free_num(new_btn, r_index); // Set lvgl button number to index
		lv_btn_set_action(new_btn, LV_BTN_ACTION_CLICK, &r_select_act);
		*/

		r_index++;
	}

	// FIXME: LVGL list
	/*
	lv_obj_t *nothing_btn = lv_list_add(routine_list, NULL, "Nothing", r_select_act);
	// lv_obj_set_free_num(nothing_btn, -1);
	lv_btn_set_style(nothing_btn, LV_BTN_STYLE_REL, &list_btn_style_rel);
	lv_btn_set_style(nothing_btn, LV_BTN_STYLE_PR, &list_btn_style_pr);
	lv_btn_set_action(nothing_btn, LV_BTN_ACTION_CLICK, &r_select_act);*/

	lv_obj_t *done_btn = lv_btn_create(select_cont);
	lv_obj_set_size(done_btn, 224, 32);
	lv_obj_align(done_btn, LV_ALIGN_BOTTOM_RIGHT, -8, -8);
	// lv_btn_set_action(done_btn, LV_BTN_ACTION_CLICK, &done_act);
	// lv_btn_set_style(done_btn, LV_BTN_STYLE_REL, &round_btn_style_rel);
	// lv_btn_set_style(done_btn, LV_BTN_STYLE_PR, &round_btn_style_pr);
	lv_obj_t *done_img = lv_img_create(done_btn);
	// lv_img_set_src(done_img, SYMBOL_OK);

	if (pros::usd::is_installed()) {
		sdconf_load();
		lv_obj_set_size(done_btn, 160, 32);
		lv_obj_align(done_btn, LV_ALIGN_BOTTOM_RIGHT, -8, -8);

		saved_toast = lv_label_create(select_cont);
		lv_label_set_text(saved_toast, "Saved selection to SD card");
		// lv_label_set_align(saved_toast, LV_LABEL_ALIGN_CENTER);
		lv_obj_align(saved_toast, LV_ALIGN_CENTER, 190, 70);
		// lv_label_set_style(saved_toast, &small_text);
		//  lv_obj_set_hidden(saved_toast, true);

		lv_obj_t *save_btn = lv_btn_create(select_cont);
		lv_obj_set_size(save_btn, 64, 32);
		lv_obj_align(save_btn, LV_ALIGN_BOTTOM_RIGHT, -172, -8);
		// lv_btn_set_action(save_btn, LV_BTN_ACTION_CLICK, &save_act);
		// lv_btn_set_style(save_btn, LV_BTN_STYLE_REL, &outline_round_btn_style_rel);
		// lv_btn_set_style(save_btn, LV_BTN_STYLE_PR, &outline_round_btn_style_pr);
		lv_obj_t *save_img = lv_img_create(save_btn);
		// lv_img_set_src(save_img, SYMBOL_SAVE);
	}

	// Wait for user to be done or for match to start
	while (!selection_done || comp_started()) {
		pros::delay(100);
	}

	// Delete screen and reset variables to default
	lv_obj_del(select_cont);
	selection_done = false;
	selection_running = false;
}

void gui::selector::exit_selection() {
	if (!selection_running) return;
	lv_obj_del(select_cont);
	selection_running = false;
	selection_done = false;
}

// ============================= Other Methods ============================= //

void gui::selector::add_autons(std::vector<selector::routine_t> new_routines) {
	routines.insert(routines.end(), new_routines.begin(), new_routines.end());
}

void gui::selector::do_auton() {
	if (selected_auton == -1) return; // If commanded to do nothing then return
	selector::routine_t routine = routines.at(selected_auton);
	routine.second();
}
