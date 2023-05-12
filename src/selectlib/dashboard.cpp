#include "dashboard.hpp"
#include "common/init.hpp"
#include "common/styles.hpp"

// =============================== Variables =============================== //

lv_obj_t *dashboard_cont;
std::vector<pros::Motor *> motors;

// ============================= Initialization ============================= //

void init_dashboard() {
	dashboard_cont = lv_obj_create(lv_scr_act());
	lv_obj_set_size(dashboard_cont, 480, 240);
	lv_obj_add_style(dashboard_cont, &bg_style, 0);

	// TODO: Refactor all of this
	lv_obj_t *bat_cont = lv_obj_create(dashboard_cont);
	lv_obj_set_size(bat_cont, 104, 32);
	lv_obj_align(bat_cont, LV_ALIGN_TOP_RIGHT, -8, 8);
	lv_obj_add_style(bat_cont, &transp_style, 0);
	//  lv_btn_set_layout(bat_cont, LV_LAYOUT_OFF);

	lv_obj_t *bat_label = lv_label_create(bat_cont);
	lv_label_set_text(bat_label, "100%");
	lv_obj_align(bat_label, LV_ALIGN_LEFT_MID, 12, 0);

	lv_obj_t *bat_img = lv_img_create(bat_cont);
	lv_img_set_src(bat_img, LV_SYMBOL_BATTERY_FULL);
	lv_obj_align(bat_img, LV_ALIGN_RIGHT_MID, -12, 0);
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