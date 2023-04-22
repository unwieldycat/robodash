#include "common/init.hpp"
#include "misc.hpp"

void gui::initialize() {
	init_styles();
	init_dashboard();

	pros::Task dashboard_task(dashboard_process);
}