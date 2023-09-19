#include "field.hpp"

lv_obj_t *field_canvas;
lv_obj_t *arrow;

// ============================= Core Functions ============================= //

gui::FieldView::FieldView() : View("Field") {}

void gui::FieldView::refresh() {}

void gui::FieldView::initialize() {
	field_canvas = lv_obj_create(this->obj);
	arrow = lv_img_create(field_canvas);
	lv_img_set_src(arrow, LV_SYMBOL_DUMMY); // temp
}

// ============================ Field Functions ============================ //
