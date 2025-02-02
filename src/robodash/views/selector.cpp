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
		return;
	}

	// Press button for selected auton
	for (int id = 0; id < lv_obj_get_child_cnt(routine_list); id++) {
		lv_obj_t *list_child = lv_obj_get_child(routine_list, id);
		if (list_child == nullptr) continue;
		if (strcmp(lv_list_get_btn_text(routine_list, list_child), saved_name) != 0) continue;
		lv_event_send(list_child, LV_EVENT_CLICKED, selected_routine);
		break;
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

	// Clear other checked buttons, make this auton's button the checked one
	for (int id = 0; id < lv_obj_get_child_cnt(selector->routine_list); id++) {
		lv_obj_t *list_child = lv_obj_get_child(selector->routine_list, id);
		lv_obj_clear_state(list_child, LV_STATE_CHECKED);
	}
	lv_obj_add_state(obj, LV_STATE_CHECKED);

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

void rd::Selector::pg_up_cb(lv_event_t *event) {
	rd::Selector *selector = (rd::Selector *)lv_obj_get_user_data(lv_event_get_target(event));
	lv_coord_t scroll_y = lv_obj_get_height(selector->routine_list);
	lv_obj_scroll_by_bounded(selector->routine_list, 0, scroll_y, LV_ANIM_ON);
}

void rd::Selector::pg_down_cb(lv_event_t *event) {
	rd::Selector *selector = (rd::Selector *)lv_obj_get_user_data(lv_event_get_target(event));
	lv_coord_t scroll_y = lv_obj_get_height(selector->routine_list) * -1;
	lv_obj_scroll_by_bounded(selector->routine_list, 0, scroll_y, LV_ANIM_ON);
}

void rd::Selector::up_cb(lv_event_t *event) {
	rd::Selector *selector = (rd::Selector *)lv_obj_get_user_data(lv_event_get_target(event));
	if (!selector) return;
	selector->prev_auton();
}

void rd::Selector::down_cb(lv_event_t *event) {
	rd::Selector *selector = (rd::Selector *)lv_obj_get_user_data(lv_event_get_target(event));
	if (!selector) return;
	selector->next_auton();
}

// ============================== Constructor ============================== //

rd::Selector::Selector(std::vector<routine_t> autons) : Selector("Auton Selector", autons) {}

rd::Selector::Selector(std::string name, std::vector<routine_t> new_routines) {
	this->name = name;
	this->selected_routine = nullptr;

	// ----------------------------- Create UI ----------------------------- //

	this->view = rd_view_create(name.c_str());

	lv_obj_set_style_bg_color(view->obj, color_bg, 0);

	routine_list = lv_list_create(view->obj);
	lv_obj_set_size(routine_list, 228, 192);
	lv_obj_align(routine_list, LV_ALIGN_TOP_LEFT, 8, 40);
	lv_obj_add_style(routine_list, &style_list, 0);

	selected_cont = lv_obj_create(view->obj);
	lv_obj_add_style(selected_cont, &style_transp, 0);
	lv_obj_set_layout(selected_cont, LV_LAYOUT_FLEX);
	lv_obj_set_size(selected_cont, 240, 240);
	lv_obj_align(selected_cont, LV_ALIGN_CENTER, 120, 0);
	lv_obj_set_flex_align(
	    selected_cont, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER
	);
	lv_obj_set_flex_flow(selected_cont, LV_FLEX_FLOW_COLUMN);

	selected_label = lv_label_create(selected_cont);
	lv_label_set_text(selected_label, "No routine\nselected");
	lv_obj_add_style(selected_label, &style_text_centered, 0);
	lv_obj_add_style(selected_label, &style_text_medium, 0);

	selected_img = lv_img_create(selected_cont);
	lv_obj_set_size(selected_img, 168, 168);
	lv_obj_add_flag(selected_img, LV_OBJ_FLAG_HIDDEN);

	// Routine list button cluster
	lv_obj_t *list_btns = lv_obj_create(view->obj);
	lv_obj_add_style(list_btns, &style_transp, 0);
	lv_obj_set_size(list_btns, 32, 192);
	lv_obj_align(list_btns, LV_ALIGN_TOP_LEFT, 236, 40);
	lv_obj_clear_flag(list_btns, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_layout(list_btns, LV_LAYOUT_FLEX);
	lv_obj_set_flex_flow(list_btns, LV_FLEX_FLOW_COLUMN);
	lv_obj_set_flex_align(
	    list_btns, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER
	);

	// Up page button
	lv_obj_t *pg_up_btn = lv_btn_create(list_btns);
	lv_obj_add_style(pg_up_btn, &style_transp, 0);
	lv_obj_set_size(pg_up_btn, 32, 32);
	lv_obj_add_event_cb(pg_up_btn, &pg_up_cb, LV_EVENT_CLICKED, NULL);
	lv_obj_set_user_data(pg_up_btn, this);
	lv_obj_add_flag(pg_up_btn, LV_OBJ_FLAG_HIDDEN);
	lv_obj_set_style_text_opa(pg_up_btn, 128, LV_STATE_PRESSED);
	lv_obj_set_flex_grow(pg_up_btn, 1);

	lv_obj_t *pg_up_img = lv_img_create(pg_up_btn);
	lv_obj_align(pg_up_img, LV_ALIGN_CENTER, 0, 0);
	lv_img_set_src(pg_up_img, LV_SYMBOL_UP "\n" LV_SYMBOL_UP);
	lv_obj_set_style_text_line_space(pg_up_img, -10, LV_PART_MAIN);

	// Up button
	lv_obj_t *up_btn = lv_btn_create(list_btns);
	lv_obj_add_style(up_btn, &style_transp, 0);
	lv_obj_set_size(up_btn, 32, 32);
	lv_obj_add_event_cb(up_btn, &up_cb, LV_EVENT_CLICKED, NULL);
	lv_obj_set_user_data(up_btn, this);
	lv_obj_set_style_text_opa(up_btn, 128, LV_STATE_PRESSED);
	lv_obj_set_flex_grow(up_btn, 1);

	lv_obj_t *up_img = lv_img_create(up_btn);
	lv_obj_align(up_img, LV_ALIGN_CENTER, 0, 0);
	lv_img_set_src(up_img, LV_SYMBOL_UP);

	// Down button
	lv_obj_t *down_btn = lv_btn_create(list_btns);
	lv_obj_add_style(down_btn, &style_transp, 0);
	lv_obj_set_size(down_btn, 32, 32);
	lv_obj_add_event_cb(down_btn, &down_cb, LV_EVENT_CLICKED, NULL);
	lv_obj_set_user_data(down_btn, this);
	lv_obj_set_style_text_opa(down_btn, 128, LV_STATE_PRESSED);
	lv_obj_set_flex_grow(down_btn, 1);

	lv_obj_t *down_img = lv_img_create(down_btn);
	lv_obj_align(down_img, LV_ALIGN_CENTER, 0, 0);
	lv_img_set_src(down_img, LV_SYMBOL_DOWN);

	// Down page button
	lv_obj_t *pg_down_btn = lv_btn_create(list_btns);
	lv_obj_add_style(pg_down_btn, &style_transp, 0);
	lv_obj_set_size(pg_down_btn, 32, 32);
	lv_obj_add_event_cb(pg_down_btn, &pg_down_cb, LV_EVENT_CLICKED, NULL);
	lv_obj_set_user_data(pg_down_btn, this);
	lv_obj_add_flag(pg_down_btn, LV_OBJ_FLAG_HIDDEN);
	lv_obj_set_style_text_opa(pg_down_btn, 128, LV_STATE_PRESSED);
	lv_obj_set_flex_grow(pg_down_btn, 1);

	lv_obj_t *pg_down_img = lv_img_create(pg_down_btn);
	lv_obj_align(pg_down_img, LV_ALIGN_CENTER, 0, 0);
	lv_img_set_src(pg_down_img, LV_SYMBOL_DOWN "\n" LV_SYMBOL_DOWN);
	lv_obj_set_style_text_line_space(pg_down_img, -10, LV_PART_MAIN);

	// Nothing auton
	lv_obj_t *nothing_btn = lv_list_add_btn(routine_list, NULL, "Nothing");
	lv_obj_add_event_cb(nothing_btn, &select_cb, LV_EVENT_CLICKED, nullptr);
	lv_obj_set_user_data(nothing_btn, this);
	lv_obj_add_style(nothing_btn, &style_list_btn, 0);
	lv_obj_add_style(nothing_btn, &style_list_btn_pr, LV_STATE_PRESSED);
	lv_obj_add_style(nothing_btn, &style_list_btn_ch, LV_STATE_CHECKED);
	lv_obj_set_style_transform_width(nothing_btn, -8, 0);
	lv_obj_add_state(nothing_btn, LV_STATE_CHECKED);

	lv_obj_t *title = lv_label_create(view->obj);
	lv_label_set_text(title, "Select autonomous routine");
	lv_obj_add_style(title, &style_text_large, 0);
	lv_obj_align(title, LV_ALIGN_TOP_LEFT, 8, 12);

	if (pros::usd::is_installed()) {
		lv_obj_t *save_icon = lv_label_create(list_btns);
		lv_obj_add_style(save_icon, &style_text_medium, 0);
		lv_obj_add_style(save_icon, &style_text_centered, 0);
		lv_label_set_text(save_icon, LV_SYMBOL_SD_CARD "\nSD");
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
		lv_obj_add_style(new_btn, &style_list_btn_ch, LV_STATE_CHECKED);
		lv_obj_set_style_transform_width(new_btn, -8, 0);
		lv_obj_set_user_data(new_btn, this);
		lv_obj_add_event_cb(new_btn, &select_cb, LV_EVENT_CLICKED, &routine);

		if (routine.color_hue > -1) {
			lv_obj_t *color_chip = lv_obj_create(new_btn);
			lv_obj_set_size(color_chip, 16, 16);
			lv_obj_set_style_bg_color(
			    color_chip, lv_color_hsv_to_rgb(routine.color_hue, 75, 80), 0
			);
			lv_obj_set_style_border_opa(color_chip, LV_OPA_0, 0);
			lv_obj_set_style_radius(color_chip, 4, 0);
			lv_obj_align(color_chip, LV_ALIGN_RIGHT_MID, -4, 8);
			lv_obj_clear_flag(color_chip, LV_OBJ_FLAG_SCROLLABLE);
			lv_obj_clear_flag(color_chip, LV_OBJ_FLAG_CLICKABLE);
		}
	}

	if (routines.size() > 3) {
		lv_obj_clear_flag(pg_down_btn, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(pg_up_btn, LV_OBJ_FLAG_HIDDEN);
	}

	if (pros::usd::is_installed()) sd_load();
}

// ============================= Other Methods ============================= //

void rd::Selector::next_auton(bool wrap_around) {
	for (int id = 0; id < lv_obj_get_child_cnt(routine_list); id++) {
		lv_obj_t *list_child = lv_obj_get_child(routine_list, id);
		if (!lv_obj_has_state(list_child, LV_STATE_CHECKED)) continue;

		if (id == lv_obj_get_child_cnt(routine_list) - 1) {
			if (!wrap_around) return;
			// nullptr because the "Nothing" button is always first, and doesnt have user data
			lv_event_send(lv_obj_get_child(routine_list, 0), LV_EVENT_CLICKED, nullptr);
		} else {
			lv_obj_t *next_child = lv_obj_get_child(routine_list, id + 1);
			if (next_child == nullptr) return;
			lv_event_send(next_child, LV_EVENT_CLICKED, &routines[id + 1]);
		}

		return;
	}
}

void rd::Selector::prev_auton(bool wrap_around) {
	lv_obj_t *prev_child = nullptr;
	int child_count = lv_obj_get_child_cnt(routine_list);
	for (int id = 0; id < child_count; id++) {
		lv_obj_t *list_child = lv_obj_get_child(routine_list, id);
		if (!lv_obj_has_state(list_child, LV_STATE_CHECKED)) {
			prev_child = list_child;
			continue;
		};

		if (id == 0) {
			if (!wrap_around) return;
			lv_event_send(
			    lv_obj_get_child(routine_list, child_count - 1), LV_EVENT_CLICKED,
			    &routines[child_count - 1]
			);
		} else {
			if (prev_child == nullptr) return;
			lv_event_send(prev_child, LV_EVENT_CLICKED, &routines[id - 1]);
		}

		return;
	}
}

void rd::Selector::run_callbacks() {
	for (select_action_t callback : this->select_callbacks) {
		if (this->selected_routine == nullptr) {
			callback(std::nullopt);
		} else {
			callback(*this->selected_routine);
		}
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