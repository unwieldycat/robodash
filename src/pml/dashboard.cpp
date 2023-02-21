#include "dashboard.hpp"
#include "display/lv_core/lv_obj.h"
#include "display/lv_objx/lv_cont.h"

// =============================== Variables =============================== //

std::vector<std::function<void()>> actions;
int console_height = 0;

lv_style_t dashboard_style;
lv_style_t actions_list_style;
lv_style_t btn_style;
lv_style_t btn_style_pressed;
lv_style_t console_style;

lv_obj_t *dashboard;
lv_obj_t *actions_list;
lv_obj_t *console_cont;

// ================================ Console ================================ //

void set_console_lines(int height) {

	if (height < console_height) {
		lv_obj_t *console_child = lv_obj_get_child_back(console_cont, NULL);

		for (int i = 0; i < height; i++) {
			console_child = lv_obj_get_child_back(console_cont, console_child);
		}

		std::vector<lv_obj_t *> children_to_delete;

		while (console_child) {
			children_to_delete.push_back(console_child);
			console_child = lv_obj_get_child_back(console_cont, console_child);
		}

		for (lv_obj_t *child : children_to_delete) {
			lv_obj_del(child);
		}
	}

	for (int i = console_height; i < height; i++) {
		lv_obj_t *console_line = lv_label_create(console_cont, NULL);
		lv_obj_set_size(console_line, 448, 24);
		lv_label_set_text(console_line, "");
	}

	console_height = height;
}

void pml::set_text(int line, std::string text) {
	if (line > console_height) return;

	lv_obj_t *console_line = lv_obj_get_child_back(console_cont, NULL);
	for (int i = 0; i < line - 1; i++) {
		console_line = lv_obj_get_child_back(console_cont, console_line);
	}

	lv_label_set_text(console_line, text.c_str());
}

// ============================== Actions List ============================== //

lv_res_t act_btn_action(_lv_obj_t *obj) {
	int act_id = lv_obj_get_free_num(obj);
	actions[act_id]();
	return LV_RES_OK;
}

void pml::add_action_btn(std::string label, std::function<void()> action) {
	// Unhide list and resize console view for buttons
	lv_obj_set_hidden(actions_list, false);
	lv_obj_set_height(console_cont, 184);
	set_console_lines(6);

	actions.push_back(action);

	lv_obj_t *new_btn = lv_btn_create(actions_list, NULL);
	lv_btn_set_style(new_btn, LV_BTN_STYLE_REL, &btn_style);
	lv_btn_set_style(new_btn, LV_BTN_STYLE_PR, &btn_style_pressed);
	lv_obj_set_size(new_btn, 96, 32);
	lv_obj_set_free_num(new_btn, actions.size() - 1);
	lv_btn_set_action(new_btn, LV_BTN_ACTION_CLICK, act_btn_action);
	lv_btn_set_fit(new_btn, true, false);
	lv_obj_t *btn_label = lv_label_create(new_btn, NULL);
	lv_label_set_text(btn_label, label.c_str());
	lv_obj_align(actions_list, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, -8);
}

// ============================= Initialization ============================= //

void pml::init() {
	lv_style_copy(&dashboard_style, &lv_style_plain);
	dashboard_style.body.border.width = 0;
	dashboard_style.body.radius = 0;
	dashboard_style.body.main_color = lv_color_hex(0x262626);
	dashboard_style.body.grad_color = lv_color_hex(0x262626);

	dashboard = lv_cont_create(lv_scr_act(), NULL);
	lv_obj_set_style(dashboard, &dashboard_style);
	lv_obj_set_size(dashboard, 480, 240);
	lv_obj_align(dashboard, NULL, LV_ALIGN_CENTER, 0, 0);

	lv_style_copy(&console_style, &lv_style_plain);
	console_style.body.radius = 4;
	console_style.body.main_color = lv_color_hex(0x1a1a1a);
	console_style.body.grad_color = lv_color_hex(0x1a1a1a);
	console_style.body.border.color = lv_color_hex(0x404040);
	console_style.body.border.width = 2;
	console_style.text.color = lv_color_hex(0xffffff);

	console_cont = lv_cont_create(dashboard, NULL);
	lv_obj_set_style(console_cont, &console_style);
	lv_obj_set_size(console_cont, 464, 224);
	lv_obj_align(console_cont, NULL, LV_ALIGN_IN_TOP_MID, 0, 8);
	lv_cont_set_layout(console_cont, LV_LAYOUT_COL_L);
	set_console_lines(7);

	lv_style_copy(&actions_list_style, &lv_style_transp);
	lv_style_copy(&btn_style, &lv_style_plain);
	btn_style.body.radius = 4;
	btn_style.body.border.width = 2;
	btn_style.body.border.color = lv_color_hex(0x404040);
	btn_style.body.main_color = lv_color_hex(0x404040);
	btn_style.body.grad_color = lv_color_hex(0x595959);
	btn_style.text.color = lv_color_hex(0xffffff);

	lv_style_copy(&btn_style_pressed, &btn_style);
	btn_style_pressed.body.main_color = lv_color_hex(0x404040);
	btn_style_pressed.body.grad_color = lv_color_hex(0x404040);

	// FIXME: Children dont have same width or expand as much as possible
	actions_list = lv_cont_create(dashboard, NULL);
	lv_obj_set_style(actions_list, &actions_list_style);
	lv_obj_set_height(actions_list, 32);
	lv_cont_set_layout(actions_list, LV_LAYOUT_ROW_M);
	lv_cont_set_fit(actions_list, true, false);
	lv_obj_align(actions_list, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, -8);
	lv_obj_set_hidden(actions_list, true);
}