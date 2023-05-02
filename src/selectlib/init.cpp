#include "common/init.hpp"
#include "misc.hpp"

void gui::initialize() {
	init_styles();
	init_dashboard();
	init_ss();

	// FIXME: Doesn't return, probably need to store variable
	// pros::Task dashboard_task(dashboard_background);
	// pros::Task screensaver_task(ss_background);
}