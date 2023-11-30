#include "api.h"
#include "robodash/apix.h"

// ============================= Routine Class ============================= //

class Routine {
  public:
	Routine(int id, std::string name, std::function<void()> action)
	    : id(id), name(name), action(action) {}

	int id;
	std::string name;
	std::function<void()> action;
};

// =============================== Variables =============================== //

std::vector<Routine> routines;
Routine *selected_routine = nullptr;
bool selection_done = false;
bool selection_running = false;

int saved_id;
char saved_name[256];

lv_obj_t *select_cont;
lv_obj_t *selected_label;
lv_obj_t *saved_toast;
lv_obj_t *routine_list;

lv_anim_t anim_toast;

// ============================= SD Card Saving ============================= //

void sdconf_save() {
	FILE *save_file;
	save_file = fopen("/usd/autoconf.txt", "w");

	if (selected_routine == nullptr) {
		fputs("-1", save_file);
	} else {
		std::string routine_name = selected_routine->name;
		int routine_id = selected_routine->id;

		// File format:
		// [id] [name]
		char file_data[sizeof(routine_name) + sizeof(routine_id) + 1];
		sprintf(file_data, "%d %s", routine_id, routine_name.c_str());

		fputs(file_data, save_file);
	}

	fclose(save_file);
}

void sdconf_load() {
	FILE *save_file;
	save_file = fopen("/usd/autoconf.txt", "r");
	if (!save_file) return;

	// Get file size
	fseek(save_file, 0L, SEEK_END);
	int file_size = ftell(save_file);
	rewind(save_file);

	// Read contents
	fscanf(save_file, "%d %[^\n]", &saved_id, saved_name);
	fclose(save_file);
}

void load_saved() {
	if (!saved_id) return;

	// None selected condition
	if (saved_id == -1) {
		lv_label_set_text(selected_label, "No routine\nselected");
		lv_obj_align(selected_label, LV_ALIGN_CENTER, 120, 0);

		selected_routine = nullptr;
		return;
	}

	// Out of bounds check
	if (routines.size() < saved_id + 1) return;

	Routine selected = routines.at(saved_id);
	std::string routine_name = selected.name;

	// Exit if routine name does not match saved
	if (saved_name != routine_name) return;

	selected_routine = &selected;

	// Update routine label
	char label_str[sizeof(routine_name) + 20];
	sprintf(label_str, "Selected routine:\n%s", routine_name.c_str());
	lv_label_set_text(selected_label, label_str);
	lv_obj_align(selected_label, LV_ALIGN_CENTER, 120, 0);
}

// ============================== UI Callbacks ============================== //

void r_select_act(lv_event_t *event) {

	lv_obj_t *obj = lv_event_get_target(event);
	Routine *routine = (Routine *)lv_event_get_user_data(event);

	if (routine == nullptr) {
		lv_label_set_text(selected_label, "No routine\nselected");
		lv_obj_align(selected_label, LV_ALIGN_CENTER, 120, 0);
	} else {
		std::string routine_name = routine->name;

		char label_str[sizeof(routine_name) + 20];
		sprintf(label_str, "Selected routine:\n%s", routine_name.c_str());
		lv_label_set_text(selected_label, label_str);
		lv_obj_align(selected_label, LV_ALIGN_CENTER, 120, 0);
	}

	selected_routine = routine;
}

void done_act(lv_event_t *event) { selection_done = true; }

void save_act(lv_event_t *event) {
	sdconf_save();
	lv_obj_clear_flag(saved_toast, LV_OBJ_FLAG_HIDDEN);
	lv_anim_start(&anim_toast);
}

// ============================= Core Functions ============================= //

