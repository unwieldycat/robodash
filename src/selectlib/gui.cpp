#include "gui.hpp"
#include "common/styles.hpp"
#include "dashboard.hpp"
#include "screensaver.hpp"
#include "styles.hpp"

#define INFO_BAR_WIDTH 32

lv_obj_t *window_cont;
lv_obj_t *info_bar;
lv_obj_t *window_list;
lv_obj_t *battery_label;
lv_obj_t *battery_icon;

// =========================== Window Management =========================== //

typedef struct Window {
	Window(int id, std::string name, lv_obj_t *obj) : id(id), name(name), obj(obj){};
	int id;
	std::string name;
	lv_obj_t *obj;
} window_t;

std::vector<Window> windows;

void repopulate_list() {
	lv_dropdown_clear_options(window_list);
	for (Window window : windows) {
		lv_dropdown_add_option(window_list, window.name.c_str(), window.id);
	}
}

void win_delete_cb(lv_event_t *event) {
	int *deleted_id = (int *)lv_event_get_user_data(event);
	(void)std::remove_if(windows.begin(), windows.end(), [&deleted_id](Window win) {
		return win.id == *deleted_id;
	});

	repopulate_list();
}

lv_obj_t *gui::create_window(std::string name) {
	static int window_id;
	window_id++;

	lv_obj_t *window_obj = lv_obj_create(window_cont);
	lv_obj_set_size(window_obj, lv_pct(100), lv_pct(100));

	Window window_meta(window_id, name, window_obj);
	lv_obj_add_event_cb(window_obj, &win_delete_cb, LV_EVENT_DELETE, &window_meta.id);
	windows.push_back(window_meta);

	repopulate_list();

	return window_obj;
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

		gui::dashboard::_refresh();
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

	gui::dashboard::_initialize();
	gui::screensaver::_initialize();

	pros::Task gui_task(background, "GUI Update Task");
}