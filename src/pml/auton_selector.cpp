#include "auton_selector.hpp"

// =============================== Variables =============================== //

std::vector<selector::Routine> routines;
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
		selector::Routine selected = routines.at(id);
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
	FILE *save_file;
	save_file = fopen("/usd/autoconf.txt", "w");

	if (selected_auton == -1) {
		fputs("-1", save_file);
	} else {
		selector::Routine selected = routines.at(selected_auton);
		std::string routine_name = selected.name;

		// File format:
		// [id] [name]
		char file_data[sizeof(routine_name) + sizeof(selected_auton) + 1];
		sprintf(file_data, "%d %s", selected_auton, routine_name.c_str());

		fputs(file_data, save_file);
	}

	fclose(save_file);
	return LV_RES_OK;
}

void load_autoconf() {
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
		lv_obj_align(selected_label, NULL, LV_ALIGN_CENTER, 120, 0);
	} else {
		selector::Routine selected = routines.at(saved_id);
		std::string routine_name = selected.name;

		// Exit if routine name does not match
		if (saved_name != routine_name) return;

		// Update routine label
		char label_str[sizeof(routine_name) + 20];
		sprintf(label_str, "Selected routine:\n%s", routine_name.c_str());
		lv_label_set_text(selected_label, label_str);
		lv_obj_align(selected_label, NULL, LV_ALIGN_CENTER, 120, 0);
	}

	selected_auton = saved_id;
}

bool comp_started() {
	return (pros::competition::is_connected() && !pros::competition::is_disabled());
}

