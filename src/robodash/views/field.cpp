#include "field.hpp"

#define FIELD_SIZE 192

lv_obj_t *field;
lv_obj_t *arrow;

double scale = 1;

double pos_x;
double pos_y;
double hdg;

// ============================= Core Functions ============================= //

gui::FieldView::FieldView() : View("Field") {}

void gui::FieldView::refresh() {
	lv_img_set_angle(arrow, hdg * 10);
	lv_obj_set_pos(arrow, (pos_x / scale * FIELD_SIZE), (pos_y / scale * FIELD_SIZE));
}

void gui::FieldView::initialize() {
	field = lv_img_create(this->obj);
	lv_obj_set_size(field, FIELD_SIZE, FIELD_SIZE);
	lv_obj_align(field, LV_ALIGN_TOP_LEFT, 8, 8);

	arrow = lv_img_create(field);
	lv_img_set_src(arrow, LV_SYMBOL_DUMMY); // temp
}

// ============================ Field Functions ============================ //

// This function does not render the arrow to minimize performance loss in
// odometry code
void gui::FieldView::set_pos(double x, double y, double hdg) {
	pos_x = x;
	pos_y = x;
	hdg = hdg;
}

void gui::FieldView::set_scale(double max) { scale = max; }