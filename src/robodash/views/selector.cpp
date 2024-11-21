#include "selector.hpp"
#include "api.h"
#include "robodash/apix.h"
#include "robodash/impl/styles.h"
#include <cstring>

const char *file_name = "/usd/rd_auton.txt";

// ============================= SD Card Saving ============================= //

void rd::Selector::sd_save() {
	FILE *save_file;

	// Ensure the file exists
	save_file = fopen(file_name, "a");
	fclose(save_file);

	// Open in read mode
	save_file = fopen(file_name, "r");
	if (!save_file) return;

	// Get file size
	fseek(save_file, 0L, SEEK_END);
	int file_size = ftell(save_file);
	rewind(save_file);

	char new_text[file_size];
	char line[256];
	char saved_selector[256];

	new_text[0] = '\0'; // THIS IS VERY IMPORTANT

	// Find and remove keys for our selector
	while (fgets(line, 256, save_file)) {
		sscanf(line, "%[^:] \n", saved_selector);
		if (saved_selector == this->name) continue;
		strcat(new_text, line);
	}

	fclose(save_file);
	save_file = fopen(file_name, "w");
	fputs(new_text, save_file);

	// Write save data
	if (selected_routine != nullptr) {
		const char *selector_name = this->name.c_str();
		const char *routine_name = selected_routine->name.c_str();

		char file_data[strlen(selector_name) + strlen(routine_name) + 2];
		sprintf(file_data, "%s: %s\n", selector_name, routine_name);
		fputs(file_data, save_file);
	}

	fclose(save_file);
}

void rd::Selector::sd_load() {
	FILE *save_file;
	save_file = fopen(file_name, "r");
	if (!save_file) return;

	// Read contents
	char line[256];
	char saved_selector[256];
	char saved_name[256];

	while (fgets(line, 256, save_file)) {
		sscanf(line, "%[^:]: %[^\n\0]", saved_selector, saved_name);
		if (saved_selector == this->name) break;
	}

	fclose(save_file);

	// None selected or not our selector
	if (strcmp(saved_name, "") == 0 || saved_selector != this->name) {
		selected_routine = nullptr;
		return;
	}

	for (rd::Selector::routine_t &r : routines) {
		if (strcmp(r.name.c_str(), saved_name) != 0) continue;
		selected_routine = &r;
		run_callbacks();
	}

	if (selected_routine != nullptr) {
		// Update routine label
		char label_str[strlen(saved_name) + 20];
		sprintf(label_str, "Selected routine:\n%s", selected_routine->name.c_str());
		lv_label_set_text(selected_label, label_str);
		lv_obj_align(selected_label, LV_ALIGN_CENTER, 120, 0);

		if (selected_routine->img.empty() || !pros::usd::is_installed()) return;

		lv_img_set_src(this->selected_img, selected_routine->img.c_str());
		lv_obj_clear_flag(this->selected_img, LV_OBJ_FLAG_HIDDEN);
	}
}

// ============================== UI Callbacks ============================== //

void rd::Selector::select_cb(lv_event_t *event) {
	lv_obj_t *obj = lv_event_get_target(event);
	rd::Selector::routine_t *routine = (rd::Selector::routine_t *)lv_event_get_user_data(event);
	rd::Selector *selector = (rd::Selector *)lv_obj_get_user_data(obj);
	if (selector == nullptr) return;

	selector->selected_routine = routine;
	selector->sd_save();

	selector->run_callbacks();

	if (routine == nullptr) {
		lv_label_set_text(selector->selected_label, "No routine\nselected");
		lv_obj_add_flag(selector->selected_img, LV_OBJ_FLAG_HIDDEN);
		return;
	}

	const char *routine_name = routine->name.c_str();

	char label_str[strlen(routine_name) + 20];
	sprintf(label_str, "Selected routine:\n%s", routine_name);
	lv_label_set_text(selector->selected_label, label_str);
	lv_obj_align(selector->selected_label, LV_ALIGN_CENTER, 120, 0);

	if (routine->img.empty() || !pros::usd::is_installed()) {
		lv_obj_add_flag(selector->selected_img, LV_OBJ_FLAG_HIDDEN);
		return;
	}

	lv_img_set_src(selector->selected_img, routine->img.c_str());
	lv_obj_clear_flag(selector->selected_img, LV_OBJ_FLAG_HIDDEN);
}

