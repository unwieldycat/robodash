#include "dashboard.hpp"
#include "common/styles.hpp"

// =============================== Variables =============================== //

lv_obj_t *dashboard_cont;
std::vector<pros::Motor *> motors;

lv_obj_t *bat_label;
lv_obj_t *bat_img;

// ============================= Initialization ============================= //

void gui::dashboard::_initialize() {
	dashboard_cont = gui::create_window("Dashboard");
	lv_obj_add_style(dashboard_cont, &style_bg, 0);

	lv_obj_t *bat_cont = lv_obj_create(dashboard_cont);
	lv_obj_set_size(bat_cont, 104, 32);
	lv_obj_align(bat_cont, LV_ALIGN_TOP_RIGHT, -8, 8);
	lv_obj_add_style(bat_cont, &style_transp, 0);

	bat_label = lv_label_create(bat_cont);
	lv_label_set_text(bat_label, "100%");
	lv_obj_align(bat_label, LV_ALIGN_LEFT_MID, 12, 0);
	lv_obj_add_style(bat_label, &style_text_medium, 0);

	bat_img = lv_img_create(bat_cont);
	lv_img_set_src(bat_img, LV_SYMBOL_BATTERY_FULL);
	lv_obj_align(bat_img, LV_ALIGN_RIGHT_MID, -12, 0);
	lv_obj_add_style(bat_img, &style_text_medium, 0);
}

// ============================ Refresh Function ============================ //

void gui::dashboard::_refresh() { pros::delay(1000); }

// ========================== Dashboard Functions ========================== //

// TODO: Implement
void gui::dashboard::add_action(std::string name, std::function<void()> fn) {}

void gui::dashboard::add_motors(std::vector<pros::Motor *> mtrs) {
	motors.insert(motors.end(), mtrs.begin(), mtrs.end());
}