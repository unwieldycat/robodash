#include "common/init.hpp"
#include "misc.hpp"

void sl::init() {
	init_styles();
	init_dashboard();

	pros::Task dashboard_task(dashboard_process);
}