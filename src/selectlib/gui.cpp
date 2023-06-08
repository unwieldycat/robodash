#include "gui.hpp"
#include "dashboard.hpp"
#include "screensaver.hpp"
#include "styles.hpp"

[[noreturn]] void background() {
	while (true) {
		gui::dashboard::_refresh();
		gui::screensaver::_refresh();

		pros::delay(500);
	}
}

void gui::initialize() {
	gui::theme::_initialize();
	gui::dashboard::_initialize();
	gui::screensaver::_initialize();

	pros::Task gui_task(background, "GUI Update Task");
}