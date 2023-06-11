#include "devices.hpp"
#include "common/styles.hpp"
#include "unwieldy-ui/gui.hpp"

std::vector<pros::Motor *> motors;

// ============================= Core Functions ============================= //

gui::DevicesView::DevicesView() : View("Devices"){};

void gui::DevicesView::initialize() {
	lv_obj_t *label = lv_label_create(this->obj);
	lv_label_set_text(label, "Test");
	lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
}

void gui::DevicesView::refresh() {}

// ========================== Dashboard Functions ========================== //

void gui::DevicesView::add_motors(std::vector<pros::Motor *> mtrs) {
	motors.insert(motors.end(), mtrs.begin(), mtrs.end());
}