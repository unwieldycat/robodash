#include "api.h"
#include "robodash/apix.h"
#include <cstring>

// ============================= SD Card Saving ============================= //

void rd::Selector::sd_save() {
	FILE *save_file;
	save_file = fopen("/usd/rd_auton.txt", "w");

	if (selected_routine == nullptr) {
		fputs("", save_file);
	} else {
		std::string routine_name = selected_routine->first;

		char file_data[sizeof(routine_name)];
		sprintf(file_data, "%s", routine_name.c_str());

		fputs(file_data, save_file);
	}

	fclose(save_file);
}

void rd::Selector::sd_load() {
	FILE *save_file;
	save_file = fopen("/usd/rd_auton.txt", "r");
	if (!save_file) return;

	// Get file size
	fseek(save_file, 0L, SEEK_END);
	int file_size = ftell(save_file);
	rewind(save_file);

	// Read contents
	char saved_name[file_size];
	fscanf(save_file, "%[^\n]", saved_name);
	fclose(save_file);

	// None selected condition
	if (strcmp(saved_name, "") == 0) {
		lv_label_set_text(selected_label, "No routine\nselected");
		lv_obj_align(selected_label, LV_ALIGN_CENTER, 120, 0);

		selected_routine = nullptr;
		return;
	}

	for (rd::Selector::routine_t &r : routines) {
		if (strcmp(r.first.c_str(), saved_name) == 0) selected_routine = &r;
	}

	if (selected_routine != nullptr) {
		// Update routine label
		char label_str[sizeof(saved_name) + 20];
		sprintf(label_str, "Selected routine:\n%s", selected_routine->first.c_str());
		lv_label_set_text(selected_label, label_str);
		lv_obj_align(selected_label, LV_ALIGN_CENTER, 120, 0);
	}
}

// ============================== UI Callbacks ============================== //

void rd::Selector::select_cb(lv_event_t *event) {
	lv_obj_t *obj = lv_event_get_target(event);
	rd::Selector::routine_t *routine = (rd::Selector::routine_t *)lv_event_get_user_data(event);
	rd::Selector *selector = (rd::Selector *)lv_obj_get_user_data(obj);
	if (selector == nullptr) return;

	if (routine == nullptr) {
		lv_label_set_text(selector->selected_label, "No routine\nselected");
		lv_obj_align(selector->selected_label, LV_ALIGN_CENTER, 120, 0);
	} else {
		const char *routine_name = routine->first.c_str();

		char label_str[strlen(routine_name) + 20];
		sprintf(label_str, "Selected routine:\n%s", routine_name);
		lv_label_set_text(selector->selected_label, label_str);
		lv_obj_align(selector->selected_label, LV_ALIGN_CENTER, 120, 0);
	}

	selector->selected_routine = routine;
}

void rd::Selector::save_cb(lv_event_t *event) {
	lv_obj_t *obj = lv_event_get_target(event);
	rd::Selector *selector = (rd::Selector *)lv_obj_get_user_data(obj);
	if (selector == nullptr) return;
	selector->sd_save();

	lv_obj_clear_flag(selector->saved_toast, LV_OBJ_FLAG_HIDDEN);
	lv_anim_start(&selector->anim_toast);
}

// ============================== Constructor ============================== //

rd::Selector::Selector(std::vector<routine_t> new_routines) {

	// ----------------------------- Create UI ----------------------------- //

	this->view = rd_view_create("Auton Selector");

	lv_obj_set_style_bg_color(view->obj, color_bg, 0);

	lv_obj_t *routine_list = lv_list_create(view->obj);
	lv_obj_set_size(routine_list, 228, 192);
	lv_obj_align(routine_list, LV_ALIGN_BOTTOM_LEFT, 8, -8);
	lv_obj_add_style(routine_list, &style_list, 0);

	selected_label = lv_label_create(view->obj);
	lv_label_set_text(selected_label, "No routine\nselected");
	lv_obj_add_style(selected_label, &style_text_centered, 0);
	lv_obj_align(selected_label, LV_ALIGN_CENTER, 120, 0);

	lv_obj_t *nothing_btn = lv_list_add_btn(routine_list, NULL, "Nothing");
	lv_obj_add_event_cb(nothing_btn, &select_cb, LV_EVENT_PRESSED, nullptr);
	lv_obj_set_user_data(nothing_btn, this);
	lv_obj_add_style(nothing_btn, &style_list_btn, 0);
	lv_obj_add_style(nothing_btn, &style_list_btn_pr, LV_STATE_PRESSED);

	lv_obj_t *title = lv_label_create(view->obj);
	lv_label_set_text(title, "Select autonomous routine");
	lv_obj_add_style(title, &style_text_large, 0);
	lv_obj_align(title, LV_ALIGN_TOP_LEFT, 8, 12);

	if (pros::usd::is_installed()) {
		saved_toast = lv_label_create(view->obj);
		lv_label_set_text(saved_toast, "Saved to SD");
		lv_obj_add_style(saved_toast, &style_text_centered, 0);
		lv_obj_add_style(saved_toast, &style_text_small, 0);
		lv_obj_align(saved_toast, LV_ALIGN_BOTTOM_RIGHT, -16, -16);
		lv_obj_add_flag(saved_toast, LV_OBJ_FLAG_HIDDEN);

		lv_obj_t *save_btn = lv_btn_create(view->obj);
		lv_obj_set_size(save_btn, 64, 32);
		lv_obj_align(save_btn, LV_ALIGN_BOTTOM_RIGHT, -172, -8);
		lv_obj_add_event_cb(save_btn, &save_cb, LV_EVENT_PRESSED, NULL);
		lv_obj_add_style(save_btn, &style_btn, 0);
		lv_obj_add_style(save_btn, &style_btn_outline, 0);
		lv_obj_add_style(save_btn, &style_btn_outline_pr, LV_STATE_PRESSED);
		lv_obj_set_user_data(save_btn, this);

		lv_obj_t *save_img = lv_img_create(save_btn);
		lv_img_set_src(save_img, LV_SYMBOL_SAVE);
		lv_obj_set_align(save_img, LV_ALIGN_CENTER);
	}

	lv_anim_init(&anim_toast);
	lv_anim_set_var(&anim_toast, saved_toast);
	lv_anim_set_time(&anim_toast, 255);
	lv_anim_set_delay(&anim_toast, 3000);
	lv_anim_set_exec_cb(&anim_toast, &anim_text_opa_cb);
	lv_anim_set_deleted_cb(&anim_toast, &anim_del_cb);
	lv_anim_set_values(&anim_toast, 255, 0);

	// ----------------------------- Add autons ----------------------------- //

	for (routine_t routine : new_routines) {
		routines.push_back(routine);
	}

	for (routine_t &routine : routines) {
		lv_obj_t *new_btn = lv_list_add_btn(routine_list, NULL, routine.first.c_str());
		lv_obj_add_style(new_btn, &style_list_btn, 0);
		lv_obj_add_style(new_btn, &style_list_btn_pr, LV_STATE_PRESSED);
		lv_obj_set_user_data(new_btn, this);
		lv_obj_add_event_cb(new_btn, &select_cb, LV_EVENT_PRESSED, &routine);
	}

	if (pros::usd::is_installed()) sd_load();
}

// ============================= Other Methods ============================= //

void rd::Selector::run_auton() {
	if (selected_routine == nullptr) return; // If commanded to do nothing then return
	selected_routine->second();
}

void rd::Selector::focus() { rd_view_focus(this->view); }