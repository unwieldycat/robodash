#include "gui.hpp"
#include "common/init.hpp"
#include "dashboard.hpp"
#include "screensaver.hpp"

[[noreturn]] void background() {
	while (true) {
		gui::dashboard::_refresh();
		gui::screensaver::_refresh();

		pros::delay(500);
	}
}

void gui::initialize() {
	init_styles();
	init_dashboard();
	init_ss();

	pros::Task gui_task(background, "GUI Update Task");
}