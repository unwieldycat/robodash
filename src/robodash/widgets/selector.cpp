#include "robodash/widgets/selector.hpp"
#include "api.h"
#include "robodash/detail/styles.h"
#include "robodash/util/kv_store.hpp"

const std::string file_path = "/usd/robodash/selector.txt";

// ============================== UI Callbacks ============================== //

void rd::Selector::select_cb(lv_event_t *event) {
	lv_obj_t *obj = lv_event_get_target(event);
	rd::Selector::routine_t *routine = (rd::Selector::routine_t *)lv_event_get_user_data(event);
	rd::Selector *selector = (rd::Selector *)lv_obj_get_user_data(obj);
	if (selector == nullptr) return;

	selector->selected_routine = routine;

	if (pros::usd::is_installed()) {
		rd::util::KVStore kv_store(file_path);
		kv_store.set(selector->name, selector->selected_routine->name);
	}

	if (routine == nullptr) {
		lv_label_set_text(selector->selected_label, "No routine\nselected");
		lv_obj_add_flag(selector->selected_img, LV_OBJ_FLAG_HIDDEN);
		return;
	}

	std::string label_str = "Selected routine:\n" + routine->name;
	lv_label_set_text(selector->selected_label, label_str.c_str());
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

rd::Selector::Selector(std::string name, std::vector<routine_t> new_routines) : view(name) {
	this->name = name;
	this->selected_routine = nullptr;

	// ----------------------------- Create UI ----------------------------- //

	lv_obj_set_style_bg_color(view, color_bg, 0);

	lv_obj_t *routine_list = lv_list_create(view);
	lv_obj_set_size(routine_list, 228, 192);
	lv_obj_align(routine_list, LV_ALIGN_TOP_LEFT, 8, 40);
	lv_obj_add_style(routine_list, &style_list, 0);

	lv_obj_t *selected_cont = lv_obj_create(view);
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

	lv_obj_t *title = lv_label_create(view);
	lv_label_set_text(title, "Select autonomous routine");
	lv_obj_add_style(title, &style_text_large, 0);
	lv_obj_align(title, LV_ALIGN_TOP_LEFT, 8, 12);

	if (pros::usd::is_installed()) {
		lv_obj_t *save_icon = lv_label_create(view);
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

	if (pros::usd::is_installed()) {
		rd::util::KVStore kv_store(file_path);
		std::optional<std::string> saved_name = kv_store.get<std::string>(name);
		if (!saved_name) return;

		for (rd::Selector::routine_t &r : routines) {
			if (r.name == saved_name.value()) selected_routine = &r;
		}

		if (selected_routine != nullptr) {
			// Update routine label
			std::string label_str = "Selected routine:\n" + saved_name.value();
			lv_label_set_text(selected_label, label_str.c_str());

			if (selected_routine->img.empty()) return;

			lv_img_set_src(this->selected_img, selected_routine->img.c_str());
			lv_obj_clear_flag(this->selected_img, LV_OBJ_FLAG_HIDDEN);
		}
	}
}

// ============================= Other Methods ============================= //

void rd::Selector::run_auton() {
	if (selected_routine == nullptr) return; // If commanded to do nothing then return
	selected_routine->action();
}

void rd::Selector::focus() { view.focus(); }
