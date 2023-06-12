#include "api.hpp"
#include "common/styles.hpp"

#define INFO_BAR_WIDTH 32

lv_obj_t *view_cont;
lv_obj_t *info_bar;
lv_obj_t *view_list;
lv_obj_t *battery_label;
lv_obj_t *battery_icon;
lv_obj_t *run_list;

std::map<int, gui::View *> views;
gui::View *current_view;

std::vector<gui::bar::action_t> actions;

void view_list_refresh();

// =========================== Base View Class =========================== //

int global_id = 0;

gui::View::View(std::string name) : name(name) {
	this->id = global_id;
	global_id++;

	this->obj = lv_obj_create(lv_scr_act());
	lv_obj_set_size(this->obj, lv_pct(100), lv_pct(100));
	lv_obj_add_flag(this->obj, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_style(this->obj, &style_bg, 0);
}

gui::View::~View() { lv_obj_del(this->obj); }

// =========================== View Management =========================== //

void gui::register_view(View *view) {
	lv_obj_set_parent(view->obj, view_cont);
	view->initialize();
	views.emplace(view->id, view);
	if (!current_view) gui::set_view(view);
	view_list_refresh();
}

void gui::set_view(View *view) {
	if (current_view) lv_obj_add_flag(current_view->obj, LV_OBJ_FLAG_HIDDEN);
	current_view = view;
	lv_obj_clear_flag(current_view->obj, LV_OBJ_FLAG_HIDDEN);
}

gui::View *gui::get_view() { return current_view; }

// ================================ Info Bar ================================ //

void view_list_refresh() {
	lv_dropdown_clear_options(view_list);

	for (auto const &[id, view] : views) {
		lv_dropdown_add_option(view_list, view->name.c_str(), view->id);
		if (id == current_view->id) lv_dropdown_set_selected(view_list, id);
	}
}

void view_list_select_cb(lv_event_t *event) {
	lv_obj_t *target = lv_event_get_target(event);
	lv_event_code_t code = lv_event_get_code(event);
	if (code != LV_EVENT_VALUE_CHANGED) return;

	int idx = lv_dropdown_get_selected(target);
	if (idx == current_view->id) return;

	gui::View *selected = views.at(idx);
	gui::set_view(selected);
}

void run_list_refresh() {
	lv_dropdown_clear_options(run_list);

	int idx = 0;
	for (gui::bar::action_t action : actions) {
		lv_dropdown_add_option(run_list, action.first.c_str(), idx);
		idx++;
	}
}

void run_list_select_cb(lv_event_t *event) {
	lv_obj_t *target = lv_event_get_current_target(event);
	lv_event_code_t code = lv_event_get_code(event);
	if (code != LV_EVENT_VALUE_CHANGED) return;

	int idx = lv_dropdown_get_selected(target);
	gui::bar::action_t selected = actions.at(idx);
	selected.second();
}

void gui::bar::add_action(std::string name, std::function<void()> action) {
	actions.push_back({name, action});
	if (!lv_obj_has_flag(run_list, LV_OBJ_FLAG_HIDDEN)) return;
	lv_obj_clear_flag(run_list, LV_OBJ_FLAG_HIDDEN);

	run_list_refresh();
}

void gui::bar::add_actions(std::vector<action_t> new_actions) {
	actions.insert(actions.end(), new_actions.begin(), new_actions.end());
	if (!lv_obj_has_flag(run_list, LV_OBJ_FLAG_HIDDEN)) return;
	lv_obj_clear_flag(run_list, LV_OBJ_FLAG_HIDDEN);

	run_list_refresh();
}

// ============================ Background Task ============================ //

[[noreturn]] void background() {
	while (true) {
		// Refresh battery level
		int level = pros::battery::get_capacity();
		char level_str[sizeof(level) + 1];
		sprintf(level_str, "%d%%", level);
		lv_label_set_text(battery_label, level_str);

		// yanderedev technique
		if (level >= 80) {
			lv_img_set_src(battery_icon, LV_SYMBOL_BATTERY_FULL);
		} else if (level < 80 && level >= 60) {
			lv_img_set_src(battery_icon, LV_SYMBOL_BATTERY_3);
		} else if (level < 60 && level >= 40) {
			lv_img_set_src(battery_icon, LV_SYMBOL_BATTERY_2);
		} else if (level < 40 && level >= 20) {
			lv_img_set_src(battery_icon, LV_SYMBOL_BATTERY_1);
		} else if (level < 20 && level >= 0) {
			lv_img_set_src(battery_icon, LV_SYMBOL_BATTERY_EMPTY);
		}

		for (auto const &[id, view] : views) {
			view->refresh();
		}

		gui::screensaver::_refresh();

		pros::delay(500);
	}
}

// =============================== Initialize =============================== //

void attribution() {
	std::string banner =
	    "\e[1;35m _  ___ __ _____ _  _ _     \n"
	    "| || \\ V  V /___| || | |                GUI powered by unwieldy-ui\n"
	    " \\_,_|\\_/\\_/     \\_,_|_|          \e[0mCopyright (C) Alex Y | Version %s\n";
	printf(banner.c_str(), UWUI_VERSION);
}

void gui::initialize() {
	attribution();
	gui::theme::_initialize();

	view_cont = lv_obj_create(lv_scr_act());
	lv_obj_set_size(view_cont, 480, 240 - INFO_BAR_WIDTH);
	lv_obj_add_style(view_cont, &style_bg, 0);

	info_bar = lv_obj_create(lv_scr_act());
	lv_obj_set_size(info_bar, 480, INFO_BAR_WIDTH);
	lv_obj_add_style(info_bar, &style_bar_bg, 0);
	lv_obj_align(info_bar, LV_ALIGN_BOTTOM_MID, 0, 0);

	view_list = lv_dropdown_create(info_bar);
	lv_dropdown_clear_options(view_list);
	lv_obj_set_size(view_list, 152, 32);
	lv_obj_align(view_list, LV_ALIGN_TOP_LEFT, 0, 0);
	lv_obj_add_style(view_list, &style_bar_button, 0);
	lv_obj_add_style(view_list, &style_bar_button_pr, LV_STATE_PRESSED);
	lv_dropdown_set_dir(view_list, LV_DIR_TOP);
	lv_obj_add_event_cb(view_list, &view_list_select_cb, LV_EVENT_ALL, NULL);

	lv_obj_add_event_cb(
	    view_list,
	    [](lv_event_t *event) {
		    lv_obj_t *list = lv_dropdown_get_list(view_list);
		    if (!list) return;
		    lv_obj_add_style(list, &style_bar_list, LV_PART_MAIN);
	    },
	    LV_EVENT_FOCUSED, NULL
	);

	run_list = lv_dropdown_create(info_bar);
	lv_dropdown_clear_options(run_list);
	lv_dropdown_set_text(run_list, "Run");
	lv_dropdown_set_symbol(run_list, LV_SYMBOL_CHARGE);
	lv_dropdown_set_selected_highlight(run_list, false);
	lv_dropdown_set_dir(run_list, LV_DIR_TOP);
	lv_obj_set_size(run_list, 64, 32);
	lv_obj_align(run_list, LV_ALIGN_TOP_LEFT, 152, 0);
	lv_obj_add_style(run_list, &style_bar_button, 0);
	lv_obj_add_style(run_list, &style_bar_button_pr, LV_STATE_PRESSED);
	lv_obj_add_flag(run_list, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_event_cb(run_list, &run_list_select_cb, LV_EVENT_ALL, NULL);

	lv_obj_add_event_cb(
	    run_list,
	    [](lv_event_t *event) {
		    lv_obj_t *list = lv_dropdown_get_list(run_list);
		    if (!list) return;
		    lv_obj_add_style(list, &style_bar_list, LV_PART_MAIN);
	    },
	    LV_EVENT_FOCUSED, NULL
	);

	lv_obj_t *batery_cont = lv_obj_create(info_bar);
	lv_obj_set_size(batery_cont, 96, 24);
	lv_obj_align(batery_cont, LV_ALIGN_TOP_RIGHT, -4, 4);
	lv_obj_add_style(batery_cont, &style_transp, 0);

	battery_label = lv_label_create(batery_cont);
	lv_label_set_text(battery_label, "100%");
	lv_obj_align(battery_label, LV_ALIGN_LEFT_MID, 12, 0);
	lv_obj_add_style(battery_label, &style_text_medium, 0);

	battery_icon = lv_img_create(batery_cont);
	lv_img_set_src(battery_icon, LV_SYMBOL_BATTERY_FULL);
	lv_obj_align(battery_icon, LV_ALIGN_RIGHT_MID, -12, 0);
	lv_obj_add_style(battery_icon, &style_text_medium, 0);

	gui::screensaver::_initialize();

	pros::Task gui_task(background, "GUI Update Task");
}