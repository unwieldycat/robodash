#include "virtual_lcd.hpp"
#include "common/styles.hpp"

// =============================== Variables =============================== //

bool initialized = false;
std::vector<std::function<void()>> actions;
int console_height = 0;

lv_obj_t *bg;
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
		lv_label_set_recolor(console_line, true);
	}

	console_height = height;
}

void pml::lcd::print_ln(int line, std::string text) {
	if (initialized) return;
	if (line > console_height) return;

	lv_obj_t *console_line = lv_obj_get_child_back(console_cont, NULL);
	for (int i = 0; i < line - 1; i++) {
		console_line = lv_obj_get_child_back(console_cont, console_line);
	}

	lv_label_set_text(console_line, text.c_str());
}

void pml::lcd::clear_ln(int line) {
	if (!initialized) return;
	if (line > console_height) return;

	lv_obj_t *console_line = lv_obj_get_child_back(console_cont, NULL);
	for (int i = 0; i < line - 1; i++) {
		console_line = lv_obj_get_child_back(console_cont, console_line);
	}

	lv_label_set_text(console_line, "");
}

// ============================== Actions List ============================== //

lv_res_t act_btn_action(_lv_obj_t *obj) {
	int act_id = lv_obj_get_free_num(obj);
	actions[act_id]();
	return LV_RES_OK;
}

void pml::lcd::add_action_btn(std::string label, std::function<void()> action) {
	if (!initialized) return;

	// Unhide list and resize console view for buttons
	lv_obj_set_hidden(actions_list, false);
	lv_obj_set_height(console_cont, 184);
	set_console_lines(6);

	actions.push_back(action);

	int btn_count = actions.size();
	int btn_size = (464 / btn_count) - 2;
	lv_obj_t *btn = lv_obj_get_child(actions_list, NULL);

	while (btn) {
		lv_obj_set_width(btn, btn_size);
		btn = lv_obj_get_child(actions_list, btn);
	}

	lv_obj_t *new_btn = lv_btn_create(actions_list, NULL);
	lv_btn_set_style(new_btn, LV_BTN_STYLE_REL, &btn_style_rel);
	lv_btn_set_style(new_btn, LV_BTN_STYLE_PR, &btn_style_pr);
	lv_obj_set_size(new_btn, btn_size, 32);
	lv_obj_set_free_num(new_btn, actions.size() - 1);
	lv_btn_set_action(new_btn, LV_BTN_ACTION_CLICK, act_btn_action);
	lv_obj_t *btn_label = lv_label_create(new_btn, NULL);
	lv_label_set_text(btn_label, label.c_str());
	lv_obj_align(actions_list, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, -8);
}

// ============================= Initialization ============================= //

bool pml::lcd::is_init() { return initialized; }

void pml::lcd::exit() {
	if (!initialized) return;
	lv_obj_del(bg);
	actions.clear();
	initialized = false;
}

void pml::lcd::init() {
	if (initialized) return;
	initialized = true;
	init_styles();

	bg = lv_cont_create(lv_scr_act(), NULL);
	lv_obj_set_style(bg, &bg_style);
	lv_obj_set_size(bg, 480, 240);
	lv_obj_align(bg, NULL, LV_ALIGN_CENTER, 0, 0);

	static lv_style_t console_style;
	lv_style_copy(&console_style, &lv_style_plain);
	console_style.body.radius = 4;
	console_style.body.main_color = lv_color_hex(0x1a1a1a);
	console_style.body.grad_color = lv_color_hex(0x1a1a1a);
	console_style.body.border.color = lv_color_hex(0x404040);
	console_style.body.border.width = 2;
	console_style.text.color = LV_COLOR_WHITE;

	console_cont = lv_cont_create(bg, NULL);
	lv_obj_set_style(console_cont, &console_style);
	lv_obj_set_size(console_cont, 464, 224);
	lv_obj_align(console_cont, NULL, LV_ALIGN_IN_TOP_MID, 0, 8);
	lv_cont_set_layout(console_cont, LV_LAYOUT_COL_L);
	set_console_lines(7);

	static lv_style_t alist_style;
	lv_style_copy(&alist_style, &lv_style_transp);
	alist_style.body.padding.hor = 0;
	alist_style.body.padding.ver = 0;
	alist_style.body.padding.inner = 4;

	actions_list = lv_cont_create(bg, NULL);
	lv_cont_set_style(actions_list, &alist_style);
	lv_obj_set_size(actions_list, 464, 32);
	lv_cont_set_layout(actions_list, LV_LAYOUT_ROW_M);
	lv_obj_align(actions_list, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, -8);
	lv_obj_set_hidden(actions_list, true);
}