// ============================== Constructor ============================== //

rd::Selector::Selector(std::vector<routine_t> autons) : Selector("Auton Selector", autons) {}

rd::Selector::Selector(std::string name, std::vector<routine_t> new_routines) {
	this->name = name;
	this->selected_routine = nullptr;

	// ----------------------------- Create UI ----------------------------- //

	this->view = rd_view_create(name.c_str());

	lv_obj_set_style_bg_color(view->obj, color_bg, 0);

	lv_obj_t *routine_list = lv_list_create(view->obj);
	lv_obj_set_size(routine_list, 228, 192);
	lv_obj_align(routine_list, LV_ALIGN_TOP_LEFT, 8, 40);
	lv_obj_add_style(routine_list, &style_list, 0);

	lv_obj_t *selected_cont = lv_obj_create(view->obj);
	lv_obj_add_style(selected_cont, &style_transp, 0);
	lv_obj_set_layout(selected_cont, LV_LAYOUT_FLEX);
	lv_obj_set_size(selected_cont, 240, 240);
	lv_obj_align(selected_cont, LV_ALIGN_CENTER, 120, 0);
	lv_obj_set_flex_align(
	    selected_cont, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER
	);
	lv_obj_set_flex_flow(selected_cont, LV_FLEX_FLOW_COLUMN);

	selected_img = lv_img_create(selected_cont);
	lv_obj_set_size(selected_img, 168, 168);
	lv_obj_add_flag(selected_img, LV_OBJ_FLAG_HIDDEN);

	selected_label = lv_label_create(selected_cont);
	lv_label_set_text(selected_label, "No routine\nselected");
	lv_obj_add_style(selected_label, &style_text_centered, 0);
	lv_obj_add_style(selected_label, &style_text_medium, 0);

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
		lv_obj_t *save_icon = lv_label_create(view->obj);
		lv_obj_add_style(save_icon, &style_text_medium, 0);
		lv_obj_add_style(save_icon, &style_text_centered, 0);
		lv_label_set_text(save_icon, LV_SYMBOL_SD_CARD "\nSD");
		lv_obj_align(save_icon, LV_ALIGN_BOTTOM_MID, 16, -8);
	}

	// ----------------------------- Add autons ----------------------------- //

	for (routine_t routine : new_routines) {
		if (!routine.img.empty()) {
			routine.img.insert(0, "S:");
		}

		routines.push_back(routine);
	}

	for (routine_t &routine : routines) {
		lv_obj_t *new_btn = lv_list_add_btn(routine_list, NULL, routine.name.c_str());
		lv_obj_add_style(new_btn, &style_list_btn, 0);
		lv_obj_add_style(new_btn, &style_list_btn_pr, LV_STATE_PRESSED);
		lv_obj_set_user_data(new_btn, this);
		lv_obj_add_event_cb(new_btn, &select_cb, LV_EVENT_PRESSED, &routine);
	}

	if (pros::usd::is_installed()) sd_load();
}

// ============================= Other Methods ============================= //

void rd::Selector::run_callbacks() {
	for (select_action_t callback : this->select_callbacks) {
		callback(*this->selected_routine);
	}
}

void rd::Selector::run_auton() {
	if (selected_routine == nullptr) return; // If commanded to do nothing then return
	selected_routine->action();
}

std::optional<rd::Selector::routine_t> rd::Selector::get_auton() {
	if (selected_routine == nullptr) return std::nullopt;
	return *selected_routine;
}

void rd::Selector::on_select(rd::Selector::select_action_t callback) {
	select_callbacks.push_back(callback);
}

void rd::Selector::focus() { rd_view_focus(this->view); }