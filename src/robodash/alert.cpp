#include "alert.hpp"
#include "robodash/detail/gui.hpp"
#include "robodash/detail/styles.h"
#include "robodash/view.hpp"

void alert_cb(lv_event_t *event) {
	rd::View *view = (rd::View *)lv_event_get_user_data(event);
	if (!valid_view(view)) return;
	view->focus();

	lv_obj_t *alert = lv_event_get_target(event);
	lv_obj_del(alert);

	if (lv_obj_get_child_cnt(alert_cont) == 0) {
		lv_obj_add_flag(alert_cont, LV_OBJ_FLAG_HIDDEN);

		if (current_view->has_flag(rd::ViewFlag::NoAnimation)) {
			lv_obj_add_flag(shade, LV_OBJ_FLAG_HIDDEN);
		} else {
			lv_anim_start(&anim_shade_hide);
		}
	}
}

void rd::alert(std::string message) {
	// TODO: Implement
}

void rd::alert(std::string message, rd::View &view) {
	if (!lv_obj_has_flag(view_menu, LV_OBJ_FLAG_HIDDEN)) {
		if (current_view->has_flag(ViewFlag::NoAnimation))
			lv_obj_add_flag(view_menu, LV_OBJ_FLAG_HIDDEN);
		else
			lv_anim_start(&anim_sidebar_close);
	}

	if (lv_obj_has_flag(shade, LV_OBJ_FLAG_HIDDEN)) {
		lv_obj_clear_flag(shade, LV_OBJ_FLAG_HIDDEN);
		if (current_view->has_flag(ViewFlag::NoAnimation)) return;
		lv_anim_start(&anim_shade_show);
	}

	lv_obj_clear_flag(alert_cont, LV_OBJ_FLAG_HIDDEN);

	lv_obj_t *alert = lv_obj_create(alert_cont);
	lv_obj_set_width(alert, lv_pct(100));
	lv_obj_set_height(alert, LV_SIZE_CONTENT);
	lv_obj_add_event_cb(alert, alert_cb, LV_EVENT_CLICKED, view);
	lv_obj_add_style(alert, &style_alert, 0);

	lv_obj_t *origin_label = lv_label_create(alert);
	lv_obj_align(origin_label, LV_ALIGN_TOP_LEFT, 0, 0);
	lv_obj_add_style(origin_label, &style_text_small, 0);
	lv_label_set_text(origin_label, view.get_name().c_str());

	lv_obj_t *alert_msg = lv_label_create(alert);
	lv_obj_align(alert_msg, LV_ALIGN_TOP_LEFT, 0, 18);
	lv_obj_set_width(alert_msg, lv_pct(100));
	lv_obj_add_style(alert_msg, &style_text_medium, 0);
	lv_label_set_long_mode(alert_msg, LV_LABEL_LONG_WRAP);
	lv_label_set_text(alert_msg, message.c_str());
}
