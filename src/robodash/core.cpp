#include "core.hpp"
#include "apix.hpp"
#include <map>
#include <vector>

#define CLOSED_SIDEBAR_WIDTH 40
#define OPEN_SIDEBAR_WIDTH 192

bool initialized = false;

// ============================== UI Elements ============================== //

lv_obj_t *screen;
lv_obj_t *view_cont;

lv_obj_t *sidebar_open_btn;

lv_obj_t *sidebar_open;
lv_obj_t *sidebar_close_btn;
lv_obj_t *view_list;
lv_obj_t *sidebar_modal;

lv_anim_t anim_sidebar_open;
lv_anim_t anim_sidebar_close;
lv_anim_t anim_modal_hide;
lv_anim_t anim_modal_show;

rd::View *current_view;

// ============================== UI Callbacks ============================== //

void view_btn_cb(lv_event_t *event) { ((rd::View *)lv_event_get_user_data(event))->focus(); }

void open_sidebar(lv_event_t *event) {
	lv_obj_clear_flag(sidebar_open, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(sidebar_modal, LV_OBJ_FLAG_HIDDEN);
	lv_anim_start(&anim_sidebar_open);
	lv_anim_start(&anim_modal_show);
}

void close_sidebar(lv_event_t *event) {
	lv_anim_start(&anim_sidebar_close);
	lv_anim_start(&anim_modal_hide);
}

// =========================== UI Initialization =========================== //

void create_ui() {
	screen = lv_scr_act();
	lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE);

	// View container
	view_cont = lv_obj_create(screen);
	lv_obj_set_size(view_cont, 480, 240);
	lv_obj_add_style(view_cont, &style_bg, 0);
	lv_obj_align(view_cont, LV_ALIGN_TOP_LEFT, 0, 0);

	sidebar_open_btn = lv_btn_create(screen);
	lv_obj_set_size(sidebar_open_btn, 32, 32);
	lv_obj_add_style(sidebar_open_btn, &style_bar_button, 0);
	lv_obj_add_style(sidebar_open_btn, &style_bar_button_pr, LV_STATE_PRESSED);
	lv_obj_align(sidebar_open_btn, LV_ALIGN_TOP_RIGHT, -4, 4);
	lv_obj_add_event_cb(sidebar_open_btn, open_sidebar, LV_EVENT_PRESSED, NULL);

	lv_obj_t *open_img = lv_img_create(sidebar_open_btn);
	lv_img_set_src(open_img, &stack);
	lv_obj_set_style_img_recolor(open_img, color_text, 0);
	lv_obj_set_style_img_recolor_opa(open_img, LV_OPA_COVER, 0);
	lv_obj_align(open_img, LV_ALIGN_CENTER, 0, 0);

	// Modal
	sidebar_modal = lv_obj_create(screen);
	lv_obj_set_size(sidebar_modal, LV_PCT(100), LV_PCT(100));
	lv_obj_add_style(sidebar_modal, &style_bar_modal, 0);
	lv_obj_add_flag(sidebar_modal, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_event_cb(sidebar_modal, close_sidebar, LV_EVENT_PRESSED, NULL);

	// Open sidebar
	sidebar_open = lv_obj_create(screen);
	lv_obj_set_size(sidebar_open, OPEN_SIDEBAR_WIDTH, 240);
	lv_obj_align(sidebar_open, LV_ALIGN_TOP_RIGHT, 0, 0);
	lv_obj_add_style(sidebar_open, &style_bar_bg, 0);
	lv_obj_add_flag(sidebar_open, LV_OBJ_FLAG_HIDDEN);

	lv_obj_t *title = lv_label_create(sidebar_open);
	lv_label_set_text(title, "Select View");
	lv_obj_add_style(title, &style_text_large, 0);
	lv_obj_align(title, LV_ALIGN_TOP_LEFT, 12, 12);

	sidebar_close_btn = lv_btn_create(sidebar_open);
	lv_obj_set_size(sidebar_close_btn, 32, 32);
	lv_obj_add_style(sidebar_close_btn, &style_transp, 0);
	lv_obj_add_style(sidebar_close_btn, &style_transp, LV_STATE_PRESSED);
	lv_obj_align(sidebar_close_btn, LV_ALIGN_TOP_RIGHT, -4, 4);
	lv_obj_add_event_cb(sidebar_close_btn, close_sidebar, LV_EVENT_PRESSED, NULL);

	lv_obj_t *close_img = lv_img_create(sidebar_close_btn);
	lv_img_set_src(close_img, LV_SYMBOL_CLOSE);
	lv_obj_align(close_img, LV_ALIGN_CENTER, 0, 0);

	// View switcher
	view_list = lv_list_create(sidebar_open);
	lv_obj_set_size(view_list, LV_PCT(100) - 8, LV_PCT(100) - 32);
	lv_obj_add_style(view_list, &style_bar_list, 0);
	lv_obj_align(view_list, LV_ALIGN_TOP_LEFT, 4, 36);
}

void create_anims() {
	// Sidebar animations
	lv_anim_init(&anim_sidebar_open);
	lv_anim_set_var(&anim_sidebar_open, sidebar_open);
	lv_anim_set_time(&anim_sidebar_open, 200);
	lv_anim_set_exec_cb(&anim_sidebar_open, &anim_x_cb);

	anim_sidebar_close = anim_sidebar_open;

	lv_anim_set_path_cb(&anim_sidebar_open, &lv_anim_path_ease_out);
	lv_anim_set_values(&anim_sidebar_open, OPEN_SIDEBAR_WIDTH, 0);

	lv_anim_set_values(&anim_sidebar_close, 0, OPEN_SIDEBAR_WIDTH);
	lv_anim_set_path_cb(&anim_sidebar_close, &lv_anim_path_ease_out);

	// Modal animations
	lv_anim_init(&anim_modal_hide);
	lv_anim_set_var(&anim_modal_hide, sidebar_modal);
	lv_anim_set_time(&anim_modal_hide, 200);
	lv_anim_set_exec_cb(&anim_modal_hide, &anim_opa_cb);

	anim_modal_show = anim_modal_hide;

	lv_anim_set_values(&anim_modal_hide, 144, 0);
	lv_anim_set_deleted_cb(&anim_modal_hide, &anim_del_cb);
	lv_anim_set_values(&anim_modal_show, 0, 144);
}

// =============================== View Class =============================== //

rd::View::View(std::string name) : name(name) {
	rd::initialize();

	this->obj = lv_obj_create(lv_scr_act());
	lv_obj_set_size(this->obj, lv_pct(100), lv_pct(100));
	lv_obj_add_flag(this->obj, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_style(this->obj, &style_bg, 0);

	lv_obj_set_parent(this->get_obj(), view_cont);
	if (!current_view) this->focus();

	lv_obj_t *view_button = lv_list_add_btn(view_list, NULL, name.c_str());
	lv_obj_add_style(view_button, &style_bar_list_btn, 0);
	lv_obj_add_style(view_button, &style_list_btn_pr, LV_STATE_PRESSED);
	lv_obj_add_event_cb(view_button, view_btn_cb, LV_EVENT_PRESSED, this);
	lv_obj_add_event_cb(view_button, close_sidebar, LV_EVENT_PRESSED, NULL);
}

rd::View::~View() { lv_obj_del(this->obj); }

std::string rd::View::get_name() { return this->name; }

lv_obj_t *rd::View::get_obj() { return this->obj; }

void rd::View::focus() {
	if (current_view) lv_obj_add_flag(current_view->get_obj(), LV_OBJ_FLAG_HIDDEN);
	current_view = this;
	lv_obj_clear_flag(current_view->get_obj(), LV_OBJ_FLAG_HIDDEN);
}

// =============================== Initialize =============================== //

void rd::initialize() {
	if (initialized) return;

	_init_fs();
	_init_styles();

	create_ui();
	create_anims();

	initialized = true;
}