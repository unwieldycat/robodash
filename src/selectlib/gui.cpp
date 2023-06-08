#include "gui.hpp"
#include "common/init.hpp"

void background() {
	while (true) {
		dashboard_background();
		ss_background();
	}
}

void gui::initialize() {
	init_styles();
	init_dashboard();
	init_ss();

	pros::Task gui_task(background, "GUI Update Task");
}