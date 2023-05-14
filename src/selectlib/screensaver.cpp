#include "screensaver.hpp"
#include "common/init.hpp"
#include "common/styles.hpp"

bool ss_active = false;
int ss_timeout = 8;

// ============================= Initialization ============================= //

lv_obj_t *ss_cont;
lv_obj_t *ss_img;

void ss_cb(lv_event_t *event) {
	lv_obj_t *obj = event->target;
	lv_obj_add_flag(ss_cont, LV_OBJ_FLAG_HIDDEN);
}

void init_ss() {
	ss_cont = lv_obj_create(lv_scr_act());
	lv_obj_set_size(ss_cont, 480, 240);
	lv_obj_add_event_cb(ss_cont, &ss_cb, LV_EVENT_PRESSED, NULL);
	lv_obj_add_style(ss_cont, &style_bg, 0);
	lv_obj_clear_flag(ss_cont, LV_OBJ_FLAG_HIDDEN);

	// FIXME: Check if screensaver file exists
	ss_img = lv_img_create(ss_cont);
	lv_img_set_src(ss_img, "/usd/screensaver.bin");
	lv_obj_align(ss_img, LV_ALIGN_CENTER, 0, 0);
}

// ========================== Background Function ========================== //

[[noreturn]] void ss_background() {
	uint start_time;
	uint time_diff;

	while (true) {
		if (ss_active) {
			pros::delay(100);
			continue;
		}

		start_time = pros::millis();

		do {
			// Set start time to current time if interaction
			if (pros::screen::touch_status().touch_status != pros::E_TOUCH_RELEASED) {
				start_time = pros::millis();
			}

			time_diff = pros::millis() - start_time;
			pros::delay(30);
		} while (time_diff < ss_timeout * 1000);

		gui::screensaver::activate();
	}
}

// ============================ Other Functions ============================ //

void gui::screensaver::set_image(std::string path) {}

void gui::screensaver::set_timeout(int sec) { ss_timeout = sec; }

void gui::screensaver::activate() {
	if (ss_active) return;
	lv_obj_clear_flag(ss_cont, LV_OBJ_FLAG_HIDDEN);
	ss_active = true;
}

void gui::screensaver::exit() {
	if (!ss_active) return;
	lv_obj_add_flag(ss_cont, LV_OBJ_FLAG_HIDDEN);
	ss_active = false;
}