rd::Selector::Selector() {
	this->view = rd_view_create("Auton Selector");

	lv_obj_set_style_bg_color(view->obj, color_bg, 0);

	routine_list = lv_list_create(view->obj);
	lv_obj_set_size(routine_list, 228, 192);
	lv_obj_align(routine_list, LV_ALIGN_BOTTOM_LEFT, 8, -8);
	lv_obj_add_style(routine_list, &style_list, 0);

	selected_label = lv_label_create(view->obj);
	lv_label_set_text(selected_label, "No routine\nselected");
	lv_obj_add_style(selected_label, &style_text_centered, 0);
	lv_obj_align(selected_label, LV_ALIGN_CENTER, 120, 0);

	lv_obj_t *nothing_btn = lv_list_add_btn(routine_list, NULL, "Nothing");
	lv_obj_add_event_cb(nothing_btn, &r_select_act, LV_EVENT_PRESSED, nullptr);
	lv_obj_add_style(nothing_btn, &style_list_btn, 0);
	lv_obj_add_style(nothing_btn, &style_list_btn_pr, LV_STATE_PRESSED);

	lv_obj_t *title = lv_label_create(view->obj);
	lv_label_set_text(title, "Select autonomous routine");
	lv_obj_add_style(title, &style_text_large, 0);
	lv_obj_align(title, LV_ALIGN_TOP_LEFT, 8, 12);

	if (pros::usd::is_installed()) {
		sdconf_load();

		saved_toast = lv_label_create(view->obj);
		lv_label_set_text(saved_toast, "Saved to SD");
		lv_obj_add_style(saved_toast, &style_text_centered, 0);
		lv_obj_add_style(saved_toast, &style_text_small, 0);
		lv_obj_align(saved_toast, LV_ALIGN_BOTTOM_RIGHT, -16, -16);
		lv_obj_add_flag(saved_toast, LV_OBJ_FLAG_HIDDEN);

		lv_obj_t *save_btn = lv_btn_create(view->obj);
		lv_obj_set_size(save_btn, 64, 32);
		lv_obj_align(save_btn, LV_ALIGN_BOTTOM_RIGHT, -172, -8);
		lv_obj_add_event_cb(save_btn, &save_act, LV_EVENT_PRESSED, NULL);
		lv_obj_add_style(save_btn, &style_btn, 0);
		lv_obj_add_style(save_btn, &style_btn_outline, 0);
		lv_obj_add_style(save_btn, &style_btn_outline_pr, LV_STATE_PRESSED);

		lv_obj_t *save_img = lv_img_create(save_btn);
		lv_img_set_src(save_img, LV_SYMBOL_SAVE);
		lv_obj_set_align(save_img, LV_ALIGN_CENTER);
	}

	lv_anim_init(&anim_toast);
	lv_anim_set_var(&anim_toast, saved_toast);
	lv_anim_set_time(&anim_toast, 255);
	lv_anim_set_delay(&anim_toast, 3000);
	lv_anim_set_exec_cb(&anim_toast, &anim_text_opa_cb);
	lv_anim_set_deleted_cb(&anim_toast, &anim_del_cb);
	lv_anim_set_values(&anim_toast, 255, 0);
}

// ============================= Other Methods ============================= //

void rd::Selector::add_autons(std::vector<routine_t> new_routines) {
	for (routine_t routine : new_routines) {
		static int r_index = 0;

		Routine new_routine(r_index, routine.first, routine.second);
		routines.push_back(new_routine);

		r_index++;
	}

	for (Routine &routine : routines) {
		lv_obj_t *new_btn = lv_list_add_btn(routine_list, NULL, routine.name.c_str());
		lv_obj_add_style(new_btn, &style_list_btn, 0);
		lv_obj_add_style(new_btn, &style_list_btn_pr, LV_STATE_PRESSED);
		lv_obj_add_event_cb(new_btn, &r_select_act, LV_EVENT_PRESSED, &routine);
	}

	load_saved();
}

void rd::Selector::do_auton() {
	if (selected_routine == nullptr) return; // If commanded to do nothing then return
	selected_routine->action();
}

void rd::Selector::focus() { rd_view_focus(this->view); }