void selector::do_selection() {
	if (selection_running || comp_started()) return;
	selection_running = true;

	static lv_style_t bg_style;
	lv_style_copy(&bg_style, &lv_style_plain);
	bg_style.body.border.width = 0;
	bg_style.body.radius = 0;
	bg_style.body.main_color = lv_color_hex(0x262626);
	bg_style.body.grad_color = lv_color_hex(0x262626);
	bg_style.text.color = LV_COLOR_WHITE;

	select_cont = lv_cont_create(lv_scr_act(), NULL);
	lv_obj_set_size(select_cont, 480, 240);
	lv_obj_set_style(select_cont, &bg_style);

	lv_obj_t *title_label = lv_label_create(select_cont, NULL);
	lv_label_set_text(title_label, "Select autonomous routine");
	lv_label_set_align(title_label, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_width(title_label, 232);
	lv_obj_align(title_label, NULL, LV_ALIGN_IN_TOP_LEFT, 8, 16);

	static lv_style_t rlist_style;
	rlist_style.body.border.color = lv_color_hex(0x595959);
	rlist_style.body.border.width = 1;
	rlist_style.body.border.opa = 1;

	static lv_style_t routine_btn_style_rel;
	lv_style_copy(&routine_btn_style_rel, &lv_style_plain);
	routine_btn_style_rel.body.radius = 0;
	routine_btn_style_rel.body.border.width = 2;
	routine_btn_style_rel.body.border.color = lv_color_hex(0x404040);
	routine_btn_style_rel.body.main_color = lv_color_hex(0x404040);
	routine_btn_style_rel.body.grad_color = lv_color_hex(0x595959);
	routine_btn_style_rel.text.color = LV_COLOR_WHITE;
	routine_btn_style_rel.body.padding.ver = 16;
	routine_btn_style_rel.text.color = lv_color_hex(0xffffff);

	static lv_style_t routine_btn_style_pr;
	lv_style_copy(&routine_btn_style_pr, &routine_btn_style_rel);
	routine_btn_style_pr.body.main_color = lv_color_hex(0x404040);
	routine_btn_style_pr.body.grad_color = lv_color_hex(0x404040);
	routine_btn_style_pr.body.radius = 0;
	routine_btn_style_pr.body.padding.ver = 16;
	routine_btn_style_pr.text.color = lv_color_hex(0xffffff);

	lv_obj_t *routine_list = lv_list_create(select_cont, NULL);
	lv_obj_set_size(routine_list, 228, 184);
	lv_obj_align(routine_list, NULL, LV_ALIGN_IN_TOP_LEFT, 8, 48);
	lv_list_set_style(routine_list, LV_LIST_STYLE_BG, &rlist_style);
	lv_list_set_style(routine_list, LV_LIST_STYLE_BTN_REL, &routine_btn_style_rel);
	lv_list_set_style(routine_list, LV_LIST_STYLE_BTN_PR, &routine_btn_style_pr);

	selected_label = lv_label_create(select_cont, NULL);
	lv_label_set_align(selected_label, LV_LABEL_ALIGN_CENTER);
	lv_label_set_text(selected_label, "No routine\nselected");
	lv_obj_align(selected_label, NULL, LV_ALIGN_CENTER, 120, 0);

	// Add routines to list
	for (selector::Routine routine : routines) {
		// Store current position in vector
		static int r_index = 0;

		lv_obj_t *new_btn = lv_list_add(routine_list, NULL, routine.name.c_str(), r_select_act);
		lv_obj_set_free_num(new_btn, r_index); // Set lvgl button number to index
		lv_btn_set_action(new_btn, LV_BTN_ACTION_CLICK, &r_select_act);

		r_index++;
	}

	static lv_style_t round_btn_style_rel;
	lv_style_copy(&round_btn_style_rel, &routine_btn_style_rel);
	round_btn_style_rel.body.radius = 16;
	round_btn_style_rel.image.color.blue = 255;
	round_btn_style_rel.image.color.red = 255;
	round_btn_style_rel.image.color.green = 255;

	static lv_style_t round_btn_style_pr;
	lv_style_copy(&round_btn_style_pr, &routine_btn_style_pr);
	round_btn_style_pr.body.radius = 16;
	round_btn_style_rel.image.color.blue = 255;
	round_btn_style_rel.image.color.red = 255;
	round_btn_style_rel.image.color.green = 255;

	lv_obj_t *nothing_btn = lv_list_add(routine_list, NULL, "Nothing", r_select_act);
	lv_obj_set_free_num(nothing_btn, -1);
	lv_btn_set_style(nothing_btn, LV_BTN_STYLE_REL, &routine_btn_style_rel);
	lv_btn_set_style(nothing_btn, LV_BTN_STYLE_PR, &routine_btn_style_pr);
	lv_btn_set_action(nothing_btn, LV_BTN_ACTION_CLICK, &r_select_act);

	lv_obj_t *done_btn = lv_btn_create(select_cont, NULL);
	lv_obj_set_size(done_btn, 224, 32);
	lv_obj_align(done_btn, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -8, -8);
	lv_btn_set_action(done_btn, LV_BTN_ACTION_CLICK, &done_act);
	lv_btn_set_style(done_btn, LV_BTN_STYLE_REL, &round_btn_style_rel);
	lv_btn_set_style(done_btn, LV_BTN_STYLE_PR, &round_btn_style_pr);
	lv_obj_t *done_img = lv_img_create(done_btn, NULL);
	lv_img_set_src(done_img, SYMBOL_OK);

	if (pros::usd::is_installed()) {
		load_autoconf();
		lv_obj_set_size(done_btn, 192, 32);
		lv_obj_align(done_btn, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -8, -8);

		lv_obj_t *save_btn = lv_btn_create(select_cont, NULL);
		lv_obj_set_size(save_btn, 32, 32);
		lv_obj_align(save_btn, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -204, -8);
		lv_btn_set_action(save_btn, LV_BTN_ACTION_CLICK, &save_act);
		lv_btn_set_style(save_btn, LV_BTN_STYLE_REL, &round_btn_style_rel);
		lv_btn_set_style(save_btn, LV_BTN_STYLE_PR, &round_btn_style_pr);
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

void selector::exit_selection() {
	if (!selection_running) return;
	lv_obj_del(select_cont);
}

// ============================= Other Methods ============================= //

void selector::add_autons(std::vector<selector::Routine> new_routines) {
	routines.insert(routines.end(), new_routines.begin(), new_routines.end());
}

void selector::do_auton() {
	if (selected_auton == -1) return; // If commanded to do nothing then return
	selector::Routine routine = routines.at(selected_auton);
	routine.action();
}