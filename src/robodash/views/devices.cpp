#include "robodash/apix.hpp"

std::vector<pros::Motor *> motors;
lv_obj_t *devices_cont;

// ============================= Core Functions ============================= //

gui::DevicesView::DevicesView() : View("Devices"){};

void gui::DevicesView::initialize() {
	devices_cont = lv_obj_create(this->obj);
	lv_obj_add_style(devices_cont, &style_transp, 0);
	lv_obj_set_size(devices_cont, LV_PCT(100), LV_PCT(100));
	lv_obj_set_size(devices_cont, 464, 192);
	lv_obj_align(devices_cont, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_layout(devices_cont, LV_LAYOUT_FLEX);
	lv_obj_set_flex_flow(devices_cont, LV_FLEX_FLOW_COLUMN);
	lv_obj_set_flex_align(
	    devices_cont, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER
	);
}

void gui::DevicesView::refresh() {}

// ========================== Dashboard Functions ========================== //

void gui::DevicesView::add_motors(std::vector<motor_desc_t> mtrs) {
	for (motor_desc_t motor_desc : mtrs) {
		lv_obj_t *motor_item = lv_obj_create(devices_cont);
		lv_obj_set_size(motor_item, 224, 32);
		lv_obj_add_style(motor_item, &style_btn_outline, 0);
		lv_obj_center(motor_item);
		lv_obj_clear_flag(motor_item, LV_OBJ_FLAG_SCROLLABLE);
		lv_obj_set_user_data(motor_item, motor_desc.second);

		lv_obj_t *motor_port = lv_img_create(motor_item);
		lv_obj_align(motor_port, LV_ALIGN_LEFT_MID, -4, 0);
		lv_obj_set_size(motor_port, 28, 28);
		lv_img_set_src(motor_port, LV_SYMBOL_DUMMY); // temp

		lv_obj_t *motor_name = lv_label_create(motor_item);
		lv_label_set_text(motor_name, motor_desc.first.c_str());
		lv_obj_set_height(motor_name, 24);
		lv_obj_align(motor_name, LV_ALIGN_LEFT_MID, 48, 0);

		lv_obj_t *motor_rpm = lv_label_create(motor_item);
		lv_label_set_text(motor_rpm, "300rpm");
		lv_obj_add_style(motor_rpm, &style_text_small, 0);
		lv_obj_align(motor_rpm, LV_ALIGN_RIGHT_MID, -64, 0);

		lv_obj_t *motor_temp = lv_label_create(motor_item);
		lv_label_set_text(motor_temp, "XX°C");
		lv_obj_add_style(motor_temp, &style_text_small, 0);
		lv_obj_align(motor_temp, LV_ALIGN_RIGHT_MID, -4, 0);

		motors.push_back(motor_desc.second);
	}
}