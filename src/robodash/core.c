#include "apix.h"
#include <stdlib.h>

const int view_menu_width = 192;

// ============================== UI Elements ============================== //

lv_obj_t *screen;
lv_obj_t *view_cont;

lv_obj_t *view_menu;
lv_obj_t *view_list;
lv_obj_t *sidebar_modal;
lv_obj_t *alert_cont;
lv_obj_t *alert_btn;

lv_anim_t anim_sidebar_open;
lv_anim_t anim_sidebar_close;
lv_anim_t anim_modal_hide;
lv_anim_t anim_modal_show;

rd_view_t *current_view;

// ============================== UI Callbacks ============================== //

void view_focus_cb(lv_event_t *event) { rd_view_focus((rd_view_t *)lv_event_get_user_data(event)); }

void views_btn_cb(lv_event_t *event) {
	lv_obj_clear_flag(view_menu, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(sidebar_modal, LV_OBJ_FLAG_HIDDEN);
	lv_anim_start(&anim_sidebar_open);
	lv_anim_start(&anim_modal_show);
}

void close_cb(lv_event_t *event) {
	if (lv_obj_get_child_cnt(alert_cont) > 0) {
		lv_obj_clear_flag(alert_btn, LV_OBJ_FLAG_HIDDEN);
	}

	lv_obj_add_flag(alert_cont, LV_OBJ_FLAG_HIDDEN);
	lv_anim_start(&anim_sidebar_close);
	lv_anim_start(&anim_modal_hide);
}

void alert_btn_cb(lv_event_t *event) {
	if (!lv_obj_has_flag(alert_cont, LV_OBJ_FLAG_HIDDEN)) return;
	lv_obj_add_flag(alert_btn, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(alert_cont, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(sidebar_modal, LV_OBJ_FLAG_HIDDEN);
	lv_anim_start(&anim_modal_show);
}

void alert_cb(lv_event_t *event) {
	rd_view_t *view = (rd_view_t *)lv_event_get_user_data(event);
	rd_view_focus(view);

	lv_obj_t *alert = lv_event_get_target(event);
	lv_obj_del(alert);

	if (lv_obj_get_child_cnt(alert_cont) == 0) {
		lv_obj_add_flag(alert_cont, LV_OBJ_FLAG_HIDDEN);
		lv_anim_start(&anim_modal_hide);
	}
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

	lv_obj_t *views_open_btn = lv_btn_create(screen);
	lv_obj_set_size(views_open_btn, 32, 32);
	lv_obj_add_style(views_open_btn, &style_core_button, 0);
	lv_obj_add_style(views_open_btn, &style_core_button_pr, LV_STATE_PRESSED);
	lv_obj_align(views_open_btn, LV_ALIGN_TOP_RIGHT, -4, 4);
	lv_obj_add_event_cb(views_open_btn, views_btn_cb, LV_EVENT_PRESSED, NULL);

	lv_obj_t *open_img = lv_img_create(views_open_btn);
	lv_img_set_src(open_img, &stack);
	lv_obj_set_style_img_recolor(open_img, color_text, 0);
	lv_obj_set_style_img_recolor_opa(open_img, LV_OPA_COVER, 0);
	lv_obj_align(open_img, LV_ALIGN_CENTER, 0, 0);

	alert_btn = lv_btn_create(screen);
	lv_obj_set_size(alert_btn, 32, 32);
	lv_obj_add_style(alert_btn, &style_core_button, 0);
	lv_obj_add_style(alert_btn, &style_core_button_pr, LV_STATE_PRESSED);
	lv_obj_align(alert_btn, LV_ALIGN_TOP_RIGHT, -42, 4);
	lv_obj_add_event_cb(alert_btn, alert_btn_cb, LV_EVENT_PRESSED, NULL);
	lv_obj_add_flag(alert_btn, LV_OBJ_FLAG_HIDDEN);

	lv_obj_t *alert_img = lv_img_create(alert_btn);
	lv_img_set_src(alert_img, LV_SYMBOL_BELL);
	lv_obj_set_style_img_recolor(alert_img, color_text, 0);
	lv_obj_set_style_img_recolor_opa(alert_img, LV_OPA_COVER, 0);
	lv_obj_align(alert_img, LV_ALIGN_CENTER, 0, 0);

	// Modal
	sidebar_modal = lv_obj_create(screen);
	lv_obj_set_size(sidebar_modal, LV_PCT(100), LV_PCT(100));
	lv_obj_add_style(sidebar_modal, &style_core_modal, 0);
	lv_obj_add_flag(sidebar_modal, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_event_cb(sidebar_modal, close_cb, LV_EVENT_PRESSED, NULL);

	// Open sidebar
	view_menu = lv_obj_create(screen);
	lv_obj_set_size(view_menu, view_menu_width, 240);
	lv_obj_align(view_menu, LV_ALIGN_TOP_RIGHT, 0, 0);
	lv_obj_add_style(view_menu, &style_core_bg, 0);
	lv_obj_add_flag(view_menu, LV_OBJ_FLAG_HIDDEN);

	lv_obj_t *title = lv_label_create(view_menu);
	lv_label_set_text(title, "Select View");
	lv_obj_add_style(title, &style_text_large, 0);
	lv_obj_align(title, LV_ALIGN_TOP_LEFT, 12, 12);

	lv_obj_t *views_close_btn = lv_btn_create(view_menu);
	lv_obj_set_size(views_close_btn, 32, 32);
	lv_obj_add_style(views_close_btn, &style_transp, 0);
	lv_obj_add_style(views_close_btn, &style_transp, LV_STATE_PRESSED);
	lv_obj_align(views_close_btn, LV_ALIGN_TOP_RIGHT, -4, 4);
	lv_obj_add_event_cb(views_close_btn, close_cb, LV_EVENT_PRESSED, NULL);

	lv_obj_t *close_img = lv_img_create(views_close_btn);
	lv_img_set_src(close_img, LV_SYMBOL_CLOSE);
	lv_obj_align(close_img, LV_ALIGN_CENTER, 0, 0);

	// View switcher
	view_list = lv_list_create(view_menu);
	lv_obj_set_size(view_list, LV_PCT(100) - 8, LV_PCT(100) - 32);
	lv_obj_add_style(view_list, &style_core_list, 0);
	lv_obj_align(view_list, LV_ALIGN_TOP_LEFT, 4, 36);

	// Alert container
	alert_cont = lv_obj_create(screen);
	lv_obj_set_size(alert_cont, 320, LV_PCT(100));
	lv_obj_align(alert_cont, LV_ALIGN_CENTER, 0, 0);
	lv_obj_add_style(alert_cont, &style_transp, 0);
	lv_obj_clear_flag(alert_cont, LV_OBJ_FLAG_CLICKABLE);
	lv_obj_set_flex_align(
	    alert_cont, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START
	);
	lv_obj_set_flex_flow(alert_cont, LV_FLEX_FLOW_COLUMN);
}

void create_anims() {
	// Sidebar animations
	lv_anim_init(&anim_sidebar_open);
	lv_anim_set_var(&anim_sidebar_open, view_menu);
	lv_anim_set_time(&anim_sidebar_open, 200);
	lv_anim_set_exec_cb(&anim_sidebar_open, &anim_x_cb);

	anim_sidebar_close = anim_sidebar_open;

	lv_anim_set_path_cb(&anim_sidebar_open, &lv_anim_path_ease_out);
	lv_anim_set_values(&anim_sidebar_open, view_menu_width, 0);

	lv_anim_set_values(&anim_sidebar_close, 0, view_menu_width);
	lv_anim_set_deleted_cb(&anim_sidebar_close, &anim_del_cb);
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

// =============================== Initialize =============================== //

bool initialized = false;

void initialize() {
	if (initialized) return;

	_init_fs();
	_init_styles();

	create_ui();
	create_anims();

	initialized = true;
}

// =============================== View Class =============================== //

rd_view_t *rd_view_create(const char *name) {
	initialize();

	rd_view_t *view = (rd_view_t *)malloc(sizeof(rd_view_t));

	view->obj = lv_obj_create(lv_scr_act());
	lv_obj_set_size(view->obj, lv_pct(100), lv_pct(100));
	lv_obj_add_flag(view->obj, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_style(view->obj, &style_bg, 0);

	lv_obj_set_parent(view->obj, view_cont);
	if (!current_view) rd_view_focus(view);

	view->_btn = lv_list_add_btn(view_list, NULL, name);
	lv_obj_add_style(view->_btn, &style_core_list_btn, 0);
	lv_obj_add_style(view->_btn, &style_list_btn_pr, LV_STATE_PRESSED);
	lv_obj_add_event_cb(view->_btn, view_focus_cb, LV_EVENT_PRESSED, view);
	lv_obj_add_event_cb(view->_btn, close_cb, LV_EVENT_PRESSED, NULL);

	view->name = name;

	return view;
}

void rd_view_del(rd_view_t *view) {
	lv_obj_del(view->_btn);
	lv_obj_del(view->obj);
	if (current_view == view) current_view = NULL;
	free(view);
}

lv_obj_t *rd_view_obj(rd_view_t *view) { return view->obj; }

void rd_view_focus(rd_view_t *view) {
	if (view == NULL) return;
	if (current_view != NULL) lv_obj_add_flag(current_view->obj, LV_OBJ_FLAG_HIDDEN);
	current_view = view;
	lv_obj_clear_flag(current_view->obj, LV_OBJ_FLAG_HIDDEN);
}

void rd_view_alert(rd_view_t *view, const char *msg) {
	if (!lv_obj_has_flag(view_menu, LV_OBJ_FLAG_HIDDEN)) {
		lv_anim_start(&anim_sidebar_close);
	}

	if (lv_obj_has_flag(sidebar_modal, LV_OBJ_FLAG_HIDDEN)) {
		lv_obj_clear_flag(sidebar_modal, LV_OBJ_FLAG_HIDDEN);
		lv_anim_start(&anim_modal_show);
	}

	lv_obj_clear_flag(alert_cont, LV_OBJ_FLAG_HIDDEN);

	lv_obj_t *alert = lv_obj_create(alert_cont);
	lv_obj_set_width(alert, LV_PCT(100));
	lv_obj_set_height(alert, LV_SIZE_CONTENT);
	lv_obj_add_event_cb(alert, alert_cb, LV_EVENT_CLICKED, view);
	lv_obj_add_style(alert, &style_alert, 0);

	lv_obj_t *origin_label = lv_label_create(alert);
	lv_obj_align(origin_label, LV_ALIGN_TOP_LEFT, 0, 0);
	lv_obj_add_style(origin_label, &style_text_small, 0);
	lv_label_set_text(origin_label, view->name);

	lv_obj_t *alert_msg = lv_label_create(alert);
	lv_obj_align(alert_msg, LV_ALIGN_TOP_LEFT, 0, 18);
	lv_obj_set_width(alert_msg, LV_PCT(100));
	lv_obj_add_style(alert_msg, &style_text_medium, 0);
	lv_label_set_long_mode(alert_msg, LV_LABEL_LONG_WRAP);
	lv_label_set_text(alert_msg, msg);
}