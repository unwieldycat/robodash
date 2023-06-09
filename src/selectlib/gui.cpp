#include "gui.hpp"
#include "common/styles.hpp"
#include "dashboard.hpp"
#include "screensaver.hpp"
#include "styles.hpp"

#define INFO_BAR_WIDTH 32

// =========================== Window Management =========================== //

typedef struct Window {
	Window(int id, std::string name, lv_obj_t *obj) : id(id), name(name), obj(obj){};
	int id;
	std::string name;
	lv_obj_t *obj;
} window_t;

lv_obj_t *window_cont;
lv_obj_t *info_bar;

std::vector<Window> windows;

void win_delete_cb(lv_event_t *event) {
	int *deleted_id = (int *)lv_event_get_user_data(event);
	(void)std::remove_if(windows.begin(), windows.end(), [&deleted_id](Window win) {
		return win.id == *deleted_id;
	});
}

lv_obj_t *gui::create_window(std::string name) {
	static int window_id;
	window_id++;

	lv_obj_t *window_obj = lv_obj_create(window_cont);
	lv_obj_set_size(window_obj, lv_pct(100), lv_pct(100));

	Window window_meta(window_id, name, window_obj);
	lv_obj_add_event_cb(window_obj, &win_delete_cb, LV_EVENT_DELETE, &window_meta.id);
	windows.push_back(window_meta);

	return window_obj;
}

// ============================ Background Task ============================ //

[[noreturn]] void background() {
	while (true) {
		gui::dashboard::_refresh();
		gui::screensaver::_refresh();

		pros::delay(500);
	}
}

// =============================== Initialize =============================== //

void gui::initialize() {
	window_cont = lv_obj_create(NULL);
	lv_obj_set_size(window_cont, 480, 240 - INFO_BAR_WIDTH);
	lv_obj_add_style(window_cont, &style_transp, 0);

	info_bar = lv_obj_create(NULL);
	lv_obj_set_size(info_bar, 480, INFO_BAR_WIDTH);
	lv_obj_add_style(info_bar, &style_bg, 0);

	gui::theme::_initialize();
	gui::dashboard::_initialize();
	gui::screensaver::_initialize();

	pros::Task gui_task(background, "GUI Update Task");
}