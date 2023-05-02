#include "dashboard.hpp"
#include "common/init.hpp"
#include "common/styles.hpp"

// =============================== Variables =============================== //

lv_obj_t *dashboard_cont;
std::vector<pros::Motor *> motors;

// ============================= Initialization ============================= //

void init_dashboard() {
	dashboard_cont = lv_obj_create(lv_scr_act(), NULL);
	lv_obj_set_size(dashboard_cont, 480, 240);
	lv_obj_set_style(dashboard_cont, &bg_style);

	lv_obj_t *auton_btn = lv_btn_create(dashboard_cont, NULL);
	lv_obj_set_size(auton_btn, 232, 48);
	lv_obj_align(auton_btn, NULL, LV_ALIGN_IN_TOP_LEFT, 8, 8);
	lv_btn_set_style(auton_btn, LV_BTN_STYLE_REL, &outline_round_btn_style_rel);
	lv_btn_set_style(auton_btn, LV_BTN_STYLE_PR, &outline_round_btn_style_pr);
	lv_btn_set_layout(auton_btn, LV_LAYOUT_OFF);

	lv_obj_t *auton_btn_img = lv_img_create(auton_btn, NULL);
	lv_img_set_src(auton_btn_img, SYMBOL_EDIT);
	lv_obj_align(auton_btn_img, NULL, LV_ALIGN_IN_RIGHT_MID, -12, 0);

	lv_obj_t *auton_btn_text = lv_label_create(auton_btn, NULL);
	lv_label_set_text(auton_btn_text, "Auton Name");
	lv_obj_align(auton_btn_text, NULL, LV_ALIGN_IN_LEFT_MID, 12, 0);
}

// ========================== Background Function ========================== //

// TODO: Implement
[[noreturn]] void dashboard_background() {
	while (true) {
		// ...
	}
}

// ========================== Dashboard Functions ========================== //

// TODO: Implement
void gui::dashboard::add_action(std::string name, std::function<void()> fn) {}
void gui::dashboard::add_toggle(std::string name, bool *var) {}

void gui::dashboard::add_motors(std::vector<pros::Motor *> mtrs) {
	motors.insert(motors.end(), mtrs.begin(), mtrs.end());
}