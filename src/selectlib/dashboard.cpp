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

	// TODO: Refactor all of this
	lv_obj_t *bat_cont = lv_cont_create(dashboard_cont, NULL);
	lv_obj_set_size(bat_cont, 104, 32);
	lv_obj_align(bat_cont, NULL, LV_ALIGN_IN_TOP_RIGHT, -8, 8);
	lv_obj_set_style(bat_cont, &transp_style);
	lv_btn_set_layout(bat_cont, LV_LAYOUT_OFF);

	lv_obj_t *bat_label = lv_label_create(bat_cont, NULL);
	lv_label_set_text(bat_label, "100%");
	lv_obj_align(bat_label, NULL, LV_ALIGN_IN_LEFT_MID, 12, 0);

	lv_obj_t *bat_img = lv_img_create(bat_cont, NULL);
	lv_img_set_src(bat_img, SYMBOL_BATTERY_FULL);
	lv_obj_align(bat_img, NULL, LV_ALIGN_IN_RIGHT_MID, -12, 0);
}

// ========================== Background Function ========================== //

// TODO: Implement
[[noreturn]] void dashboard_background() {
	while (true) {
		pros::delay(500);
	}
}

// ========================== Dashboard Functions ========================== //

// TODO: Implement
void gui::dashboard::add_action(std::string name, std::function<void()> fn) {}

void gui::dashboard::add_motors(std::vector<pros::Motor *> mtrs) {
	motors.insert(motors.end(), mtrs.begin(), mtrs.end());
}