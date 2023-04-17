#include "common/init.hpp"
#include "common/styles.hpp"
#include "display/lv_core/lv_obj.h"
#include "display/lv_objx/lv_cont.h"
#include "display/lv_objx/lv_img.h"

lv_obj_t *dashboard_cont;

void create_dashboard() {
	dashboard_cont = lv_obj_create(lv_scr_act(), NULL);
	lv_obj_set_size(dashboard_cont, 480, 240);
	lv_obj_set_style(dashboard_cont, &bg_style);

	lv_obj_t *auton_btn = lv_btn_create(dashboard_cont, NULL);
	lv_obj_set_size(auton_btn, 64, 64);
	lv_obj_align(auton_btn, NULL, LV_ALIGN_CENTER, -4, 0);
	lv_btn_set_style(auton_btn, LV_BTN_STYLE_REL, &outline_round_btn_style_rel);
	lv_btn_set_style(auton_btn, LV_BTN_STYLE_PR, &outline_round_btn_style_pr);
	lv_btn_set_layout(auton_btn, LV_LAYOUT_CENTER);

	lv_obj_t *auton_btn_img = lv_img_create(auton_btn, NULL);
	lv_img_set_src(auton_btn_img, SYMBOL_EDIT);

	lv_obj_t *auton_btn_text = lv_label_create(auton_btn, NULL);
	lv_label_set_text(auton_btn_text, "Edit Auton");
	lv_label_set_style(auton_btn_text, &small_text);
}