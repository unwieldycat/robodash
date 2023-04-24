#include "common/init.hpp"
#include "misc.hpp"

void gui::initialize() {
	init_styles();
	init_dashboard();
	init_ss();

	// pros::Task dashboard_task(dashboard_process);
}