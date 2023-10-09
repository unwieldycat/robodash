#include "gui.hpp"
#include "apix.hpp"

#define CLOSED_SIDEBAR_WIDTH 32
#define OPEN_SIDEBAR_WIDTH 128

lv_obj_t *view_cont;

lv_obj_t *sidebar_closed;
lv_obj_t *sidebar_open_btn;

lv_obj_t *sidebar_open;
lv_obj_t *sidebar_close_btn;

lv_obj_t *view_list;

std::map<int, gui::View *> views;
gui::View *current_view;

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

void view_btn_cb(lv_event_t *event) { gui::set_view((gui::View *)lv_event_get_user_data(event)); }

void gui::register_view(View *view) {
	lv_obj_set_parent(view->obj, view_cont);
	view->initialize();
	views.emplace(view->id, view);
	if (!current_view) gui::set_view(view);

	lv_obj_t *view_button = lv_list_add_btn(view_list, NULL, view->name.c_str());
	lv_obj_add_style(view_button, &style_list_btn, 0);
	lv_obj_add_style(view_button, &style_list_btn_pr, LV_STATE_PRESSED);
	lv_obj_add_event_cb(view_button, view_btn_cb, LV_EVENT_PRESSED, view);
}

void gui::register_views(std::vector<View *> views) {
	for (View *view : views) {
		gui::register_view(view);
	}
}

void gui::set_view(View *view) {
	if (current_view) lv_obj_add_flag(current_view->obj, LV_OBJ_FLAG_HIDDEN);
	current_view = view;
	lv_obj_clear_flag(current_view->obj, LV_OBJ_FLAG_HIDDEN);
}

gui::View *gui::get_view() { return current_view; }

// ================================ Sidebar ================================ //

// TODO: Sidebar animation?

void open_sidebar(lv_event_t *event) { lv_obj_clear_flag(sidebar_open, LV_OBJ_FLAG_HIDDEN); }

void hide_sidebar(lv_event_t *event) { lv_obj_add_flag(sidebar_open, LV_OBJ_FLAG_HIDDEN); }

// ============================ Background Task ============================ //

[[noreturn]] void background() {
	while (true) {
		for (auto const &[id, view] : views) {
			view->refresh();
		}

		gui::screensaver::_refresh();

		pros::delay(500);
	}
}

// =============================== Initialize =============================== //

void attribution() {
	std::string banner = "\e[1;35m        _ \n"
	                     " _ _ __| |\n"
	                     "| '_/ _` |		GUI powered by robodash\n"
	                     "|_| \\__,_|	  \e[0mCopyright (C) Alex Y | Version %s\n";
	printf(banner.c_str(), RD_VERSION);
}

void gui::initialize() {
	attribution();
	gui::theme::_initialize();

	// View container
	view_cont = lv_obj_create(lv_scr_act());
	lv_obj_set_size(view_cont, 480 - CLOSED_SIDEBAR_WIDTH, LV_PCT(100));
	lv_obj_add_style(view_cont, &style_bg, 0);
	lv_obj_align(view_cont, LV_ALIGN_TOP_LEFT, 0, 0);

	// Sidebar
	sidebar_closed = lv_obj_create(lv_scr_act());
	lv_obj_set_size(sidebar_closed, 480 - CLOSED_SIDEBAR_WIDTH, LV_PCT(100));
	lv_obj_add_style(sidebar_closed, &style_bar_bg, 0);
	lv_obj_align(sidebar_closed, LV_ALIGN_TOP_RIGHT, 0, 0);

	sidebar_open_btn = lv_btn_create(sidebar_closed);
	lv_obj_set_size(sidebar_open_btn, 24, 24);
	lv_obj_add_style(sidebar_open_btn, &style_btn_outline, 0);
	lv_obj_add_style(sidebar_open_btn, &style_btn_outline_pr, LV_STATE_PRESSED);
	lv_obj_align(sidebar_open_btn, LV_ALIGN_TOP_LEFT, 4, 4);
	lv_obj_add_event_cb(sidebar_open_btn, open_sidebar, LV_EVENT_PRESSED, NULL);

	lv_obj_t *open_img = lv_img_create(sidebar_close_btn);
	lv_img_set_src(open_img, LV_SYMBOL_BARS);
	lv_obj_align(open_img, LV_ALIGN_CENTER, 0, 0);

	// Open sidebar
	sidebar_open = lv_obj_create(view_cont);
	lv_obj_set_size(view_cont, OPEN_SIDEBAR_WIDTH, LV_PCT(100));
	lv_obj_align(sidebar_open, LV_ALIGN_TOP_RIGHT, 0, 0);
	lv_obj_add_style(sidebar_open, &style_bar_bg, 0);
	lv_obj_add_flag(sidebar_open, LV_OBJ_FLAG_HIDDEN);

	sidebar_close_btn = lv_btn_create(sidebar_open);
	lv_obj_set_size(sidebar_close_btn, 24, 24);
	lv_obj_add_style(sidebar_close_btn, &style_btn_outline, 0);
	lv_obj_add_style(sidebar_close_btn, &style_btn_outline_pr, LV_STATE_PRESSED);
	lv_obj_align(sidebar_close_btn, LV_ALIGN_TOP_LEFT, 4, 4);

	lv_obj_t *close_img = lv_img_create(sidebar_close_btn);
	lv_img_set_src(close_img, LV_SYMBOL_CLOSE);
	lv_obj_align(close_img, LV_ALIGN_CENTER, 0, 0);

	// View switcher
	view_list = lv_list_create(sidebar_open);
	lv_obj_set_size(view_list, LV_PCT(100) - 8, LV_PCT(100) - 32);
	lv_obj_add_style(view_list, &style_list, 0);
	lv_obj_align(view_list, LV_ALIGN_TOP_LEFT, 4, 28);

	gui::screensaver::_initialize();

	pros::Task gui_task(background, "GUI Update Task");
}