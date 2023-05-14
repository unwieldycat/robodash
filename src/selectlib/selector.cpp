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

void r_select_act(lv_event_t *event) {

	lv_obj_t *obj = lv_event_get_target(event);
	int *id = (int *)lv_event_get_user_data(event);

	if (*id == -1) {
		lv_label_set_text(selected_label, "No routine\nselected");
		lv_obj_align(selected_label, LV_ALIGN_CENTER, 120, 0);
	} else {
		gui::selector::routine_t selected = routines.at(*id);
		std::string routine_name = selected.first;
		char label_str[sizeof(routine_name) + 20];
		sprintf(label_str, "Selected routine:\n%s", routine_name.c_str());
		lv_label_set_text(selected_label, label_str);
		lv_obj_align(selected_label, LV_ALIGN_CENTER, 120, 0);
	}

	selected_auton = *id;
}

void done_act(lv_event_t *event) { selection_done = true; }

void save_act(lv_event_t *event) {
	sdconf_save();
	lv_obj_clear_flag(saved_toast, LV_OBJ_FLAG_HIDDEN);
}

bool comp_started() {
	return (pros::competition::is_connected() && !pros::competition::is_disabled());
}

void gui::selector::do_selection() {
	if (selection_running || comp_started()) return;
	selection_running = true;

	select_cont = lv_obj_create(lv_scr_act());
	lv_obj_set_size(select_cont, 480, 240);
	lv_obj_add_style(select_cont, &style_bg, 0);

	lv_obj_t *title_label = lv_label_create(select_cont);
	lv_label_set_text(title_label, "Select autonomous routine");
	lv_obj_add_style(title_label, &style_text_centered, 0);
	lv_obj_set_width(title_label, 232);
	lv_obj_align(title_label, LV_ALIGN_TOP_LEFT, 8, 16);

	lv_obj_t *routine_list = lv_list_create(select_cont);
	lv_obj_set_size(routine_list, 228, 184);
	lv_obj_align(routine_list, LV_ALIGN_TOP_LEFT, 8, 48);
	lv_obj_add_style(routine_list, &style_list, 0);

	selected_label = lv_label_create(select_cont);
	lv_obj_add_style(selected_label, &style_text_centered, 0);
	lv_label_set_text(selected_label, "No routine\nselected");
	lv_obj_align(selected_label, LV_ALIGN_CENTER, 120, 0);

	// Add routines to list
	for (gui::selector::routine_t routine : routines) {
		// Store current position in vector
		static int r_index = 0;

		lv_obj_t *new_btn = lv_list_add_btn(routine_list, NULL, routine.first.c_str());
		lv_obj_add_style(new_btn, &style_list_btn, 0);
		lv_obj_add_style(new_btn, &style_list_btn_pr, LV_STATE_PRESSED);
		lv_obj_add_event_cb(new_btn, &r_select_act, LV_EVENT_PRESSED, &r_index);

		r_index++;
	}

	int nothing_id = -1; // bruh

	lv_obj_t *nothing_btn = lv_list_add_btn(routine_list, NULL, "Nothing");
	lv_obj_add_event_cb(nothing_btn, &r_select_act, LV_EVENT_PRESSED, &nothing_id);
	lv_obj_add_style(nothing_btn, &style_list_btn, 0);
	lv_obj_add_style(nothing_btn, &style_list_btn_pr, LV_STATE_PRESSED);

	lv_obj_t *done_btn = lv_btn_create(select_cont);
	lv_obj_set_size(done_btn, 224, 32);
	lv_obj_align(done_btn, LV_ALIGN_BOTTOM_RIGHT, -8, -8);
	lv_obj_add_event_cb(done_btn, &done_act, LV_EVENT_PRESSED, NULL);
	lv_obj_add_style(done_btn, &style_btn, 0);
	lv_obj_add_style(done_btn, &style_btn_primary, 0);
	lv_obj_add_style(done_btn, &style_btn_primary_pr, LV_STATE_PRESSED);

	lv_obj_t *done_img = lv_img_create(done_btn);
	lv_img_set_src(done_img, LV_SYMBOL_OK);

	if (pros::usd::is_installed()) {
		sdconf_load();
		lv_obj_set_size(done_btn, 160, 32);
		lv_obj_align(done_btn, LV_ALIGN_BOTTOM_RIGHT, -8, -8);

		saved_toast = lv_label_create(select_cont);
		lv_label_set_text(saved_toast, "Saved selection to SD card");
		lv_obj_add_style(saved_toast, &style_text_centered, 0);
		lv_obj_add_style(saved_toast, &style_text_small, 0);
		lv_obj_align(saved_toast, LV_ALIGN_CENTER, 190, 70);
		lv_obj_add_flag(saved_toast, LV_OBJ_FLAG_HIDDEN);

		lv_obj_t *save_btn = lv_btn_create(select_cont);
		lv_obj_set_size(save_btn, 64, 32);
		lv_obj_align(save_btn, LV_ALIGN_BOTTOM_RIGHT, -172, -8);
		lv_obj_add_event_cb(save_btn, &save_act, LV_EVENT_PRESSED, NULL);
		lv_obj_add_style(save_btn, &style_btn, 0);
		lv_obj_add_style(save_btn, &style_btn_outline, 0);
		lv_obj_add_style(save_btn, &style_btn_outline_pr, LV_STATE_PRESSED);

		lv_obj_t *save_img = lv_img_create(save_btn);
		lv_img_set_src(save_img, LV_SYMBOL_SAVE);
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
