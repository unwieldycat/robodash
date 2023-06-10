#include "gui.hpp"
#include "common/styles.hpp"

#define INFO_BAR_WIDTH 32

lv_obj_t *window_cont;
lv_obj_t *info_bar;
lv_obj_t *window_list;
lv_obj_t *battery_label;
lv_obj_t *battery_icon;

std::map<int, gui::Window *> windows;
gui::Window *current_window;

void list_refresh();

// =========================== Base Window Class =========================== //

gui::Window::Window(std::string name) : name(name) {
	this->obj = lv_obj_create(window_cont);
	lv_obj_set_size(this->obj, lv_pct(100), lv_pct(100));
	lv_obj_add_flag(this->obj, LV_OBJ_FLAG_HIDDEN);
	windows.emplace(this->id, this);
	list_refresh();
}

gui::Window::~Window() { lv_obj_del(this->obj); }

// =========================== Window Management =========================== //

void gui::set_window(Window *window) {
	lv_obj_add_flag(current_window->obj, LV_OBJ_FLAG_HIDDEN);
	current_window = window;
	lv_obj_clear_flag(current_window->obj, LV_OBJ_FLAG_HIDDEN);
}

gui::Window *gui::get_window() { return current_window; }

// ================================ Info Bar ================================ //

void list_refresh() {
	lv_dropdown_clear_options(window_list);

	for (auto const &[id, window] : windows) {
		lv_dropdown_add_option(window_list, window->name.c_str(), window->id);
		if (id == current_window->id) lv_dropdown_set_selected(window_list, id);
	}
}

void list_select_cb(lv_event_t *event) {
	lv_obj_t *target = lv_event_get_target(event);
	int idx = lv_dropdown_get_selected(target);
	if (idx == current_window->id) return;

	gui::Window *selected = windows.at(idx);
	gui::set_window(selected);
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

		for (auto const &[id, window] : windows) {
			window->refresh();
		}

		gui::screensaver::_refresh();

		pros::delay(500);
	}
}

// =============================== Initialize =============================== //

void gui::initialize() {
	gui::theme::_initialize();

	window_cont = lv_obj_create(lv_scr_act());
	lv_obj_set_size(window_cont, 480, 240 - INFO_BAR_WIDTH);
	lv_obj_add_style(window_cont, &style_bg, 0);

	info_bar = lv_obj_create(lv_scr_act());
	lv_obj_set_size(info_bar, 480, INFO_BAR_WIDTH);
	lv_obj_add_style(info_bar, &style_bar_bg, 0);
	lv_obj_align(info_bar, LV_ALIGN_BOTTOM_MID, 0, 0);

	window_list = lv_dropdown_create(info_bar);
	lv_dropdown_clear_options(window_list);
	lv_obj_set_size(window_list, 152, 32);
	lv_obj_align(window_list, LV_ALIGN_TOP_LEFT, 0, 0);
	lv_obj_add_style(window_list, &style_bar_button, 0);
	lv_obj_add_style(window_list, &style_bar_button_pr, LV_STATE_PRESSED);
	lv_dropdown_set_dir(window_list, LV_DIR_TOP);
	lv_obj_add_event_cb(window_list, &list_select_cb, LV_EVENT_VALUE_CHANGED, NULL);

	lv_obj_add_event_cb(
	    window_list,
	    [](lv_event_t *event) {
		    lv_obj_t *list = lv_dropdown_get_list(window_list);
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

	for (auto const &[id, window] : windows) {
		window->initialize();
	}

	pros::Task gui_task(background, "GUI Update Task");
}