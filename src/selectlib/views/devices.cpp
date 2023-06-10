#include "devices.hpp"
#include "common/styles.hpp"
#include "selectlib/gui.hpp"

std::vector<pros::Motor *> motors;

// ============================= Core Functions ============================= //

gui::DevicesWindow::DevicesWindow() : Window("Devices"){};

void gui::DevicesWindow::initialize() {
	lv_obj_add_style(this->obj, &style_bg, 0);

	lv_obj_t *label = lv_label_create(this->obj);
	lv_label_set_text(label, "Test");
	lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
}

void gui::DevicesWindow::refresh() {}

// ========================== Dashboard Functions ========================== //

void gui::DevicesWindow::add_motors(std::vector<pros::Motor *> mtrs) {
	motors.insert(motors.end(), mtrs.begin(), mtrs.end());
}